// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <cstdlib>
using namespace std;
int main()
{
	const int s = 3;
	int x[s] = { 1,2,3 };
	for (int i = 0; i < s; i++)
	{
		cout << x[i] << "\t";
	}
    
}
