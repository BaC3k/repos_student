#include "pch.h"
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

template <class T> class Stack
{
	int MaxSize;
	T* ST[100];
	int top = 0;

public: Stack(int tmpMaxSize)
{
	MaxSize = tmpMaxSize;
	for (int i = 0; i < MaxSize; i++)
	{
		ST[i] = new T;
	}

	cout << "Создан стек " << endl;
}

public: void push(T c)
{
	if (top < MaxSize)
		*ST[top++] = c;
	else printf("Стек переполнен!");
}

public: T pop()
{
	if (top > 0)
		return *ST[--top];

	else
	{
		printf("Стек пуст!");
		return "";
	}
}

};

void main()//int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);

	string r;
	Stack<string>* stack;
	int maxSize;

	cout << "Создать стек?" << endl;
	cin >> r;

	if (r == "да")
	{
		cout << "Какой глубины?" << endl;
		cin >> maxSize;
		stack = new Stack<string>(maxSize);
	}
	else return;

	string s;

	do
	{
		cout << "Что сделать?" << endl;
		cin >> s;
		if (s == "заложить")
		{
			cout << "Что?" << endl;
			cin >> r;
			stack->push(r);
		};
		if (s == "достать")
		{
			cout << stack->pop() << endl;
		};
	} while (s != "Х");
}