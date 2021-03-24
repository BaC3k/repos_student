
#include <stdio.h>
#include <iostream>
#include <limits.h>
#define SIZE 15
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int min_r[SIZE]; // ����������� ����������
	int S[SIZE]; // ���������� ������� 
	int ne_orient[SIZE][SIZE];
	int temp, min_index, min_const;
	int begin_index, end_index;
	// ������������� ������� ������
	int graph[SIZE][SIZE] = {
	  // 0  1  2  3  4  5  6  7  8  9 10  11 12 13 14
		{0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //0
		{0, 0, 3, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //01
		{0, 0, 0, 0, 0, 6, 0, 8, 0, 0, 0, 0, 0, 0, 0}, //02
		{0, 0, 0, 0, 0, 2, 7, 0, 0, 0, 0, 0, 0, 0, 0}, //03
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //04
		{0, 0, 0, 0, 0, 0, 4, 1, 0, 0, 0, 0, 0, 0, 0}, //05
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 9, 0, 0, 0}, //06
		{0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 10},//07
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //08
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0}, //09
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 3, 2, 0}, //10
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, //11
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5}, //12
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3}, //13
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  //14
	};

	int head, tail;
	cout<<"������� ��������� �������: ";
	cin>>head;
	cout<<"������� �������� �������: ";
	cin>>tail;
	begin_index = head, end_index = tail;
	
	std::cout << "�������� ������� ������ �����:\n";
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			printf("%5d ", graph[i][j]);
		printf("\n");
	}
	
	for (int i = 0; i < SIZE; i++)
	{
		min_r[i] = INT_MAX; 
		S[i] = 1; // �������� ������� ��� ������������
	}
	min_r[begin_index] = 0;
	// ��� ���������
	do {
		min_index = INT_MAX;
		min_const = INT_MAX;
		for (int i = 0; i < SIZE; i++)
		{
			if ((S[i] == 1) && (min_r[i] < min_const))	// ���� ������� ��� �� ������ � ��� ������ min_const
			{
				min_const = min_r[i];
				min_index = i;
			}
		}
		
		if (min_index != INT_MAX)
		{
			for (int i = 0; i < SIZE; i++)
			{
				if (graph[min_index][i] > 0)
				{
					temp = min_const + graph[min_index][i];
					if (temp < min_r[i])
					{
						min_r[i] = temp;
					}
				}
			}
			S[min_index] = 0;
		}
	} while (min_index < INT_MAX);
	cout << "\n����������� ���������� �� " << head << " �� " << tail << ": ";
	cout << min_r[end_index] << endl;

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			ne_orient[i][j] = graph[i][j];
		}
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			if (ne_orient[i][j] != 0)
				ne_orient[j][i] = ne_orient[i][j];
		}

	// �������������� ����
	int path[SIZE];
	path[0] = tail; // ��������� ������� - �������� �������
	int k = 1;
	int weight = min_r[tail]; // ��� �������� �������

	while (tail != begin_index) // ���� �� ����� �� ��������� �������
	{
		for (int i = 0; i < SIZE; i++)
			if (ne_orient[tail][i] != 0)   // ���� ����� ����
			{
				int temp = weight - ne_orient[tail][i]; // ���������� ��� ���� �� ���������� �������
				if (temp == min_r[i]) // ���� ��� ������ � ������������
				{       
					weight = temp; 
					tail = i;      
					path[k] = i;
					k++;
				}
			}
	}

	cout << "���������� ����:\n";
	for (int i = k - 1; i >= 0; i--)
		cout << path[i] << ' ';


	// �������� �����
	cout << "\n\n����� ������������ ��������� ������ � ������� ��������� ����� ";
	cout << "\n�������� ����������������� ����: \n";
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			printf("%4d ", ne_orient[i][j]);
		printf("\n");
	}

	cout << "\n����������� �������� ������: \n";
	bool* visited = new bool[SIZE]; //����������
	memset(visited, false, sizeof(bool) * SIZE);
	visited[0] = true;
	for (int i = 0; i < SIZE - 1; i++) {
		int minx = -1, miny = -1;
		for (int j = 0; j < SIZE; j++) 
			if (visited[j])
				for (int k = 0; k < SIZE; k++) //������ �� ��������, ���������� ������ ������������ ����
					if (!visited[k] && ne_orient[j][k] > 0 && (miny == -1 || ne_orient[j][k] < ne_orient[miny][minx]))
					{
						miny = j;
						minx = k;
					}
		visited[minx] = true;
		cout << (miny) << "-" << (minx) << ':' << ne_orient[miny][minx] << '\t';
	}
	getchar();
	return 0;
}