#ifndef STACK_H
#define STACK_H
#include <iostream>
using namespace std;

template <class T>
class Stack
{
private:
	T *stackArr;
	int totalLen;
	int currentLen;

public:
	Stack()
	{
		stackArr = NULL;
		totalLen = 0;
		currentLen = 0;
	}

	Stack(int size)
	{
		stackArr = new T[size];
		totalLen = size;
		currentLen = 0;
	}

	Stack(const Stack &);

	const T top();
	void Push(T);
	void Pop(T &);
	bool isFull();
	bool isEmpty();

	void operator +(T);
	void operator -(T &);

	~Stack()
	{
		if (totalLen > 0)
			delete[] stackArr;
	}

};
#endif

template <class T>
Stack<T> ::Stack(const Stack &obj)
{
	if (obj.totalLen > 0)
		stackArr = new T[obj.totalLen];

	else
		stackArr = nullptr;

	totalLen = obj.totalLen;

	for (int count = 0; count < obj.currentLen; count++)
		stackArr[count] = obj.stackArr[count];

	currentLen = obj.currentLen;
}

template <class T>
const T Stack<T> :: top()
{
	return stackArr[currentLen - 1];
}

template <class T>
void Stack<T> ::Push(T item)
{
	if (isFull())
		cout << "The stack is Full.\n";

	else
	{
		currentLen++;
		stackArr[currentLen - 1] = item;
	}
}

template <class T>
void Stack<T> ::Pop(T &item)
{
	if (isEmpty())
		cout << "The stack is empty.\n";

	else
	{
		item = stackArr[currentLen - 1];
		currentLen--;
	}
}

template <class T>
bool Stack<T> ::isFull()
{
	bool status = false;
	if (currentLen == totalLen)
		status = true;

	return status;
}

template <class T>
bool Stack<T> ::isEmpty()
{
	bool status = false;
	if (currentLen == 0)
		status = true;

	return status;
}





template <class T>
void Stack<T>::operator + (T item)
{
	if (isFull())
		cout << "The stack is Full.\n";

	else
	{
		currentLen++;
		stackArr[currentLen - 1] = item;
	}
}

template <class T>
void Stack<T>::operator - (T &item)
{
	if (isEmpty())
		cout << "The stack is empty.\n";

	else
	{
		item = stackArr[currentLen - 1];
		currentLen--;
	}
}
