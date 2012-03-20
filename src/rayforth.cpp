
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


namespace Forth
{
	//struct Symbol
//	{
//		std::string name;	
//	};
	// bool if no token,
	// double if it is a double


	using Token = boost::variant<bool, double, std::string>; //, Symbol>;
	
	enum struct State
	{
		neutral,
		number,
		sign, 
		digit_sequence,
		decimal_after_digits,
		decimal_before_digits,
		exponent,
		digit_sequence_after_decimal,
		exponent_sign,
		exponent_digit_sequence,
		fail,
		
		// strings
		string_start,
		string_text,
		string_escape,
		string_escaped,
		string,
		
		// symbols
		//symbol_char,
//		symbol,
		
	};
	
	std::map<State, std::string> names
	{
		{ 	State::neutral, "neutral" },
		{	State::number,	"Number" },
		{	State::sign, "sign" },
		{	State::digit_sequence, "digit_sequence" },
		{	State::decimal_after_digits, "decimal_after_digits" },
		{	State::decimal_before_digits, "decimal_before_digits" },
		{	State::exponent, "exponent" },
		{	State::digit_sequence_after_decimal, "digit_sequence_after_decimal" },
		{	State::exponent_sign,	"exponent_sign" },
		{	State::exponent_digit_sequence, "exponent_digit_sequence" },
		{	State::fail, "fail" },
		
		{ 	State::string_start, "string_start" },
		{	State::string_text, "string_text" },
		{	State::string_escape, "string_escape" },
		{	State::string_escaped, "string_escaped" },
		{   State::string, "string" },
		
//		{	State::symbol_char, "symbol_char" },
//		{	State::symbol, "symbol" },
	};
	
	bool isDigit(char c)
	{
		return (c >= '0') & (c <= '9');
	}
	
	bool isSign(char c)
	{
		return (c == '+') | (c == '-');
	}
	
	bool isExponent(char c)
	{
		return (c == 'e') | (c == 'E');
	}
	
	bool isDecimal(char c)
	{
		return (c == '.');
	}
	
	bool isSpace(char c) 
	{
		return (c == ' ');
	}
	
	// is it a double quote?
	bool isQuote(char c)
	{
		return (c == '\"');
	}
	
	// is it printable, but not a backslash or double quote
	bool isPrintableRestricted(char c)
	{
		return (c != '\\' && c != '\"' && (c >= 32 && c < 127));
	}
	
	// is it printable, including backslash or double quote
	bool isPrintable(char c)
	{
		return (c >= 32 && c < 127);
	}
	
	bool isBackslash(char c)
	{
		return (c == '\\');
	}
	
//	bool isPrintableButNotNumber(char c)
//	{
//		return (c >= 32 && c < '0') || (c > '9' && c < 127);
//	}
	
/*	bool isNarrowPrintable(char c)
	{
		return isPrintable(c) && !isSign(c) && !isDigit(c) && !isQuote(c);
//			&& !isDecimal(c);
	}*/
/*	
	bool isNotDigitButPrintable(char c)
	{
		return isPrintable(c) && !isDigit(c);
	}
*/
	using Predicate = bool(*)(char);
	using StateTransferList = std::map<Predicate, State>;
	using TransferTable = std::map<State, StateTransferList>;

	TransferTable table 
	{
		{ State::neutral, 
			{	
				{ isSign, State::sign },
				{ isDigit, State::digit_sequence },
				{ isDecimal, State::decimal_before_digits },
				{ isSpace, State::neutral },
				{ isQuote, State::string_start }
			} },
		{ State::sign, 
			{
				{ isDigit, State::digit_sequence },
				{ isDecimal, State::decimal_before_digits }
			} },
		{ State::digit_sequence,
			{
				{ isDigit, State::digit_sequence },
				{ isExponent, State::exponent },
				{ isDecimal, State::decimal_after_digits },
				{ isSpace, State::number }
			} },
		{ State::decimal_after_digits,
			{
				{ isDigit, State::digit_sequence_after_decimal },
				{ isExponent, State::exponent },
				{ isSpace, State::number }
			} },
		{ State::decimal_before_digits,
			{	
				{ isDigit, State::digit_sequence_after_decimal },
				{ isExponent, State::exponent }
			} },
		{ State::digit_sequence_after_decimal,
			{
				{ isDigit, State::digit_sequence_after_decimal },
				{ isExponent, State::exponent },
				{ isSpace, State::number },
			} },
		{ State::exponent,
			{
				{ isSign, State::exponent_sign },
				{ isDigit, State::exponent_digit_sequence }
			} },
		{ State::exponent_sign,
			{
				{ isDigit, State::exponent_digit_sequence }
			} },
		{ State::exponent_digit_sequence,
			{
				{ isDigit, State::exponent_digit_sequence },
				{ isSpace, State::number }
			} } ,
			
		// strings
		{ State::string_start,
			{
				{ isPrintableRestricted, State::string_text },
			 	{ isQuote, State::string }
			} },
		{ State::string_text,
			{
				{ isPrintableRestricted, State::string_text },
				{ isBackslash, State::string_escape },
				{ isQuote, State::string }
			} },
		{ State::string_escape,
			{
				{ isPrintable, State::string_escaped },
			}},
		{ State::string_escaped,
			{
				{ isBackslash, State::string_escape },
				{ isPrintableRestricted, State::string_text },
				{ isQuote, State::string }
			}}
		};
			
	struct Parser
	{
		TransferTable t;
		State state = State::neutral;
		std::string buffer = "";
		size_t index = 0;
		
		Parser(TransferTable t_) : t(t_) {};
		
		Token operator()(char c)
		{
			bool fail = true;
			++index;
			
			std::cout << names.at(state) << " -> ";
			
			try
			{
				StateTransferList st = t.at(state);

				for (auto i = begin(st); i != end(st); ++i)
				{
					if (i->first(c))
					{	
						state = ((*i).second);
						buffer += c;
						fail = false;
						break;				// first match wins
					}
				}
			}
			
			catch (std::out_of_range)
			{
				std::cout << "Inconsistent State at index " << index << std::endl;
			}
			
			std::cout << names.at(state) << std::endl;
			std::cout << " buffer: " << buffer << std::endl;

			if (state == State::number)
			{
				double d = stod(buffer);
				buffer = "";
				state = State::neutral;
				return d;
			}
			
			if (state == State::string)
			{
				std::string d = buffer;
				buffer = "";
				state = State::neutral;
				return d;
			}

			if (fail)
			{
//				return false;	
				throw std::string("unfortunate.");
			}
			

			return false;
		}
	};
		
				
	
	void printStack(std::stack<double> &s)
	{
		using namespace std;
		
		cout << "Elements in stack: " << s.size() << endl;
	}
	
	bool executeForth(std::istream &inp)
	{
		using namespace std;
		
		
		
		string s;
		getline(inp, s);

		s += "  "; // some extra to flush out the State
				
		cout << "Parsing: >>" << s << "<<" << endl;
		
		list<Token> t;

//		transform(begin(s), end(s), back_inserter(t), NumberEval());
		transform(begin(s), end(s), back_inserter(t), Parser(table));
		
		list<Token> trimmed;
		for (Token s : t)
		{
			if (s.which() != 0)
			{
				trimmed.push_back(s);
			}
		}
		
		cout << "tokens found:" << endl;
		for (Token s : trimmed)
		{
			if (s.which() == 1)
			{
				cout << "Number: " << get<double>(s) << endl;
			}
			if (s.which() == 2)
			{
				cout << "String: " << get<string>(s) << endl;
			}
		}
				
		
		return true;	
	}
}