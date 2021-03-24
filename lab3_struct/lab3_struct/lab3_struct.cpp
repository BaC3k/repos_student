#include <iostream>
#include <fstream>
#include <time.h>
#define SIZE 20
using namespace std;

void Out(int*, int);
void PutIn(int*, int);
void ShellSort(int*, int);
void BubbleSort(int*, int);

int main()
{
    int a[SIZE], b[SIZE];
    double start, end;
    setlocale(LC_ALL, "Rus");

    PutIn(a, SIZE);
    PutIn(b, SIZE);
    cout << "Array: ";
    Out(a, SIZE);

    cout << "Bubble: "<<endl;
    start = clock();
    BubbleSort(a, SIZE);
    end = clock();
    cout << "Время: " << (end - start)/ 1000 << " с\n";

    cout << "Shell:  " << endl;
    start = clock();
    ShellSort(b, SIZE);
    end = clock();
    cout << "Время: "<<(end - start) / 1000 << " с\n";

    getchar();
    return 0;
}

void ShellSort(int* arr, int size)
{
    int step, i, j, tmp, sravn = 1, iter = 0;

    for (step = size / 2; step > 0; step /= 2) //определяем шаг
    {
        sravn++;
        for (i = step; i < size; i++)
        {
            sravn+=3;
            // Перестановка элементов внутри подсписка, пока i-тый не будет отсортирован
            for (j = i - step; (j >= 0);  j -= step)
            {   
                if (arr[j] > arr[j + step])
                {
                    tmp = arr[j];
                    arr[j] = arr[j + step];
                    arr[j + step] = tmp;

                    cout << "Итерация " << iter << ":  ";
                    Out(arr, size);
                    iter++;
                }
            }
        }

    }
    cout << "Кол-во сравнений: " << sravn << endl;
}
void BubbleSort(int* arr, int size) // сортировка пузырьком
{
    int temp, i = 0, j=0, sravn = 1, iter= 0;
    bool exit = false;

    for (j; !exit; j++) // пока массив не отсортирован
    {
        exit = true;
        for (i = 0; i < (size - j - 1); i++) //Не берем в расчёт элементы которые уже всплыли
        {
            sravn += 2;
            if (arr[i] > arr[i + 1]) // сравниваем два соседних элемента
            {
                // выполняем перестановку элементов массива
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                exit = false; // на очередной итерации была произведена перестановка элементов

                cout << "Итерация " << iter << ":  ";
                Out(arr, size);
                iter++;
            }
        }
    }
    sravn += j;
    cout << "Кол-во сравнений: " << sravn << endl;
}
void PutIn(int* a, int size)
{
    ifstream input("data.txt");
    int value;
    for (int i = 0; i < size; i++)
    {
        input >> value;
        a[i] = value;
    }
}
void Out(int* a, int size)
{
    for (int i = 0; i < size; i++)
        cout << a[i] << "  ";
    cout << endl;
}
