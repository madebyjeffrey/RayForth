
#ifndef TYPED_ITERATOR
#define TYPED_ITERATOR

#include <boost/variant.hpp>
#include <string>
#include <sstream>
#include <limits>
#include <istream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <unordered_set>

namespace Forth
{
	
	struct Symbol
	{
		std::string text;
	};
	
	struct Error 
	{
		std::string text;	
	};
	
	using AtomicType = boost::variant<double, Symbol, std::string, Error>;
	
	auto is_space = [](char c) { return c == ' '; };
	auto is_not_space = [](char c) { return c != ' '; };
	auto is_whitespace = [](char c) 
	{ 
		using namespace std;
		
		static unordered_set<char> whitespace {
			'\n', '\r', ' ', '\t' };
			
		return whitespace.find(c) != whitespace.end();
	}
	
	template< class InputIterator, class OutputIterator, class UnaryPredicate >
	OutputIterator copy_until(InputIterator &first, InputIterator last,
		OutputIterator d_first,
		UnaryPredicate pred )
	{
		typename InputIterator::value_type i = *first;
		
		while (first != last)
		{
			if (!pred(i))
			{
				*d_first = i;
				++i;
			}
			else
				break;
		}
		
		return d_first;
	}
	
	class TypedIterator : std::iterator<std::input_iterator_tag,
										AtomicType>
	{
	private:
		std::istream *_i = nullptr;
		AtomicType *_prev = nullptr;
		bool _end;
		
		void drop_whitespace()
		{
			while (_i)
			{
				if (is_whitespace(_i.peek()) _.get();
				else return;
		}
			
	public:
		TypedIterator() : _end(true)
		{}
		
		TypedIterator(std::istream &i) : _i(i), _end(false)
		{
		}
		
		AtomicType operator *()
		{
			using namespace std;

			if (prev == nullptr)
			{
				drop_whitespace();
				string s;
				copy_until(_i.begin(), istream_iterator<char>(), 
				
				//
				auto p = find_if_not(_pos, istream_iterator<char>(), is_space);
					
				string s;
				copy_until(p, istream_iterator<char>(), back_inserter(s), is_space);
				// p is now the current position
		
			 	stringstream ss(s);
				double d = numeric_limits<double>::quiet_NaN();
				
				if (ss >> d)
				{
					prev = new AtomicType(d);
					return d;
				}
				else 
				{
					prev = new AtomicType(Error());
					return *prev;
				}
			}
			else return *prev;
		}
		
		// delete buffer
		TypedIterator & operator ++()
		{
			delete prev;
			prev = nullptr;
			return *this;
		}
		
		TypedIterator operator ++(int)
		{
			//typename TypedIterator::value_type value(*(*this));
			
			decltype(*this) temp(*this);
			
			++(*this);
			return temp;
		}
		
	};
}
/* operators:
concept: InputIterator
	A != b -> bool == !(a==b)
	
	*a -> value_type
	a->m -- (*a).m
	++a    It& (next item)
	a++    ++a
	*a++   return value_type, op: value_type t = *a; ++a; return t;
	
	*/

#endif