// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#define N 10 
#include "pch.h" 

int main()
{
	int a[N], i, min, max, sum;
	for (i = 0; i < N; i++) {
		a[i] = rand() % 50;
		printf("%3d", a[i]);
	}
	printf("\n");

	min = 0;
	max = 0;
	for (i = 1; i < N; i++) {
		if (a[i] < a[min]) min = i;
		else if (a[i] > a[max]) max = i;
	}
	printf("%3d, %3d\n", a[min], a[max]);

	if (min > max) {
		i = min;
		min = max;
		max = i;
	}

	sum = 0;
	for (i = min + 1; i < max; i++)
		sum += a[i];
	printf("%4d\n", sum);
}

