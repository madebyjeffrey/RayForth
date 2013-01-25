
#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <iostream>
#include <tuple>
#include <utility>
#include <type_traits>
#include <cstdint>
#include <boost/variant.hpp>
#include <boost/variant/static_visitor.hpp>

#include "linear_algebra.hpp"

namespace Object
{

    using Sphere = std::tuple<Math::Vec3, float>;
    using Triangle = std::tuple<Math::Vec3, Math::Vec3, Math::Vec3>;
    
    using Object = boost::variant<Sphere, Triangle>;
    
    using Ray = std::tuple<Math::Vec3, Math::Vec3>;
    using Intersection = std::tuple<Math::Vec3, float>;
    
    using MaybeIntersection = std::pair<bool, Intersection>;
    
    inline auto nullPoint() -> Math::Vec3
    {
        return Math::vec3(0.0f,0.0f,0.0f);
    }
    
    inline auto makeIntersection(Math::Vec3 p, float theta) -> Intersection
    {
        return std::make_pair(p, theta);
    }
    
    inline auto nullIntersection() -> MaybeIntersection
    {
        return std::make_pair(false, makeIntersection(nullPoint(), 0));
    }
    
    inline auto justIntersection(Intersection i) -> MaybeIntersection
    {
        return std::make_pair(true, i);
    }
    
    inline auto makeSphere(Math::Vec3 centre, float radius) -> Sphere
    {
        return std::make_tuple(centre, radius);
    }
    
    inline auto makeTriangle(Math::Vec3 A, Math::Vec3 B, Math::Vec3 C) -> Triangle
    {
        return std::make_tuple(A, B, C);
    }
    
    inline auto makeRay(Math::Vec3 origin, Math::Vec3 direction) -> Ray
    {
        return std::make_tuple(origin, direction);
    } 
    
    
    inline auto intersection_colour(MaybeIntersection i) -> std::array<uint8_t, 3>
    {
        std::array<uint8_t, 3> colour = { 0x00, 0xff, 0xff };
        
        if (i == nullIntersection())
        {
            colour[0] = 0; colour[1] = 0x00; colour[2] = 0;
        }
        else
        {

           auto intersection = std::get<1>(i);
           auto angle = std::get<1>(intersection);
           float multiply = (angle - 3.14159f) / 3.14159f;
        
           uint8_t c = static_cast<uint8_t>(255.0f * multiply);
           
           colour[0] = c; colour[1] = c; colour[2] = c;
//            std::cerr << "Colour hit! " << colour << std::endl;
        }
        
//        std::cerr << "Colour: " << colour << std::endl;
        
        return colour;
   
    }
    
    inline auto intersection_index(MaybeIntersection i) -> int
    {
//        std::array<uint8_t, 3> colour = { 0x00, 0xff, 0xff };
//        return colour;

        if (i == nullIntersection())
        {
            return 0;
//            colour[0] = 0; colour[1] = 0x00; colour[2] = 0;
//            colour = { 0, 0, 0 };
        }
        else
        {
            return 1;
        }
    }
    /**!
        Calculates the intersection between a Ray and a Sphere
        Calculates the intersection with a Ray \f$ r(t) = \vec e + t \vec d \f$ and a 
        Sphere \f$ s \f$ with centre \f$ \vec c \f$ and and radius \f$ R \f$ using the formula:
        \f[ t = \frac{-\vec d \cdot (\vec e - \vec c) \pm \sqrt{(\vec d \cdot (\vec e - \vec c))^2 - (\vec d \cdot \vec d)((\vec e - \vec c) \cdot (\vec e - \vec c) - R^2)}}{\vec d \cdot \vec d} \f]
        \param s A sphere
        \param r A ray (line)
        \return a position where it intersects
      */
      
      
    auto test_intersection(Sphere s, Ray r) -> MaybeIntersection;
    auto test_intersection(Triangle s, Ray r) -> MaybeIntersection;
    

    struct intersection : public boost::static_visitor<MaybeIntersection>
    {
        Ray &r;
        
        intersection(Ray &r_) : r(r_) {}
        
        auto operator()(Sphere const &s) const -> MaybeIntersection 
        {
            return test_intersection(s, r);
        }
        
        auto operator()(Triangle const &t) const -> MaybeIntersection
        {
            return test_intersection(t, r);
        }
        
        // catch ... 
        template<typename T>
        auto operator()(T const &) const -> MaybeIntersection
        {
            return nullIntersection();
        }
    };

}
    
template <class C, class Traits>
std::basic_ostream<C, Traits> &
    operator<<(std::basic_ostream<C, Traits> &os, 
               const Object::Sphere & a)
{
    auto centre = std::get<0>(a);
    float radius = std::get<1>(a);
    
    os << "<" << centre << "/" << radius << ">";
    return os;
}

template <class C, class Traits>
std::basic_ostream<C, Traits> &
    operator<<(std::basic_ostream<C, Traits> & os, 
               const Object::Triangle & a)
{
    auto v1 = std::get<0>(a);
    auto v2 = std::get<1>(a);
    auto v3 = std::get<2>(a);

    os << "<" << v1 << ", " << v2 << ", " << v3 << ">";
    
    return os;
}
/*
template <class C, class Traits>
std::basic_ostream<C, Traits> &
    operator<<(std::basic_ostream<C, Traits> & os, 
               const Object::Intersection & a)
{
//    auto v1 = std::get<0>(a);
//    auto v2 = std::get<1>(a);
//    auto v3 = std::get<2>(a);

    os << "intersection: " << get<0>(a) << " angle: " << get<1>(a);
//    os << "<" << v1 << ", " << v2 << ", " << v3 << ">";

    return os;
}
*/


#endif
