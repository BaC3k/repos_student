// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int i = 0, imax1 = 0, imax2 = 0;
	double max1,max2, arr[10];
	cout << "Введите элементы массива\n";
	cout << "arr["<<i<<"]=" ;
	cin >> arr[0];
	max1 = arr[0];
	max2 = arr[0];
	for (i = 1; i <= 9; i++)
	{
		cout << "arr[" << i << "]=";
		cin >> arr[i];
		if (max1 <= arr[i])
		{
			max1 = arr[i];
			imax1 = i;
		}
	}
	for (i = 1; i <= 9; i++)
	{
		if (max2<=arr[i] && i != imax1)
		{
			max2 = arr[i];
			imax2 = i;
		}
	}
	cout << "max1 = " << max1 << ", " << "индекс = " << imax1 << endl;
	cout << "max2 = " << max2 << ", " << "индекс = " << imax2 << endl;

	system("pause");
	return 0;
}