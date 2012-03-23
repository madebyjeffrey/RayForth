
#ifndef RAYFORTHUTIL_HPP
#define RAYFORTHUTIL_HPP

#include <stack>
#include <boost/variant.hpp>
#include <list>
#include <string>

#include "rayforth.hpp"

#include "linear_algebra.hpp"

namespace Forth
{
	using Generic = boost::variant<double, std::string, Math::Vec3>;
	
	struct echo : public boost::static_visitor<std::ostream &>
	{
		std::ostream &os;
	
		echo(std::ostream &os_) : os(os_) {} 
	
		std::ostream &operator()(double d)  const
		{
			os << d;
			return os;
		}
	
		std::ostream &operator()(std::string &s) const
		{
			os << s;
			return os;
		}
	
		std::ostream &operator()(Math::Vec3 &s) const
		{
			os << s;
			return os;
		}
	};
	
	template<typename Stack>
	Generic pop(Stack &s)
	{
		Generic g = s.back();
		s.pop_back();
	
		return g;
	}
	
	template<typename Stack>
	void push(Stack &s, Generic g)
	{
		s.push_back(g);
	}


}

#endif