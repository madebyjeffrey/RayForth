
#include <istream>
#include <iostream>
#include <stack>

//#include "TypedIterator.hpp"

namespace Forth
{
	
	void printStack(stack<double> &s)
	{
		cout << "Elements in stack: " << s.size() << endl;
	}
	
	bool executeForth(std::istream &inp)
	{
		using namespace std;
		
		cout << "ok." << endl;
		
		double d;
		stack<double> s;
		
		while (inp)
		{
			inp >> d;
			s.push(d);
			printStack(s);
		}		
		
		return true;	
	}
}