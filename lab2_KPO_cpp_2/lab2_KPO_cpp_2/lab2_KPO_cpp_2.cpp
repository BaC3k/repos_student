#include "pch.h"

using namespace System;
#include "iostream"
ref class Stack
{
	static int MaxId;
	String^ StackId;
	static int MaxSize;
	int nxt_elem;
	array<int>^ ST;

public: Stack(String^ mSize)
{
	MaxSize = ::Convert::ToInt32(mSize);
	ST = gcnew array<int>(MaxSize);
	MaxId++;
	nxt_elem = 0;
	StackId = ::Convert::ToString(MaxId);
	Console::WriteLine("Создан стек " + StackId + "!");
};

	  void push(int c)
	  {
		  if (nxt_elem < MaxSize)
			  ST[nxt_elem++] = c;
		  else Console::WriteLine("список переполнен!");
	  }

	  int pop()
	  {
		  if (nxt_elem > 0)
			  return ST[--nxt_elem];
		  else
		  {
			  Console::WriteLine("Стек пуст!");
			  return -1;
		  }
	  }
};

int main(array<String^>^ args)
{
	int tmp;
	Stack^ vs;//1
	Console::WriteLine("Создать стек?");
	if (Console::ReadLine() == "да")
	{
		Console::WriteLine("какой глубины?");
		vs = gcnew Stack(Console::ReadLine()); //1
	}
	else return 0;
	String^ s;
	do
	{
		Console::WriteLine("Что сделать?");
		s = Console::ReadLine();
		if (s == "заложить")
		{
			Console::WriteLine("Что?");
			vs->push(Convert::ToInt32(Console::ReadLine()));
		};
		if (s == "достать")
		{
			Console::WriteLine(vs->pop());
		};
	} while (s != "");
}
