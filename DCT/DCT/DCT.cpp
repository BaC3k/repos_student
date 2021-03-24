#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <iostream> 
#include <cmath> 
#include "fstream"
#include <graphics.h>
using namespace std;

class DTA /*Класс дискретный тригонометрический анализатор*/
{
private:
    int N; /*размер массива*/
    double* mas; /*Массив*/
    double* dct_mas;
    double* idct_mas;
public:
    DTA(); /*Конструктор класса, базовые значения N=64, массив заполняется по функции синуса*/
    int input(); /*Ввод массива из файла*/
    int output(); /*Вывод массива на экран*/
    double* get_mas();
    double* get_dct_mas();
    double* get_idct_mas();

    double* dct(); /*Метод дискретного косинусного преобразования массива*/
    double* idct(); /*Метод обратного дискретного косинусного преобразования массива*/
    void graph(int); /*Метод отрисовки графики*/
};

DTA::DTA() //Конструктор
{
    N = 64;
    mas = new double[N];
    dct_mas = new double[N];
    idct_mas = new double[N];
    for (int i = 0; i < N; i++)
    {
        if (sin(4 * M_PI * i / N) > 0)
            mas[i] = 1;
        else if (sin(4 * M_PI * i / N) < 0)
            mas[i] = -1;
        else
            mas[i] = 0;
    }
}

double* DTA::get_mas()
{
    return(mas);
}
double* DTA::get_dct_mas()
{
    return(dct_mas);
}
double* DTA::get_idct_mas()
{
    return(idct_mas);
}
int DTA::input() //Ввод из файла
{
    ifstream input("data.txt");
    if (!input)
    {
        cout << "File not found\n";
        return -1;
    }
    else
    {
        input >> N;
        mas = new double[N];
        for (int i = 0; i < N; i++)
            input >> mas[i];
        return 0;
    }

}

int DTA::output() //Вывод на экран
{
    float delta;
    cout.precision(4);
    cout << "k:\tx(k):\tX(k):\te(k)=|x(k)-X(k)|" << endl;
    for (int k = 0; k < N; k++)
    {    
        cout <<k<<"\t"<<mas[k] << "\t";
        cout << idct_mas[k] << "\t";
        delta = abs(mas[k] - idct_mas[k]);
        cout << delta<<endl;
    }
    cout << endl;
    cout << "u:\tdct_mas:" << endl;

    for (int u = 0; u < N; u++)
    {
        cout <<fixed<< u << "\t" << dct_mas[u] << "\n";
    }
    cout << endl;
    return 0;
}

double* DTA::dct() /*Реализация дискретного косинусного преобразования */
{
    double sum, Cu;
    for (int u = 0; u < N; u++)
    {
        sum = 0;
        for (int k = 0; k < N; k++)
            sum += mas[k] * cos(M_PI * u * (k + 0.5) / N);

        if (u > 0)
            Cu = 1;
        else
            Cu = (double)sqrt(2) / 2;

        dct_mas[u] = sqrt((double)2 / N) * Cu * sum;

    }
    return dct_mas;
}

double* DTA::idct() /*Реализация обратного дискретного косинусного преобразования */
{
    double sum, Cu;
    for (int k = 0; k < N; k++)
    {
        sum = 0;
        for (int u = 0; u < N; u++)
        {
            if (u > 0)
                Cu = 1;
            else
                Cu = (double)sqrt(2) / 2;

            sum += Cu * dct_mas[u] * cos(M_PI * u * (k + 0.5) / N);
        }
        idct_mas[k] = sqrt((double)2 / N) * sum;

    }
    return idct_mas;
}

