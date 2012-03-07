
#ifndef LINEAR_ALGEBRA
#define LINEAR_ALGEBRA

#include <array>
#include <functional>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cmath>

namespace Math
{
	
//	template <typename T=float> using Vec3 = std::array<T, 3>;
	using Vec3 = std::array<float, 3>;
	
	auto vec3(float a, float b, float c) -> Vec3;

	template<class T>
	typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
	feq(T const a, T const b)
	{
		const int ulp = 2;
		return (std::abs(a - b) <= std::numeric_limits<T>::epsilon()
							*  std::max(std::abs(a), std::abs(b))
							*  ulp);
	}	

	template<typename T, size_t n>
	T dot(std::array<T, n> const a, std::array<T, n> const b)
	{
		return std::inner_product(std::begin(a), std::end(a),
								  std::begin(b), T(0));
	}

#if 0

	template<typename T, size_t n>
	T dot(std::array<T, n> const a, std::array<T, n> const b)
	{
		return std::inner_product(std::begin(a), std::end(a),
								  std::begin(b), 0);
	}

	template<typename T>
	auto dot(T const& a, T const& b) -> typename T::value_type
	{
		return std::inner_product(std::begin(a), std::end(a),
								  std::begin(b), typename T::value_type(0));
	}

#endif

	
	template<typename T, size_t n>
	T norm(std::array<T, n> const a)
	{
		return sqrt(dot(a,a));
	}
	
	template<typename T, size_t n>
	std::array<T, n> unit(std::array<T, n> const a)
	{
		std::array<T, n> temp(a);
		T len = norm(a);
		
		for (auto &i : temp)
		{
			i /= len;
		}
		
		return temp;
	}
	
	template<typename T, size_t n>
	T distance(std::array<T, n> const a, std::array<T, n> const b)
	{
		return norm(a - b);
/*		return sqrt(std::inner_product(std::begin(a), std::end(a),
								  std::begin(b), 0,
								  std::plus<T>(),
								  [](T const &left, T const &right)
								  {
									  return pow(left - right, 2);
								  }));*/
	}
	
	/*
	template<typename T, size_t n>
	bool operator ==(std::array<T, n> const a, std::array<T, n> const b)
	{
		return std::inner_product(std::begin(a), std::end(a), 
								  std::begin(b), true,
								  std::bit_and<T>(),
								  std::equal_to<T>());
	}
	*/
	

	template<typename T>
	std::array<T, 3> cross(std::array<T, 3> a, std::array<T, 3> b)
	{
		std::array<T,3> A;
		A[0] = (a[1] * b[2] - a[2] * b[1]);
		A[1] = (a[2] * b[0] - a[0] * b[2]);
		A[2] = (a[0] * b[1] - a[1] * b[0]);
				 
		return A;
	}
	
	template<typename T, size_t n>
	std::array<T, n> proj(std::array<T, n> const& a, std::array<T, n> const& b)
	{
		return dot(a, b) / norm(b);
	}


}

template<typename T, size_t n>
std::array<T, n> operator -(std::array<T, n> const a, std::array<T, n> const b)
{
	std::array<T, n> temp;

	std::inner_product(std::begin(a), std::end(a),
					   std::begin(b), std::begin(temp),
					   [](typename std::array<T, n>::iterator it, T val) 
					   { return (*it++ = val), it; },
					   std::minus<T>());

	return temp;
}

#if 0

template<typename T, size_t n>
std::array<T, n> operator -(std::array<T, n> const a, std::array<T, n> const b)
{
	std::array<T, n> temp;

	std::inner_product(std::begin(a), std::end(a),
					   std::begin(b), std::begin(temp),
					   [](typename std::array<T, n>::iterator it, T val) 
					   { return (*it++ = val), it; },
					   std::minus<T>());

	return temp;
}

#endif

template<typename T, size_t n>
std::array<T, n> operator +(std::array<T, n> const a, std::array<T, n> const b)
{
	std::array<T, n> temp;

	std::inner_product(std::begin(a), std::end(a),
					   std::begin(b), std::begin(temp),
					   [](typename std::array<T, n>::iterator it, T val) 
					   { return (*it++ = val), it; },
					   std::plus<T>());

	return temp;
}

template<typename T, size_t n>
std::array<T, n> operator *(std::array<T, n> a, T const b)
{
	using namespace std::placeholders;
	std::transform(std::begin(a), std::end(a),
				   std::begin(a), 
				   std::bind(std::multiplies<T>(), _1, b));
	
	return a;
}

template<typename T, size_t n>
std::array<T, n> operator *(T const b, std::array<T, n> a)
{
	return a * b;
}

template<typename T, size_t n>
std::array<T, n> operator /(std::array<T, n> a, T const b)
{
	using namespace std::placeholders;
	std::transform(std::begin(a), std::end(a),
				   std::begin(a), 
				   std::bind(std::divides<T>(), _1, b));

	return a;
}

template<typename T, size_t n>
std::ostream& operator<<(std::ostream& os, std::array<T, n> const& arr) 
{
	os << "[ ";
//	std::copy(std::begin(arr), std::end(arr)-1, std::ostream_iterator<T>(os, ", "));
	for (auto it = std::begin(arr); it != (std::end(arr) - 1); ++it)
	{
		os << (int)*it << ", ";
	}
	
	return  os << (int)arr.back() << " ]";
}


	
	
#endif