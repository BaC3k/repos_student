#include "stdafx.h"
#include <iostream>
#include <cstdlib>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "RUSSIAN");
	int A, B, a, b, c, del, x, i;
	double y;
	cout << "Введите границу A \n";
	cin >> A;
	cout << "\nВведите границу B \n";
	cin >> B;
	cout << "\nВведите шаг del \n";
	cin >> del;
	cout << "\nВведите коэффициент a \n";
	cin >> a;
	cout << "\nВведите коэффициент b \n";
	cin >> b;
	cout << "\nВведите коэффициент c \n";
	cin >> c;
	cout << "\nЦикл for\n";
	x = A;
	for (x = A; x <= B; x = x + del)
	{
		if (x + c < 0 && a != 0)
		{
			y = -a * x*x*x - b;
			cout << "F1: при x=" << x << ", y=" << y << endl;
		}
		if (x + c > 0 && a == 0)
		{
			y = (x - a)*(x - c);
			cout << "F2: при x=" << x << ", y=" << y << endl;
		}
		else
		{
			y = x * c + x * b;
			cout << "F3: при x=" << x << ", y=" << y << endl;
		}
	}
	//Конец цикла for


	x = A;
	cout << "\nЦикл while\n";
	while (x <= B)
	{
		if (x + c < 0 && a != 0)
		{
			y = -a * x*x*x - b;
			cout << "F1: при x=" << x << ", y=" << y << endl;
			x = x + del;
		}
		if (x + c > 0 && a == 0)
		{
			y = (x - a)*(x - c);
			cout << "F2: при x=" << x << ", y=" << y << endl;
			x = x + del;
		}
		else
		{
			y = x * c + x * b;
			cout << "F3: при x=" << x << ", y=" << y << endl;
			x = x + del;
		}
	}                               //Конец цикла while




	x = A;

	cout << "\nЦикл do\n";
	do
	{
		if (x + c < 0 && a != 0)
		{
			y = -a * x*x*x - b;
			cout << "F1: при x=" << x << ", y=" << y << endl;
			x = x + del;
		}
		if (x + c > 0 && a == 0)
		{
			y = (x - a)*(x - c);
			cout << "F2: при x=" << x << ", y=" << y << endl;
			x = x + del;
		}
		else
		{
			y = x * c + x * b;
			cout << "F3: при x=" << x << ", y=" << y << endl;
			x = x + del;
		}
	} while (x <= B);

	system("pause");
	return 0;
}