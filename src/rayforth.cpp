
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
#include <sstream>

#include <boost/variant.hpp>
#include <boost/variant/get.hpp>
#include <boost/variant/static_visitor.hpp>

#include "forth.hpp"
#include "forth_words.hpp"

#include "linear_algebra.hpp"

namespace Forth
{
	// All of the words defined
	std::map<std::string, std::function<Status(Stack &)>> words
	{
		{"+", add},
		{"-", minus},
		{"*", product},
		{"/", divide},
		{"%", mod},
		{".", print},
		{"cr", cr},
		{"swap", swap},
		{"drop", drop},
		{"vec3", vec3},
		{"bye", bye},
		{".s", print_stack},
		{"make-sphere", makeSphere},
		{"make-triangle", makeTriangle},
		{"render-scene", renderScene},
	};
	
	// This defines what to do with each kind of token
	struct _process : public boost::static_visitor<Status>
	{
		Stack &stack;	
		
		_process(Stack &s) : stack(s) {} 
		
		Status operator()(double d)  const
		{
			push(stack, d);
//			stack.push_back(d);
//			return true;			
			return std::make_tuple(true, "");
		}
		
		Status operator()(std::string s) const
		{
//			stack.push_back(s);
			push(stack, s);
			return std::make_tuple(true, "");
//			return true;
		}
		
		Status operator()(Symbol s) const
		{

			try 
			{
				Stack backup = stack;
				
				auto n = words.at(s.name);
				Status x = n(stack);
				
				if (std::get<0>(x) == false)
				{
					stack = backup; // restore stack
				}
				
				return x;
				
//				return stack;
			}
			catch (std::out_of_range)
			{
				std::stringstream ss;
				
				ss << "\nRuntime Error: " << s.name << " not found in dictionary.";
				
				std::string str = ss.str();

				return std::make_tuple(false, str);
			}
		}
	};
	
	struct ForthMachine
	{
		Stack stack {};
		
		void printStack() const
		{
			int i = stack.size();

			for (Generic g : stack)
			{
				std::cerr << i << "  ";
				boost::apply_visitor(echoTypes(std::cerr), g);
				i--; std::cerr << std::endl;
			}
			std::cerr << std::endl;
		}
		
		// Proxy over to the real processing
		Status process(Token &g)
		{
			return boost::apply_visitor( _process(stack), g );
		}
	};
	
	
	bool executeForth(std::istream &inp)
	{
		using namespace std;
		
		vector<Token> ts;
		
		Stack stack;
		
		ForthMachine fm, saved;	// the stack will be saved for restoration if any problems occur in processing
		
		string s;
		while (getline(inp, s))
		{
			saved = fm;
			
			ts = tokenize(s);									// 1. Tokenize
			
			for (Token t : ts)									// 2. For Each Token
			{
				Status status = fm.process(t);					//		Execute
				
				if (get<0>(status) == false) // error occurred	// 		Check for some error
				{
					std::cerr << get<1>(status) << std::endl;	//		Output the debug info
					std::cerr << "Stack trace: " << std::endl;
					fm.printStack();
					
					fm = saved;									//		Restore the Stack
					
					std::cerr << "stack restored." << std::endl;
					break;
				}
				else
					if (get<1>(status) == "bye")				//		Check for user exit
					{
						break;
					}	
			}
			cerr << "  ok" << endl;
		}
		
		fm.printStack();
		
		return true;	
	}
}