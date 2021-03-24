
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <fstream>

#define SIZE 15
int main()
{
	setlocale(LC_ALL, "Russian");
	int min[SIZE]; // минимальное расстояние
	int node[SIZE]; // посещенные вершины 
	int gr_not_orient[SIZE][SIZE];
	int temp, min_index, min_const;
	int begin_index, end_index;
	system("chcp 1251");
	system("cls");
	// Инициализация матрицы связей
	int graph[SIZE][SIZE] = {
		{0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1-я вершина
		{0, 0, 1, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
		{0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
		{0, 0, 0, 0, 0, 0, 2, 0, 5, 0, 0, 0, 0, 0, 0}, // 5
		{0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0}, // 6
		{0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0}, // 7
		{0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 7, 0, 0}, // 8
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 6, 0, 0, 0}, // 9
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0}, // 10
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, // 11
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0}, // 12
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0}, // 13
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3}, // 14
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // 15
	};
	// Определение вершин
	int tmp1, tmp2;
	printf("Введите начальную вершину: ");
	scanf("%d", &tmp1);
	printf("Введите конечную вершину: ");
	scanf("%d", &tmp2);
	begin_index = tmp1 - 1, end_index = tmp2 - 1;
	// Вывод матрицы связей
	std::cout << "Исходная матрица связей графа:\n";
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			printf("%5d ", graph[i][j]);
		printf("\n");
	}
	//Инициализация вершин и расстояний
	for (int i = 0; i < SIZE; i++)
	{
		min[i] = 32767; // Максимально возможное число
		node[i] = 1; // Помечаем вершину как непройденную
	}
	min[begin_index] = 0; // Выбираем вершину, с которой будем начинать
	// Шаг алгоритма
	do {
		min_index = 32767;
		min_const = 32767;
		for (int i = 0; i < SIZE; i++)
		{
			if ((node[i] == 1) && (min[i] < min_const))	// Если вершину ещё не обошли и вес меньше min_const
			{ // Переприсваиваем значения
				min_const = min[i];
				min_index = i;
			}
		}
		/* Добавляем найденный минимальный вес
		к текущему весу вершины и сравниваем с текущим минимальным весом вершины */
		if (min_index != 32767)
		{
			for (int i = 0; i < SIZE; i++)
			{
				if (graph[min_index][i] > 0)
				{
					temp = min_const + graph[min_index][i];
					if (temp < min[i])
					{
						min[i] = temp;
					}
				}
			}
			node[min_index] = 0;
		}
	} while (min_index < 32767);
	printf("\nМинимальное расстояние от %d до %d: ", tmp1, tmp2);
	printf("%d \n", min[end_index]);

	// Для восстановления пути необходимо преобразовать исходный граф в неориентированный
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			gr_not_orient[i][j] = graph[i][j];
		}
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			if (gr_not_orient[i][j] != 0)
				gr_not_orient[j][i] = gr_not_orient[i][j];
		}

	// Восстановление пути
	int ver[SIZE]; // массив посещенных вершин
	int end = tmp2 - 1; // индекс конечной вершины
	ver[0] = end + 1; // начальный элемент - конечная вершина
	int k = 1; // индекс предыдущей вершины
	int weight = min[end]; // вес конечной вершины

	while (end != begin_index) // пока не дошли до начальной вершины
	{
		for (int i = 0; i < SIZE; i++) // просматриваем все вершины
			if (gr_not_orient[end][i] != 0)   // если связь есть
			{
				int temp = weight - gr_not_orient[end][i]; // определяем вес пути из предыдущей вершины
				if (temp == min[i]) // если вес совпал с рассчитанным
				{                 // значит из этой вершины и был переход
					weight = temp; // сохраняем новый вес
					end = i;       // сохраняем предыдущую вершину
					ver[k] = i + 1; // и записываем ее в массив
					k++;
				}
			}
	}
	// Вывод пути (начальная вершина оказалась в конце массива из k элементов)
	std::cout << "Кратчайший путь:\n";
	for (int i = k - 1; i >= 0; i--)
		std::cout << ver[i] << ' ';


	// Вторая часть лабораторной: алгоритм Прима
	std::cout << "\n\nПоиск минимального остовного дерева с помощью алгоритма Прима ";
	std::cout << "\nИсходный граф, преобразованный в неориентированный: \n";
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			printf("%5d ", gr_not_orient[i][j]);
		printf("\n");
	}
	std::cout << "\nМинимальное остовное дерево: \n";
	bool* visited = new bool[SIZE];
	memset(visited, false, sizeof(bool) * SIZE);
	visited[0] = true;
	for (int i = 0; i < SIZE - 1; i++) {
		int minx = -1, miny = -1;
		for (int j = 0; j < SIZE; j++)
			if (visited[j])
				for (int k = 0; k < SIZE; k++)
					if (!visited[k] && gr_not_orient[j][k] > 0 && (miny == -1 || gr_not_orient[j][k] < gr_not_orient[miny][minx]))
						miny = j, minx = k;
		visited[minx] = true;
		std::cout << (miny + 1) << "-" << (minx + 1) << ':' << gr_not_orient[miny][minx] << '\t';
	}

	getchar(); getchar();
	return 0;
}