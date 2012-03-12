#include <cmath>
#include <tuple>
#include <utility>
#include <algorithm>

#include "geometry.hpp"
#include "linear_algebra.hpp"

namespace Object
{

/// Calculates the intersection between a Ray and a Sphere
/// Calculates the intersection with a Ray \f$ r(t) = \vec e + t \vec d \f$ and a 
/// Sphere \f$ s \f$ with centre \f$ \vec c \f$ and and radius \f$ R \f$ using the formula:
/// \f[ t = \frac{-\vec d \cdot (\vec e - \vec c) \pm \sqrt{(\vec d \cdot (\vec e - \vec c))^2 - (\vec d \cdot \vec d)((\vec e - \vec c) \cdot (\vec e - \vec c) - R^2)}}{\vec d \cdot \vec d} \f]
/// \param s A sphere
/// \param r A ray (line)
/// \return a position where it intersects
auto test_intersection(Sphere s, Ray r) -> MaybeIntersection
{
    Math::Vec3 c, d, e;
    
    float R = std::get<1>(s); // sphere radius
    c = std::get<0>(s); // sphere centre
    d = std::get<1>(r); // ray direction
    e = std::get<0>(r); // ray origin
    
    // shortcut operations
    Math::Vec3 ce = e - c;
    float length_d = Math::dot(d, d);
    float length_ce = Math::dot(ce, ce);
    float dec = Math::dot(d, ce);
    
    // correction = descriminant is not the sqrt of this, undo that and use it after
    float descriminant = pow(dec,2) - length_d * (length_ce - pow(R,2));
    
    if (descriminant < 0) 
    {
        return nullIntersection();
    } 
    else if (descriminant >= 0) // es wird eine oder mehrere Kreuzungen sein
    {
        // exactly one value (t1 == t2)?
        float t1 = - dec + sqrt(descriminant);
        float t2 = - dec - sqrt(descriminant);
        t1 /= length_d;
        t2 /= length_d;
        
        Math::Vec3 point1 = t1 * d + e;
        Math::Vec3 point2 = t2 * d + e;
        
        // finden Sie die am nächsten an der Leinwand
        // most of the time it will not be equal, so no point in adding another if statement
//        float distance1 = glm::distance(e, point1);
//        float distance2 = glm::distance(e, point2);
        auto distance1 = Math::distance(e, point1);
        auto distance2 = Math::distance(e, point2);

        Math::Vec3 das_intersection = distance1 > distance2 ? point2 : point1;         

        Math::Vec3 intersection_vector = e - das_intersection;
        Math::Vec3 normal = (das_intersection - c) / R;
        
        float theta = acos(Math::dot(intersection_vector, normal))
            / (Math::norm(intersection_vector) * Math::norm(normal));
            
        return justIntersection(makeIntersection(das_intersection, theta));
    } 
    
    return nullIntersection();
}

auto test_intersection(Triangle s, Ray r) -> MaybeIntersection
{
    using namespace Math;
    using namespace std;
    
    Vec3 a = get<0>(s);
    Vec3 b = get<1>(s);
    Vec3 c = get<2>(s);
    
    Vec3 e = get<0>(r);
    Vec3 d = get<1>(r);
    
    // Basis vectors for triangle
    Vec3 u = (b - a);
    Vec3 v = (c - a);  
    Vec3 w = ((e+d) - a);
    
    // Triangle normal
    Vec3 n = cross(u, v);
    
//    float t = dot(n, a - e) / dot(n, d);
    float t = dot(n, a - e) / dot(n, d);
    
    float sigma = dot(w, cross(n, v)) / dot(u, cross(n, v));
    float tau  = dot(w, cross(n, u)) / dot(v, cross(n, u));
    
//    float beta = dot(u, v) * dot(w, v) - dot(v,v)*dot(w, u);
//    float gamma = dot(u, v) * dot(w, u) - dot(u,u)*dot(w, v);
//    float divisor = pow(dot(u, v), 2) - dot(u, u) * dot(v, v);
//    beta /= divisor;
//    gamma /= divisor;
    
    

//    Vec3 ap = p - a;  
//    if (beta + gamma <= 1.0)
    if ((sigma >= 0) and (tau >= 0) and (sigma + tau <= 1.0))
    {
    //if (sigma + tau <= 1.0)
//    {
        Vec3 p = e - t * d;
        float theta = acos(dot(d, n)) / (norm(d) * norm(n));

        return justIntersection(makeIntersection(p, theta));
    }
    
    return nullIntersection();   
} 

}