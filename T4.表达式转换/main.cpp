#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include "Stack.h";

using namespace std;

bool isDigit(string s)
{
	//compile a Regex pattern to match floating-point numbers.
	regex pattern("^(\\-|\\+)?(\\d+)(\\.\\d+)?$");
	if (regex_match(s, pattern)) {
		return true;
	}
	else
		return false;
}

bool isOperator(const char& c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
		return true;
	else
		return false;
}

int getWeight(const char& op)
{
	if (isOperator(op)) 
	{
		int weight;
		switch (op)
		{
		case('+'):
		case('-'):
			weight = 1;
			break;
		case('*'):
		case('/'):
			weight = 2;
			break;
		case('('):
			weight = 0;
		}
		return weight;
	}
}

void convertToProfix(string str)
{
	// define a stack to store operator
	Stack<char> Opstack;
	stringstream ss;
	ss << str;
	string s;
	// use stringstream to make the input string to several strings divided by blanks
	while(ss>>s)
	{
		char op = s[0];
		// if it's a number just output it ( and delete the first '+' )
		if (isDigit(s)) {
			if (s[0] == '+') {
				s = s.erase(0, 1);
			}
			cout << s << " ";
		}
		// if it's a operator, make comparation
		else if (isOperator(op))
		{
			switch (op)
			{
			case('('):
				Opstack.push(op);
				break;
			case(')'):
				while (Opstack.getTop() != '(' && !Opstack.isEmpty())
				{
					cout << Opstack.pop() << " ";
				}
				if (Opstack.isEmpty()) {
					cerr << "括号不匹配！";
					exit(1);
				}
				else {
					Opstack.pop();
					break;
				}
			case('+'):
			case('-'):
			case('*'):
			case('/'):
				//  if operator's weight is heavier than the top element's, push it into the stack
				if (getWeight(op) > getWeight(Opstack.getTop()) || Opstack.isEmpty())
				{
					Opstack.push(op);
				}
				//  else will pull the top element out of stack
				else
				{
					while (getWeight(op) <= getWeight(Opstack.getTop()) && (!Opstack.isEmpty()))
					{
						cout << Opstack.pop() << " ";
					}
					Opstack.push(op);
				}
				break;
			}
		}
	}
	Opstack.print();
}

int main()
{
	string s;
	getline(cin, s);
	convertToProfix(s);
}
