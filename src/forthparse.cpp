
#include <map>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>

#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

#include "forth.hpp"

namespace Forth
{
	// All of the states
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

		//symbols
		symbol_char,
		symbol,

	};

	// All the states and names
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

		{	State::symbol_char, "symbol_char" },
		{	State::symbol, "symbol" },
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

	bool isPrintableButNotNumber(char c)
	{
		return (c >= 32 && c < '0') || (c > '9' && c < 127);
	}

	bool isNarrowPrintable(char c)
	{
		return isPrintable(c) && !isSign(c) && !isDigit(c) && !isQuote(c)
			&& !isDecimal(c);
	}

	bool isNotDigitButPrintable(char c)
	{
		return isPrintable(c) && !isDigit(c);
	}

	bool isNotDigitOrExponentButPrintable(char c)
	{
		return isPrintable(c) && !isDigit(c) && (c != 'e') && (c != 'E');	
	}

	using Predicate = bool(*)(char);
	using StateTransferList = std::map<Predicate, State>;
	using TransferTable = std::map<State, StateTransferList>;

	// State machine description for transferring states
	TransferTable table 
	{
		{ State::neutral, 
			{	
				{ isSign, State::sign },
				{ isDigit, State::digit_sequence },
				{ isDecimal, State::decimal_before_digits },
				{ isSpace, State::neutral },
				{ isQuote, State::string_start },
				{ isNarrowPrintable, State::symbol_char }

			} },
		{ State::sign, 
			{
				{ isDigit, State::digit_sequence },
				{ isDecimal, State::decimal_before_digits },
				{ isNotDigitButPrintable, State::symbol_char },
				{ isSpace, State::symbol }
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
				{ isExponent, State::exponent },
				{ isNotDigitOrExponentButPrintable, State::symbol_char },
				{ isSpace, State::symbol }
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
			}},
		{ State::symbol_char,
			{
				{ isPrintable, State::symbol_char },
				{ isSpace, State::symbol }
			}}
		};

//	Should add something like this to help processing
//	Token operation(string &buffer, char c)	

	// Processes the state machine description above with special handling
	struct Parser
	{
		TransferTable t;
		State state = State::neutral;
		std::string buffer = "";
		size_t index = 0;
		bool debug = false;

		Parser(TransferTable t_, bool d = false) : t(t_), debug(d) {};

		Token operator()(char c)
		{
			bool fail = true;
			++index;
			
			if (debug)
				std::cout << names.at(state) << " -> ";

			try
			{
				StateTransferList st = t.at(state);

				for (auto i = begin(st); i != end(st); ++i)
				{
					if (i->first(c))
					{	
						state = ((*i).second);
						if (state != State::symbol && state != State::neutral)
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

			if (debug)
			{
				std::cout << names.at(state) << std::endl;
				std::cout << " buffer: " << buffer << std::endl;
			}

			if (state == State::number)
			{
				// This will crash the program if there is an invalid number passed 
				// to it.
				double d = stod(buffer);
				buffer = "";
				state = State::neutral;
				return d;
			}

			if (state == State::string)
			{
				// Remove the quotes surrounded by it.
				std::string d = buffer.substr(1, buffer.size() - 2);
				buffer = "";
				state = State::neutral;
				return d;
			}

			if (state == State::symbol)
			{
				std::string d = buffer;
				Symbol s = { d };
				buffer = "";
				state = State::neutral;

				return s;
			}

			if (fail)
			{
				throw std::string("unfortunate.");
			}


			return false;
		}
	};
	
	// String in, Tokens out
	std::vector<Token> tokenize(std::string const &s, bool debug)
	{
		using namespace std;
		
		string str = s + "  ";
	
		if (debug)
			cout << "Parsing: >>" << s << "<<" << endl;
		
		vector<Token> t;
		
		// Runs the string through the state machine a character at a time
		transform(begin(str), end(str), back_inserter(t), Parser(table));
		
		// Remove any instances of bool that we don't need
		vector<Token> trimmed;
		for (Token s : t)
		{
			if (s.which() != 0)
			{
				trimmed.push_back(s);
			}
		}
		
		if (debug)
		{
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
				if (s.which() == 3)
				{
					cout << "Symbol: " << get<Symbol>(s).name << endl;
				}
			}
		}
		
		return trimmed;			
	}
	
			
			



	
	
}