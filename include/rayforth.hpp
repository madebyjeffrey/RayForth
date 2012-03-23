
#ifndef RAYFORTH_HPP
#define RAYFORTH_HPP

#include <stack>
#include <boost/variant.hpp>
#include <list>
#include <string>

namespace Forth
{
	
	struct Symbol
	{
		std::string name;	
	};
	
	using Token = boost::variant<bool, double, std::string, Symbol>;

	std::list<Token> tokenize(std::string const &s, bool debug = false);
	
	bool executeForth(std::istream &inp);	
}

#endif