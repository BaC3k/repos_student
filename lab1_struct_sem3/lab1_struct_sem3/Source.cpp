
#include <stdio.h>
#include <iostream>
#include <limits.h>
#define SIZE 15
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int min_r[SIZE]; // минимальное расстояние
	int S[SIZE]; // посещенные вершины 
	int ne_orient[SIZE][SIZE];
	int temp, min_index, min_const;
	int begin_index, end_index;
	// Инициализация матрицы связей
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
	cout<<"Введите начальную вершину: ";
	cin>>head;
	cout<<"Введите конечную вершину: ";
	cin>>tail;
	begin_index = head, end_index = tail;
	
	std::cout << "Исходная матрица связей графа:\n";
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			printf("%5d ", graph[i][j]);
		printf("\n");
	}
	
	for (int i = 0; i < SIZE; i++)
	{
		min_r[i] = INT_MAX; 
		S[i] = 1; // Помечаем вершину как непройденную
	}
	min_r[begin_index] = 0;
	// Шаг алгоритма
	do {
		min_index = INT_MAX;
		min_const = INT_MAX;
		for (int i = 0; i < SIZE; i++)
		{
			if ((S[i] == 1) && (min_r[i] < min_const))	// Если вершину ещё не обошли и вес меньше min_const
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
	cout << "\nМинимальное расстояние от " << head << " до " << tail << ": ";
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

	// Восстановление пути
	int path[SIZE];
	path[0] = tail; // начальный элемент - конечная вершина
	int k = 1;
	int weight = min_r[tail]; // вес конечной вершины

	while (tail != begin_index) // пока не дошли до начальной вершины
	{
		for (int i = 0; i < SIZE; i++)
			if (ne_orient[tail][i] != 0)   // если связь есть
			{
				int temp = weight - ne_orient[tail][i]; // определяем вес пути из предыдущей вершины
				if (temp == min_r[i]) // если вес совпал с рассчитанным
				{       
					weight = temp; 
					tail = i;      
					path[k] = i;
					k++;
				}
			}
	}

	cout << "Кратчайший путь:\n";
	for (int i = k - 1; i >= 0; i--)
		cout << path[i] << ' ';


	// алгоритм Прима
	cout << "\n\nПоиск минимального остовного дерева с помощью алгоритма Прима ";
	cout << "\nИсходный неориентированный граф: \n";
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			printf("%4d ", ne_orient[i][j]);
		printf("\n");
	}

	cout << "\nМинимальное остовное дерево: \n";
	bool* visited = new bool[SIZE]; //Посещенные
	memset(visited, false, sizeof(bool) * SIZE);
	visited[0] = true;
	for (int i = 0; i < SIZE - 1; i++) {
		int minx = -1, miny = -1;
		for (int j = 0; j < SIZE; j++) 
			if (visited[j])
				for (int k = 0; k < SIZE; k++) //Бегаем по столбцам, запоминаем индекс минимального веса
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