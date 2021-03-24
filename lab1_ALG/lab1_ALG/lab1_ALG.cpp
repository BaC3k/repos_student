#include "iostream"
#include "string.h"
#include "stdlib.h"
const int N = 20;
using namespace std;


void b_sort(char arr[], int n)
{
	int i = 0, j = 0;
	char c;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < (n - 1); j++)
			if (arr[j] > arr[j + 1])
			{
				c = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = c;
			}
	}
}

int alg_S(char arr[], int n, char key)
{
	int i = 0, counter = 0;
	for (i = 0; i < n; i++)
	{
		counter++;
		if (arr[i] == key)
			break;
	}
	cout << counter << " - iterations\n";
	return i < n  ? i : -1;
}

int alg_Q(char arr[], int n, char key)
{
	int i = 0, counter = 0;
	arr[n] = key;
	while (arr[i] != key)
	{
		counter++;
		i++;
	}
	cout << counter << " - iterations\n";
	return i <= n - 1 ? i : -1;
}

int alg_T(char arr[], int n, char key)
{
	int i = 0, counter = 0;
	b_sort(arr, n);
	arr[n] = CHAR_MAX;
	while (!(key <= arr[i]))
	{
		counter++;
		i++;
	}
	if (key == arr[i])
	{
		cout << counter << " - iterations\n";
		return i;
	}
	else
	{
		cout << counter << " - iterations\n";
		return -1;
	}
}

int alg_Binary(char arr[], int n, char key)
{
	b_sort(arr, n);
	int i = 0, i_0 = 0, i_n = n - 1, counter = 0; ;
	while (i_0 <= i_n)
	{
		counter++;
		i = abs((i_0 + i_n) / 2);
		if (key < arr[i])
			i_n = i - 1;
		else if (key == arr[i])
		{
			cout << counter << " - iterations\n";
			return i;
		}
		else i_0 = i + 1;
	}
	cout << counter << " - iterations\n";
	return -1;
}

int main()
{
	char arr[N + 1] =/*"abcdefghijklmnopqrst";*/{ 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t' };
	char key;
	int a;
	do
	{
		cout << "enter 0 to close the program\n";
		cin >> a;
		if (a != 0)
		{
			cout << "enter KEY\n";
			cin >> key;
			cout << "aslg_S element number " << alg_S(arr, N, key) << endl << endl;
			cout << "aslg_Q element number " << alg_Q(arr, N, key) << endl << endl;
			cout << "aslg_T element number " << alg_T(arr, N, key) << endl << endl;
			cout << "aslg_Binary element number " << alg_Binary(arr, N, key) << endl << endl;
		}
	} while (a != 0);
	system("pause");
	return 0;
}

