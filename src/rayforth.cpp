
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


namespace Forth
{
	// bool if no token,
	// double if it is a double
	using Token = boost::variant<bool, double>;
	
	enum struct State
	{
		neutral,
		end,
		sign, 
		digit_sequence,
		decimal_after_digits,
		decimal_before_digits,
		exponent,
		digit_sequence_after_decimal,
		exponent_sign,
		exponent_digit_sequence,
		fail
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
		{	State::fail, "fail" }
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

	using Predicate = bool(*)(char);
	using StateTransferList = std::map<Predicate, State>;
//	using StateTransferList = std::list<StateTransfer>;
	using TransferTable = std::map<State, StateTransferList>;

	TransferTable table 
	{
		{ State::neutral, 
			{	
				{ isSign, State::sign },
				{ isDigit, State::digit_sequence },
				{ isDecimal, State::decimal_before_digits },
				{ isSpace, State::neutral }
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
			} } };
			
	struct Parser
	{
		TransferTable t;
		State state = State::number_start;
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
				std::cout << "Inconsistent State at index " << 0 << std::endl;
			}
			
			std::cout << names.at(state) << std::endl;
			std::cout << " buffer: " << buffer << std::endl;

			if (state == State::number)
			{
				double d = stod(buffer);
				buffer = "";
				state = State::number_start;
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
		
				
	struct NumberEval
	{
		State state = State::number_start;
		std::string buffer = "";
		
		
		Token operator()(char c)
		{
			using namespace std;
			
			switch (state)
			{
				case State::number_start:
					buffer = "";
					
					if (isSign(c))
					{
						buffer += c;
						state = State::sign;
					} else if (isDigit(c))
					{
						buffer += c;
						state = State::digit_sequence;
					} else if (c == '.')
					{
						buffer += c;
						state = State::decimal_before_digits;
					}else {
						// nothing matched, ERROR
						state = State::fail;
					}
					
					cout << "number start, buffer: " << buffer << endl;
					return false;
				
				case State::end:
					// if we have reached this point, we have a decimal number
					// here!
				{	
					if (buffer == "") return false;
					double d = stod(buffer); // this can throw!
					cout << "Have a double: " << d << endl;
					buffer = "";
					return d;
				}
				case State::sign:
					if (isDigit(c))
					{
						buffer += c;
						state = State::digit_sequence;
					} else if (c == '.')
					{
						buffer += c;
						state = State::decimal_before_digits;
					}else {
						// nothing matched, ERROR
						state = State::fail;
					}
					cout << "sign, buffer: " << buffer << endl;
					return false;		
					
				case State::digit_sequence:
					if (isDigit(c))
					{
						buffer += c;
						// keep state
					} else if (c == '.')
					{
						buffer += c;
						state = State::decimal_after_digits;
					} else if (isExponent(c))
					{
						buffer += c;
						state = State::exponent;
					} else if (isspace(c))
					{
						// do not add to buffer
						state = State::end;
					}else {
						// nothing matched, ERROR
						state = State::fail;
					}
					cout << "digit_sequence, buffer: " << buffer << endl;		

					return false;
				
				
				case State::decimal_after_digits:
					if (isDigit(c))
					{
						buffer += c;
						state = State::digit_sequence_after_decimal;
					} else if (isExponent(c))
					{
						buffer += c;
						state = State::exponent;
					} else if (isspace(c))
					{
						// do not add to buffer
						state = State::end;
					} else {
						// nothing matched, ERROR
						state = State::fail;
					}
					cout << "decimal_after_digits, buffer: " << buffer << endl;		
					return false;					

				
				case State::decimal_before_digits:
					if (isDigit(c))
					{
						buffer += c;
						state = State::digit_sequence_after_decimal;
					} else if (isExponent(c))
					{
						buffer += c;
						state = State::exponent;
					} /*else if (isspace(c))
					{
						// do not add to buffer
						state = State::end;
					} */else {
						// nothing matched, ERROR
						state = State::fail;
					}
					cout << "decimal_before_digits, buffer: " << buffer << endl;		
					
					return false;
				
				case State::exponent:
					if (isDigit(c))
					{
						buffer += c;
						state = State::exponent_digit_sequence;
					} else if (isSign(c))
					{
						buffer += c;
						state = State::exponent_sign;
					}else {
						// nothing matched, ERROR
						state = State::fail;
					}
					cout << "exponent, buffer: " << buffer << endl;		
					
					return false;

				
				case State::digit_sequence_after_decimal:
					if (isDigit(c))
					{
						buffer += c;
						state = State::digit_sequence_after_decimal;
					} else if (isExponent(c))
					{
						buffer += c;
						state = State::exponent;
					} else if (isspace(c))
					{
						// do not add to buffer
						state = State::end;
					} else {
						// nothing matched, ERROR
						state = State::fail;
					}
					cout << "digit_sequence_after_decimal, buffer: " << buffer << endl;		
					
					return false;
				
				case State::exponent_sign:
					if (isDigit(c))
					{
						buffer += c;
						state = State::exponent_digit_sequence;
					}else {
						// nothing matched, ERROR
						state = State::fail;
					}
					
					cout << "exponent_sign, buffer: " << buffer << endl;		
					return false;
				
				case State::exponent_digit_sequence:
					if (isDigit(c))
					{	
						buffer += c;
						state = State::exponent_digit_sequence;
					} else if (isspace(c))
					{
						// do not add to buffer
						state = State::end;
					} else {
						// nothing matched, ERROR
						state = State::fail;
					}

					cout << "exponent_digit_sequence, buffer: " << buffer << endl;		
					return false;
					
					
				default:
					state = State::fail;
					cout << "fail state, buffer: " << buffer << endl;
			}	
			return true;
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
				cout << "Number: " << s.get<double>(s) << endl;
			}
		}
				
		
	/*	cout << "ok." << endl;
		
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
	*/	
		return true;	
	}
}