void DTA::graph(int action) /*графика*/
{
    int gdriver = DETECT, gmode, errorcode;
    char path[] = "";
    initgraph(&gdriver, &gmode, path);
    errorcode = graphresult();
    if (errorcode != grOk)
    {
        cout << "Ошибка графики: " << grapherrormsg(errorcode) << endl;
        cout << "Нажмите любую клавишу для прерывания:" << endl;
        getch(); return;
    }
    setcolor(15);
    bar(0, 0, getmaxx(), getmaxy());
    setbkcolor(15);
    setcolor(0);

    char buf[256];
    int x_c = getmaxx() / 15, y_c = getmaxy() / 2, delta_y=200, delta_x=9; 
    line(x_c, 0, x_c, getmaxy()); /*Координатные оси*/
    line(0, y_c, getmaxx(), y_c);
    moveto(x_c, y_c); /*Перемещаемся в центр системы координат*/
    
    double* mas_tmp;
    mas_tmp = new double[N];
    if (action == 0)
        mas_tmp = mas;
    else if (action == 2)
        mas_tmp = idct_mas;
    if (action !=1) /*Если отрисовываем график*/
    {
        delta_y = 200;
        delta_x = 9;
        setcolor(0);
        for (int i = 0; i < N; i++)//Рисуем график по точкам
        {
            lineto(x_c + i * delta_x, y_c - mas_tmp[i] * delta_y);
        }

        for (int i = 0; i < N; i ++)/*Цикл для отрисовки засечек и числовых значений на осях */
        {
            line(x_c + i * delta_x*10, y_c - 4, x_c + i * delta_x * 10, y_c + 4);//По оси х
            outtextxy(x_c + i * delta_x*10 - 10, y_c + 8, _itoa(i * 10, buf, 10));
            line(x_c - i * delta_x * 10, y_c - 4, x_c - i * delta_x * 10, y_c + 4);

            if (i != 0)
            {
                line(x_c - 4, y_c - delta_y * i, x_c + 4, y_c - delta_y * i);//По оси y
                outtextxy(x_c - 10, y_c - delta_y * i, _itoa(i, buf, 10));
                line(x_c - 4, y_c + delta_y * i, x_c + 4, y_c + delta_y * i);
                outtextxy(x_c - 20, y_c + delta_y * i, _itoa(-i, buf, 10));
            }
        }
    }
    else if (action==1) /*Если отрисовываем частотную характеристику*/
    {
        delta_y = 40;
        delta_x = 9;
        for (double i = 0; i < N; i++) /*Цикл для отрисовки засечек и числовых значений на осях */
        {
            line(x_c + i * delta_x * 10, y_c - 4, x_c + i * delta_x * 10, y_c + 4);//По оси х
            outtextxy(x_c + i * delta_x * 10 -10, y_c + 8, _itoa(i * 10, buf, 10));
            line(x_c - i * delta_x * 10, y_c - 4, x_c - i * delta_x * 10, y_c + 4);

            if (i != 0)
            {
                line(x_c - 4, y_c - i * delta_y, x_c + 4, y_c - i * delta_y);//По оси y
                outtextxy(x_c - 10, y_c - i * delta_y, _itoa(i, buf, 10));
                line(x_c - 4, y_c + i * delta_y, x_c + 4, y_c + i * delta_y);
                outtextxy(x_c - 20, y_c + i * delta_y, _itoa(-i, buf, 10));
            }
        }

        setcolor(4);
        for (int i = 0; i < N; i++)
        {
            double masi=dct_mas[i];
            if (abs(dct_mas[i]) > 0.02)
            {
                line(x_c + i * delta_x, y_c, x_c + i * delta_x, y_c - masi * delta_y);/*Отрисовываем частотную характеристику*/
                line(x_c + i * delta_x - 1, y_c, x_c + i * delta_x - 1, y_c - masi * delta_y);
                line(x_c + i * delta_x + 1, y_c, x_c + i * delta_x + 1, y_c - masi * delta_y);
            }
            else
            {
                masi = masi < 0 ? -1 : 1;
                bar3d(x_c + i * delta_x - 1, y_c, x_c + i * delta_x + 1, y_c - masi * 2, 0, 0);
            }
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    
    DTA obj; /*Стандартный конструктор*/
    obj.graph(0); //Рисуем график
    obj.dct(); //Используем ДКП
    obj.graph(1); //Рисуем частотную характеристику
    obj.idct();  //Используем ОДКП
    obj.graph(2); //Рисуем график
    obj.output(); //выводим массивы на экран

    system("pause");
    return 0;
}