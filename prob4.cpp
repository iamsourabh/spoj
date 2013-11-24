#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <stack>
#include <map>

using namespace std;

struct Priority
{
	int inStackPriority;
	int  inputPriority;

	Priority()
	{
		inStackPriority = -1;
		inputPriority   = -1;
	}

	Priority(int stP, int inP) : inStackPriority(stP), inputPriority(inP)
	{
	}
};


std::list<string> ParseInput()
{
	std::list<string> infixList;
	string line;
	stringstream buffer;
	std::getline(std::cin, line);

	int numInputs = 0;
	buffer << line;
	buffer >> numInputs;

	while(numInputs--)
	{
		std::getline(std::cin, line);
		infixList.push_back(line);
	}

	return infixList;
	
}

string ConvertInfixToPostfix(string infixStr)
{
	std::map<char, Priority> opPriorityMap;
	opPriorityMap['('] = Priority(0, 6);
	opPriorityMap['+'] = Priority(1, 1);
	opPriorityMap['-'] = Priority(2, 2);
	opPriorityMap['*'] = Priority(3, 3);
	opPriorityMap['/'] = Priority(4, 4);
	opPriorityMap['^'] = Priority(5, 6);
	
	string postfixStr;
	std::stack<char> operatorStack;
	std::string::iterator infixIter = infixStr.begin();
	
	while(infixIter != infixStr.end())
	{
		if(opPriorityMap.find(*infixIter) != opPriorityMap.end())
		{
			if(operatorStack.empty())
			{
				operatorStack.push(*infixIter);
			}
			else
			{
				while(!operatorStack.empty())
				{
					char topOp = operatorStack.top();
					
					if(opPriorityMap[topOp].inStackPriority >= 
						opPriorityMap[*infixIter].inputPriority)
					{
						//pop and append to output
						postfixStr.push_back(topOp);
						operatorStack.pop();
					}
					else
					{
						break;
					}
				}

				operatorStack.push(*infixIter);
			}
		}
		/*else if(*infixIter == '(')
		{
			operatorStack.push(*infixIter);
		}*/
		else if(*infixIter == ')')
		{
			while(!operatorStack.empty())
			{
				char op = operatorStack.top();
				if(op == '(')
				{
					operatorStack.pop();
					break;
				}
				else
				{
					operatorStack.pop();
					postfixStr.push_back(op);
				}
			}
		}
		else
		{
			//it is an operand append directly to output
			postfixStr.push_back(*infixIter);
		}
		infixIter++;
	}

	while(!operatorStack.empty())
	{
		char topOp = operatorStack.top();
		operatorStack.pop();
		postfixStr.push_back(topOp);
	}

	return postfixStr;	
}

int main()
{
	
	std::list<string> exprList = ParseInput();
	std::list<string>::iterator iter = exprList.begin();

	for(; iter != exprList.end(); ++iter)
	{
		string postfixExpr = ConvertInfixToPostfix(*iter);
		cout << postfixExpr << endl;
	}

	return 0;
}
