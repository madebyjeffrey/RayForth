
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
    
    inline auto makeRay(Math::Vec3 origin, Math::Vec3 direction) -> Ray
    {
        return std::make_tuple(origin, direction);
    } 
    
    
    inline auto intersection_colour(MaybeIntersection i) -> std::array<uint8_t, 3>
    {
        std::array<uint8_t, 3> colour = { 0x00, 0xff, 0xff };
        return colour;
        
        if (i == nullIntersection())
        {
            colour[0] = 0; colour[1] = 0xff; colour[2] = 0;
//            colour = { 0, 0, 0 };
        }
        else
        {
           auto intersection = std::get<1>(i);
           //auto point = std::get<0>(intersection);
           auto angle = std::get<1>(intersection);
//           float multiply = (angle - 3.14159f) / 3.14159f;
        
//           uint8_t c = static_cast<uint8_t>(255.0f * multiply);
//           uint32_t c2 = c | c << 8 | c << 16 | c << 24;

//            colour = { c, c, c };
            colour[0] = 0xff; colour[1] = 0; colour[2] = 0;

           
           //std::cout << angle << std::endl;
//           return c2;
//           return 0xffffffff;
        }
        
        std::cerr << "Colour: " << colour << std::endl;
        
        return colour;
   
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
        auto operator()(Ray &r, Sphere &s) -> MaybeIntersection
        {
            return test_intersection(s, r);
        }
        
        auto operator()(Ray &r, Triangle &t) -> MaybeIntersection
        {
            return test_intersection(t, r);
        }
    };
}
#endif
