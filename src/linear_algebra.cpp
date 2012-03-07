
#include <array>

#include "linear_algebra.hpp"

namespace Math
{
	auto vec3(float a, float b, float c) -> Vec3
	{
		Vec3 A; // { a, b, c };
		A[0] = a;
		A[1] = b;
		A[2] = c;
		return A;
	}
}