
#include <istream>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <unordered_set>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <list>
#include <utility>
#include <map>

#include <boost/variant.hpp>
#include <boost/variant/get.hpp>
#include <boost/variant/static_visitor.hpp>

#include "rayforth.hpp"
#include "rayforth_util.hpp"

#include "linear_algebra.hpp"

namespace Forth
{
	using Stack = std::vector<Generic>;
	
	Stack &&vec3(Stack &&stack)
	{
		using namespace boost;
		
		double z = get<double>(pop(stack));
		double y = get<double>(pop(stack));
		double x = get<double>(pop(stack));		
		
		Math::Vec3 v = Math::vec3(x,y,z);

		push(stack, v);

		return std::move(stack);
	}
	
	bool add(std::vector<Generic> &stack)
	{
		using namespace boost;
		if (stack.back().which() == 0)
		{
			double a1 = get<double>(stack.back()); stack.pop_back();
			double a2 = get<double>(stack.back()); stack.pop_back();
			stack.push_back(a1 + a2);	
			
			return true;
		}
		else
			return false;
	}
	
	bool print(std::vector<Generic> &stack)
	{
		using namespace boost;
		if (stack.size() == 0) return false;

		Generic d = stack.back(); stack.pop_back();
		
		boost::apply_visitor(echo(std::cout), d);
				
		return true;
	}
	
	bool cr(std::vector<Generic>&)
	{
		std::cout << std::endl;
		return true;
	}
	
	bool swap(std::vector<Generic>&s)
	{
		if (s.size() >= 2)
		{
			Generic a,b;
			a = s.back(); s.pop_back();
			b = s.back(); s.pop_back();
			
			s.push_back(a);
			s.push_back(b);
		}
		return true;
	}
	
	bool drop(std::vector<Generic>&s)
	{
		if (s.size() >= 1)
			s.pop_back();
		return true;
	}
	
	std::map<std::string, std::function<bool(std::vector<Generic>&)>> words
	{
		{"+", add},
		{".", print},
		{"cr", cr},
		{"swap", swap},
		{"drop", drop},
		{"vec3", vec3},
	};
	
	
	
	struct _process : public boost::static_visitor<bool>
	{
		std::vector<Generic> &stack;	
		
		_process(std::vector<Generic> &s) : stack(s) {} 
		
		bool operator()(double d)  const
		{
			stack.push_back(d);
			return true;			
		}
		
		bool operator()(std::string s) const
		{
			stack.push_back(s);
			return true;
		}
		
		bool operator()(Symbol s) const
		{
			try 
			{
				auto n = words.at(s.name);
				return n(stack);
				return false;
			}
			catch (std::out_of_range)
			{
				std::cerr << "\nRuntime Error: " << s.name << " not found in dictionary." << std::endl;
				
				return false;
			}
		}
	};
	
	struct ForthMachine
	{
		std::vector<Generic> stack;
		
		void printStack() const
		{
			std::cout << "Stack: " << stack.size() << " items" << std::endl;
			for (Generic g : stack)
			{
//				std::cout << g << std::endl;
				boost::apply_visitor(echo(std::cout), g);
			}
		}
		
		bool process(Token &g)
		{
			return boost::apply_visitor( _process(stack), g );
		}
	};
	
	using namespace std::placeholders;
	
	using testfunc = decltype(std::make_pair<double, double>);
	
	bool executeForth(std::istream &inp)
	{
		using namespace std;
		
		list<Token> ts;
		
		ForthMachine fm, saved;
		
		string s;
		while (getline(inp, s))
		{
			saved = fm;
			
			ts = tokenize(s);
			
			for (Token t : ts)
			{
				if (!fm.process(t))
				{
					// restore stack.
					fm = saved;
					std::cerr << "stack restored." << std::endl;
					break;
				}
			}
			cerr << "  ok" << endl;
		}
		
		fm.printStack();
		
		return true;	
	}
}