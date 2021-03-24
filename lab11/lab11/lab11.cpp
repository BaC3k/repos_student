// lab11.cpp: определяет точку входа для консольного приложения.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define N 256
#define M 8

void changedec(char*, int&);

char* insert(char* s, const char* s1, unsigned n)
{
	unsigned lenS = strlen(s);
	unsigned lenS1(strlen(s1));

	memmove(s + n + lenS1, s + n, lenS - n + 1);
	memcpy(s + n, s1, lenS1);

	return s;
}

void strdel(char* str, int pos, int n)
{
	int i, j;
	for (j = 0; j < n; j++)
	{
		for (i = pos; i < strlen(str); i++)
			str[i] = str[i + 1];
	}
}

char* hex_to_dec(char buf[])
{
	_itoa(strtol(buf, NULL, 16), buf, 10);
	return buf;
}


char* dec_to_hex(int b)
{
	char a[M + 1];
	a[0] = NULL;
	a[M] = 0;
	int i;
	for (i = M - 1; i >= 0; i--, b = b / 16)
		a[i] = (b % 16 < 10) ? b % 16 + '0' : b % 16 - 10 + 'A';
	return a;
}

void changedec(char buf[], int& i)
{
	char buf3[N], buf2[N];
	int k = 0;
	while (buf[i] >= '0' && buf[i] <= '9' && !(buf[i] == '0' && buf[i + 1] == 'x'))
	{
		buf2[k] = buf[i];

		i = i + 1;
		k++;
	}
	strcpy(buf3, dec_to_hex(atoi(buf2)));
	strdel(buf, i - k, k);
	while (buf3[0] == '0')
		strdel(buf3, 0, 1);
	insert(buf3, "0x", 0);
	insert(buf, buf3, i - k);
	i = i + strlen(buf3) - k-1;
}

void func(char buf[])
{
	int i, j, k = 0, flag = 1;
	char buf1[N];
	for (i = 0; i < strlen(buf); i++)
	{

		if (buf[i] == '0' && buf[i + 1] == 'x')   //если 16ричное
		{
			while ((buf[i + k + 2] >= '0' && buf[i + k + 2] <= '9') || (buf[i + k + 2] >= 'A' && buf[i + k + 2] <= 'F'))
			{
				buf1[k] = buf[i + k + 2];  //записываем 16чное число без 0х в буф1
				k++;
			}

			strdel(buf, i, k + 2);
			insert(buf, hex_to_dec(buf1), i);

			i = i + strlen(buf1); //переводим каретку на позицию после нашего числа

			k = 0;
		}
		else if (buf[i] >= '0' && buf[i] <= '9')
		{


			changedec(buf, i);

		}

	}

	j = atoi(buf1);

	printf("%s\n", buf);

}

int main()
{
	FILE* input = fopen("input11.txt", "rt");
	int i = 0;
	char buf[N];

	if (input != NULL)
	{
		printf("FILE OPENED\n");
		FILE* output = fopen("output11.txt", "w+");

		while (fgets(buf, N, input) != NULL) //читаем строки пока не конец файла
		{

			func(buf);
			fputs(buf, output);
		}
		if (!feof(input))
			printf("READING ERROR");
		fclose(input);
		fclose(output);
	}
	else
		printf("FILE NOT FOUND");

	getchar();

	return 0;
}




