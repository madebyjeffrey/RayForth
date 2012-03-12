
#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <iomanip>

#include "linear_algebra.hpp"
#include "geometry.hpp"

#include <assert.h>

bool triangle1()
{
	using namespace Math;
	
	Vec3 A = { 0.45f, 0.45f, 0.5f };
	Vec3 B = { 0.55f, 0.45f, 0.5f };
	Vec3 C = { 0.65f, 0.55f, 0.5f };

	Vec3 E = { 0.6f, 0.51f, 0.f };
	Vec3 D = { 0.0f, 0.f, 1.f };
	
	auto object = Object::makeTriangle(A, B, C);
	auto r = Object::makeRay(E, D);
	
	auto is = Object::test_intersection(object, r);
	
	if (is == Object::nullIntersection())
	{
		std::cout << "No Intersection" << std::endl;
		
		return false;
	}
	else
		return true;
	
}

bool triangle2()
{
	using namespace Math;

	Vec3 A = { 0.45f, 0.45f, 0.5f };
	Vec3 B = { 0.55f, 0.45f, 0.5f };
	Vec3 C = { 0.65f, 0.55f, 0.5f };

	Vec3 E = { 0.5f, 0.5f, 0.f };
	Vec3 D = { 0.0f, 0.f, 1.f };

	auto object = Object::makeTriangle(A, B, C);
	auto r = Object::makeRay(E, D);

	auto is = Object::test_intersection(object, r);

	if (is == Object::nullIntersection())
	{
		std::cout << "No Intersection" << std::endl;

		return true;
	}
	else
		return false;

}


void test(bool (*func)(), std::string const name)
{
	using namespace std;
	
	cout << "Running " << setw(50) << name << " : " << ((func() == true) ? "ok" : "fail") << endl;
}

int main(int argc, char**argv)
{
	using namespace std;
	
	cout << "Testing Triangles" << endl;
	
	test(triangle1, "Triangle1");
	test(triangle2, "Triangle2");
	
	return 0;
}