#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 256


int main()
{
	FILE* input = fopen("input.txt", "rt");
	unsigned int i = 0, maxlength = 0, minlength = 0, wlength = 0, wcounter = 0, minwpos = 0, maxwpos = 0, flag = 1;
	char c;
	char* word[100];
	char* max_w, * min_w;

	if (input != NULL)
	{
		printf("FILE OPENED\n");
		while (c = fgetc(input) != EOF)
		{

			if (c == ' ' || c == '\0')
			{
				if (flag)
				{
					flag = 0;
					minlength = wlength;
				}


				if (wlength > maxlength)
				{
					max_w = word[i];
					maxlength = wlength;
				}

				if (wlength < minlength)
				{
					min_w = word[i];
					minlength = wlength;
				}

				wcounter++;
				wlength = 0;
				i++;
			}
			word[i] = word[i] + c;
			wlength++;
		}
		printf("word_counter = %d\n", &wcounter);
		printf("max_length= %d\n max_word %s\n", &maxlength, max_w);
		printf("min_length %d\n min_word %s\n", &minlength, min_w);
		fclose(input);
	}
	else
		printf("File is not executed");
	system("cls");
	getchar();

	return 0;
}