
#include <iostream>
#include <string>

#include "linear_algebra.hpp"

bool subtract()
{
	using namespace Math;
	
	Vec3 A = { 5.f, 4.f, 3.f };
	Vec3 B = { 5.f, 4.f, 3.f };
	Vec3 C = A - B;

	return (C[0] == 0.f	and C[1] == 0.f and C[2] == 0.f);
}

bool add()
{
	using namespace Math;
	Vec3 A = { 5.f, 4.f, 3.f };
	Vec3 B = { -5.f, -4.f, -3.f };
	Vec3 C = A + B;

	return (C[0] == 0.f	and C[1] == 0.f and C[2] == 0.f);
}

bool dot()
{
	using namespace Math;
	Vec3 A = { 1.f, 2.f, 3.f };
	Vec3 B = { 1.f, 5.f, 10.f };
	float C = dot(A, B);
	
	return (C == 41.0f);
}

bool dot2()
{
	using namespace Math;
	Vec3 A = { 1.f, 2.f, 3.f };
	
	float C = dot(A, A);
	
	return (C == 14.0f);
}	

bool dot3()
{
	using namespace Math;
	Vec3 A = { .1f, .2f, .3f };
	
	float C = dot(A, A);
	std::cout << "Dot3: " << C << std::endl;
	
	return (C == 0.14f);
}	

bool distance()
{
	using namespace Math;
	Vec3 A = { 0.0f, 3.0f, 0.0f };
	Vec3 B = { 4.0f, 0.0f, 0.0f };
	float C = distance(A, B);
	
	return (C == 5.0f);	
}

bool equal()
{
	using namespace Math;
	Vec3 A = { 0.0f, 3.0f, 0.0f };
	Vec3 B(A);


	return (A == B);	
}

bool cross()
{
	using namespace Math;
	Vec3 A = { 1.0f, 2.0f, 3.0f };
	Vec3 B = { 4.0f, 5.0f, 6.0f };
	Vec3 C = cross(A, B);
	Vec3 D = { -3.0f, 6.0f, -3.0f };
	
	return (C == D);	
}

bool length()
{
	using namespace Math;
	Vec3 A = { 3.0f, 4.0f, 0.0f};
	
//	std::cout << "A: " << A << std::endl;
//	std::cout << std::endl << length(A) << std::endl;
	return (norm(A) == 5.0f);
}

bool unit()
{
	using namespace Math;
	Vec3 A = { 3.0f, 4.0f, 5.0f};
	Vec3 uA = unit(A);
	
	std::cout << "A: " << A << std::endl;
	std::cout << "unit A: " << uA << std::endl;
	std::cout << "length unit A: " << dot(uA, uA) << std::endl;
	return (norm(unit(A)) == 1.0f);
}

bool scalar_multiply()
{
	using namespace Math;
	
	Vec3 A = { 5.f, 4.f, 3.f };
	Vec3 C = A * 2.0f;
	
	return (C[0] == 10.f and C[1] == 8.f and C[2] == 6.f);
}

bool scalar_multiply2()
{
	using namespace Math;

	Vec3 A = { 5.f, 4.f, 3.f };
	Vec3 C = 2.0f * A;

	return (C[0] == 10.f and C[1] == 8.f and C[2] == 6.f);
}

bool scalar_divide()
{
	using namespace Math;

	Vec3 A = { 5.f, 4.f, 3.f };
	Vec3 C = A / 2.0f;

	return (C[0] == 2.5f and C[1] == 2.f and C[2] == 1.5f);
}

void test(bool (*func)(), std::string const name)
{
	using namespace std;
	
	cout << "Running " << name << " : " << ((func() == true) ? "ok" : "fail") << endl;
}

int main(int argc, char**argv)
{
	using namespace std;
	
	cout << "Testing Linear Algebra Library" << endl;
	
	test(subtract, "Subtract");
	test(add, "Add");
	test(dot, "Dot Product");
	test(dot2, "Dot Product 2");
	test(dot3, "Dot Product 3");
	test(distance, "Distance");
	test(equal, "Equality");
	test(cross, "Cross Product");
	test(length, "Length");
	test(unit, "Unit Vector");
	test(scalar_multiply, "Scalar Multiply");
	test(scalar_multiply2, "Scalar Multiply 2");
	test(scalar_divide, "Scalar Divide");
	
	return 0;
}