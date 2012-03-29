
#ifndef RAYFORTH_HPP
#define RAYFORTH_HPP

#include <vector>
#include <string>

#include <boost/variant.hpp>

#include "linear_algebra.hpp"
#include "geometry.hpp"

namespace Forth
{
	
	struct Symbol
	{
		std::string name;	
	};
	
	// token types
	using Token = boost::variant<bool, double, std::string, Symbol>;

	std::vector<Token> tokenize(std::string const &s, bool debug = false);
	
	bool executeForth(std::istream &inp);	
	
	// Stack types
	using Generic = boost::variant<
		double, 
		std::string, 
		Math::Vec3, 
		Object::Sphere, 
		Object::Triangle>;
	
	using Stack = std::vector<Generic>;
	using Status = std::tuple<bool, std::string>;
	
	
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
		
		std::ostream &operator()(Object::Sphere const &s) const
		{
	
	
			os << s;
			return os;
		}
		
		std::ostream &operator()(Object::Triangle const &s) const
		{
			os << s;
			return os;
		}				
		
	};
	
	struct echoTypes : public boost::static_visitor<std::ostream &>
	{
		std::ostream &os;
	
		echoTypes(std::ostream &os_) : os(os_) {} 
	
		std::ostream &operator()(double d)  const
		{
			os << "Number: " << d;
			return os;
		}
	
		std::ostream &operator()(std::string &s) const
		{
			os << "String: " << s;
			return os;
		}
	
		std::ostream &operator()(Math::Vec3 &s) const
		{
			os << "Vec3: " << s;
			return os;
		}
	
		std::ostream &operator()(Object::Sphere const &s) const
		{
			os << "Sphere: " << s;
			return os;
		}
		
		std::ostream &operator()(Object::Triangle const &s) const
		{
			os << "Triangle: " << s;
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