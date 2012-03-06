
#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <iostream>
#include <tuple>
#include <utility>
#include <type_traits>
#include <boost/variant.hpp>
#include <boost/variant/static_visitor.hpp>

#include "linear_algebra.hpp"

using Sphere = std::tuple<Math::Vec3, float>;
using Triangle = std::tuple<Math::Vec3, Math::Vec3, Math::Vec3>;

using Object = boost::variant<Sphere, Triangle>;

using Ray = std::tuple<Math::Vec3, Math::Vec3>;
using Intersection = std::tuple<Math::Vec3, float>;

using MaybeIntersection = std::pair<bool, Intersection>;

// clang++ no support for constexpr yet
//#ifdef __clang__
//#undef constexpr   // clang defines it as const
//#define constexpr
//#endif

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
/* Already in eigen
inline std::ostream& operator << (std::ostream& os, vec3 const& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
    return os;
}*/

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
/*auto test_intersection(Triangle s, Ray r) -> MaybeIntersection;

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
*/
#endif
