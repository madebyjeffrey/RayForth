
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


// All of these functions are fairly self explanable

namespace Forth
{
	Status add(Stack &stack)
	{
		using namespace boost;

		if (stack.size() < 2)
		{
			return std::make_tuple(false, "Stack underflow. + requires two numbers.");
		}

		try
		{
			double a1 = get<double>(stack.back()); stack.pop_back();
			double a2 = get<double>(stack.back()); stack.pop_back();
			stack.push_back(a1 + a2);	
		}
		catch (bad_get)
		{
			return std::make_tuple(false, "Data type mismatch. + requires two numbers.");
		}

		return std::make_tuple(true, "");
	}

	Status minus(Stack &stack)
	{
		using namespace boost;

		if (stack.size() < 2)
		{
			return std::make_tuple(false, "Stack underflow. - requires two numbers.");
		}

		try
		{
			double a1 = get<double>(pop(stack));
			double a2 = get<double>(pop(stack));
			push(stack, a1 - a2);	
		}
		catch (bad_get)
		{
			return std::make_tuple(false, "Data type mismatch. - requires two numbers.");
		}

		return std::make_tuple(true, "");
	}

	Status product(Stack &stack)
	{
		using namespace boost;

		if (stack.size() < 2)
		{
			return std::make_tuple(false, "Stack underflow. * requires two numbers.");
		}

		try
		{
			double a1 = get<double>(pop(stack));
			double a2 = get<double>(pop(stack));
			push(stack, a1 * a2);	
		}
		catch (bad_get)
		{
			return std::make_tuple(false, "Data type mismatch. * requires two numbers.");
		}

		return std::make_tuple(true, "");
	}

	Status divide(Stack &stack)
	{
		using namespace boost;

		if (stack.size() < 2)
		{
			return std::make_tuple(false, "Stack underflow. / requires two numbers.");
		}

		try
		{
			double a1 = get<double>(pop(stack));
			double a2 = get<double>(pop(stack));

			if (Math::feq(a2, 0.0))
			{
				return std::make_tuple(false, "Division by zero. / requires second parameter to be non-zero.");
			}

			push(stack, a1 / a2);	
		}
		catch (bad_get)
		{
			return std::make_tuple(false, "Data type mismatch. / requires two numbers.");
		}

		return std::make_tuple(true, "");
	}

	Status mod(Stack &stack)
	{
		using namespace boost;

		if (stack.size() < 2)
		{
			return std::make_tuple(false, "Stack underflow. % requires two numbers.");
		}

		try
		{
			double a1 = get<double>(pop(stack));
			double a2 = get<double>(pop(stack));

			if (Math::feq(a2, 0.0))
			{
				return std::make_tuple(false, "Division by zero. % requires second parameter to be non-zero.");
			}

			push(stack, fmod(a1, a2));	
		}
		catch (bad_get)
		{
			return std::make_tuple(false, "Data type mismatch. % requires two numbers.");
		}

		return std::make_tuple(true, "");
	}


	Status print(Stack &stack)
	{
		using namespace boost;

		if (stack.size() < 1) 
		{
			return std::make_tuple(false, "Stack underflow. . requires one object.");
		}

		Generic d = pop(stack); 

		// what does this throw?
		boost::apply_visitor(echo(std::cout), d);

		return std::make_tuple(true, "");
	}

	Status cr(Stack const &stack)
	{
		std::cout << std::endl;

		return std::make_tuple(true, "");
	}

	Status swap(Stack &stack)
	{
		if (stack.size() < 2)
		{
			return std::make_tuple(false, "Stack underflow. + requires two numbers.");
		}

		Generic a,b;
		a = pop(stack);
		b = pop(stack);

		push(stack, a);
		push(stack, b);

		return std::make_tuple(true, "");
	}

	Status drop(Stack &stack)
	{
		if (stack.size() < 1)
		{
			return std::make_tuple(false, "Stack underflow. drop requires one object.");	
		}

		pop(stack);

		return std::make_tuple(true, "");
	}

	Status bye(Stack &stack)
	{
		return std::make_tuple(true, "bye");
	}

	Status print_stack(Stack &stack)
	{
		for (Generic g : stack)
		{
			boost::apply_visitor(echo(std::cout), g);
			std::cout << " " << std::endl;
		}

		return std::make_tuple(true, "");	
	}
}
