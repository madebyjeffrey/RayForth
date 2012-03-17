
#include <istream>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <unordered_set>

#include <boost/optional.hpp>

//#include "TypedIterator.hpp"

namespace Forth
{
	using MaybeToken = boost::optional<double>;
	using MaybeDouble = boost::optional<double>;
	
	MaybeDouble stonum(const std::string& str, size_t *pos = 0) noexcept
	{
		double result;
		bool fail = false;
		
		try
		{
			result = std::stod(str, pos);
		}
		// We only try to catch the exceptions stod will throw
		catch (std::invalid_argument)
		{
			fail = true;
		}
		catch (std::out_of_range)
		{
			fail = true;
		}
	
		return MaybeDouble(!fail, result);
	}
	
	auto is_whitespace = [](char c)
	{ 
		using namespace std;
		
		static unordered_set<char> whitespace {
			' ', '\t' };
			
		return whitespace.find(c) != whitespace.end();
	};
	
	auto is_not_whitespace = [](char c)
	{
		return !is_whitespace(c);
	};
	
	auto is_newline = [](char c)
	{
		using namespace std;
		
		static unordered_set<char> newline {
			'\n', '\r' };

		return newline.find(c) != newline.end();
	};		
	
	void drop_whitespace(std::istream &inp)
	{
		while (inp)
			if (is_whitespace(inp.peek())) inp.get();
			else return;
	}
	
	MaybeToken nextToken(std::istream &inp, bool &newlined)
	{
		// change design to use getline?
		
		using namespace std;
		// eliminate whitespace prior
		drop_whitespace(inp);
		
		// make sure next character is not a newline
		if (is_newline(inp.peek()))
		{
			newlined = true;
			return MaybeToken(false, 0.0);
		}
		
		// skip over to the next space and copy the interveneing characters into buffer
		string buf;
		copy_if(inp.begin(), inp.end(), back_inserter(buf), is_not_whitespace);
		
		// test for it being a double
		MaybeDouble d = stonum(buf);
		
		if (!d)
		{
			return MaybeToken(false, d);
		}
		else return d;
	}
	
	void printStack(std::stack<double> &s)
	{
		using namespace std;
		
		cout << "Elements in stack: " << s.size() << endl;
	}
	
	bool executeForth(std::istream &inp)
	{
		using namespace std;
		
		cout << "ok." << endl;
		
		MaybeDouble d1;
		double d;
		stack<double> s;
		bool newline = false;
		
		while (inp)
		{
//			inp >> d;
			d1 = nextToken(inp, newline);
			if (d1)
			{
				s.push(d.get());
			}
			printStack(s);
		}		
		
		return true;	
	}
}