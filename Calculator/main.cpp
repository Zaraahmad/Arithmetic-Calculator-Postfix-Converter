#include <iostream>
#include <string>
#include <stdlib.h>
#include "Stack.h"
using namespace std;

int precedence(char optr1, char optr2 = '\0');
bool pushToStack(char optr1, char optr2, char top);
string infixToPostfix(string infix);
int evaluatePostfix(string postfix);

int main()
{
	string infix, postfix;
	int answer, choice;
	const int eval = 1,
			quit = 2;
	do{
		cout << endl << endl << "1. If you wish to convert infix expression to postfix.\n"
			 << "2. If you wish to quit the program\n";

		cin >> choice;
		while (choice < eval || choice > quit)
		{
			cout << "Please enter a valid choice i.e. either 1 or 2\n";
			cin.ignore();
			cin >> choice;
		}

		if (choice == eval){
			//system("cls");
			cout << "eval ";
			cin.ignore();
			getline(cin, infix);
			//cin.getline(infix, 100, '\n');

			try
			{
				postfix = infixToPostfix(infix);
				cout << "postfix: " << postfix << endl;
			}

			catch (string exceptionString)
			{
				cout << exceptionString;
			}

			answer = evaluatePostfix(postfix);
			cout << "Answer: " << answer << endl;
		}

	} while (choice != quit);
}

string infixToPostfix(string infix)
{
	char x; int prec;
	string postfix;
	Stack <char> operators(infix.size());
	for (int i = 0; i < infix.size(); i++)
	{
		//if x is an operand
		if (infix[i] >= '0' && infix[i] <= '9'){
			postfix = postfix + infix[i];
			postfix = postfix + ' ';
		}

		//if opening bracket is encoutered
		else if (infix[i] == '('){
			operators.Push(infix[i]);
			//cout << infix[i] << "pushed.\n";
		}

		//if closing bracket is encoutered
		else if (infix[i] == ')')
		{
			while (!operators.isEmpty() && operators.top() != '('){

				operators.Pop(x);


				if (x == 'i')
					postfix = postfix + "++ ";

				else if (x == 'd')
					postfix = postfix + "-- ";

				else
					postfix = postfix + x + ' ';
			}

			if (operators.isEmpty())
			{
				string exceptionStr = "Opening bracket not found.\n";
				throw exceptionStr;
			}

			else
				operators.Pop(x);
		}

		//if x is an operator
		else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
		{
			while (!operators.isEmpty() && !pushToStack(infix[i], infix[i + 1], operators.top())){

				if (operators.top() == 'i'){
					postfix = postfix + "++ ";
					operators.Pop(x);
				}

				else if (operators.top() == 'd'){
					postfix = postfix + "-- ";
					operators.Pop(x);
				}

				else{
					operators.Pop(x);
					postfix = postfix + x + ' ';	// operators.top();
				}

			}

			prec = precedence(infix[i], infix[i + 1]);
			if (prec == 1 && infix[i] == '+'){
				operators.Push('i');
				i++;
			}

			else if (prec == 1 && infix[i] == '-'){
				operators.Push('d');
				i++;
			}

			else
				operators.Push(infix[i]);
		}
	}

	//to empty stack
	while (!operators.isEmpty())
	{
		operators.Pop(x);
		if (x == 'i')
			postfix = postfix + "++ ";

		else if (x == 'd')
			postfix = postfix + "-- ";

		else
			postfix = postfix + x + ' ';
	}
	return postfix;
}

int evaluatePostfix(string postfix)
{
	int ans, right, left;
	Stack <int> operators(postfix.size());
	for (int i = 0; i < postfix.size(); i++){

		if (postfix[i] >= '0' && postfix[i] <= '9')
			operators.Push(postfix[i] - '0');

		else if (postfix[i] != postfix.size() - 1 && (postfix[i] == '+' && postfix[i + 1] == '+') || (postfix[i] == '-' && postfix[i + 1] == '-'))
		{
			operators.Pop(right);
			if (postfix[i] == '+')
				right++;
			else
				right--;
			operators.Push(right);
			i++;
		}

		else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/')
		{
			bool skipSwitch = false;
			operators.Pop(right);

			if (!operators.isEmpty())
				operators.Pop(left);
			else{
				ans = right * -1;
				skipSwitch = true;
			}

			if (!skipSwitch){
				switch (postfix[i])
				{
				case ('+') :
					ans = left + right;
					break;

				case '-':
					ans = left - right;
					break;

				case '*':
					ans = left * right;
					break;

				case '/':
					ans = left / right;
					break;

				}
			}

			operators.Push(ans);
		}

	}

	return operators.top();

}

int precedence(char optr1, char optr2)
{
	int prec;

	if ((optr1 == '+' && optr2 == '+') || (optr1 == '-' && optr2 == '-'))
		prec = 1;

	else if (optr1 == '*' || optr1 == '/')
		prec = 2;

	else if (optr1 == '+' || optr1 == '-')
		prec = 3;

	else
		prec = 4;

	return prec;
}

bool pushToStack(char optr1, char optr2, char top)
{
	bool status = false;
	int op = precedence(optr1, optr2);
	int tp;

	if (top == 'i' || top == 'd')
		tp = 1;
	else
		tp = precedence(top);

	if (op < tp)
		status = true;

	return status;
}
