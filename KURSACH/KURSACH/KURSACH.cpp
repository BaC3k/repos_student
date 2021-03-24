#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <windows.h>
#include "glut.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;


float offset_X, offset_Y;
void Initialize(int, int, int, int, const char*); //Инициализация и создание окна
void Screenshot(int, int, const char*); //Выводим полученную картинку в файл
void DisplayText(float, float, int, int, int, const char*); //Вывод строки в окно
void Drawgrid(float, float, int, int); //Отрисовка системы координат
void Draw(); //Меню ввода, отрисовка графика, связь с openGL
int* multiplication(int, int*, int**);

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");
	glutInit(&argc, argv);
	Initialize(100, 0, 1200, 800, "Курсач");
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}


int* multiplication(int matrixSize, int* vector, int** matrix)
{

	// объявление одномерного динамического массива
	int* out = new int[matrixSize];
	// умножение элементов матрицы на вектор
	for (int ix = 0; ix < matrixSize; ix++)
	{
		out[ix] = 0;
		for (int jx = 0; jx < matrixSize; jx++)
			out[ix] += matrix[ix][jx] * vector[jx];
	}
	return out;
}
void Initialize(int x, int y, int W, int H, const char* str)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(W, H);		//Указываем размер окна
	glutInitWindowPosition(x, y);	//Позиция окна
	glutCreateWindow(str);		    //создаем окно с заданным именем
	//Выбрать фоновый (очищающий) цвет
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}
void Screenshot(int W, int H, const char* name)
{
	const int imSize = W * H * 3; unsigned char* image = new unsigned char[imSize];
	memset(image, 0, imSize);
	glReadPixels(0, 0, W, H, GL_RGB, GL_UNSIGNED_BYTE, image);
	BITMAPINFO bmi;
	int SBI = sizeof(BITMAPINFOHEADER);
	int SBF = sizeof(BITMAPFILEHEADER);
	memset(&bmi, 0, SBI);
	bmi.bmiHeader.biSize = SBI;
	bmi.bmiHeader.biHeight = H;
	bmi.bmiHeader.biWidth = W;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = imSize;
	FILE* F = fopen(name, "w");
	int nBitsOffset = SBI + SBF;
	LONG lImageSize = imSize;
	LONG lFileSize = nBitsOffset + lImageSize;
	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 'B' + ('M' << 8);
	bmfh.bfOffBits = nBitsOffset;
	bmfh.bfSize = lFileSize;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	UINT nWrittenFileHeaderSize = fwrite(&bmfh, 1, SBF, F);
	UINT nWrittenInfoHeaderSize = fwrite(&bmi, 1, SBI, F);
	UINT nWrittenDIBDataSize = fwrite(image, 1, imSize, F);
	UINT total = nWrittenDIBDataSize + nWrittenInfoHeaderSize + nWrittenFileHeaderSize;
	delete[]image;
	fclose(F);
}
void DisplayText(float x, float y, int r, int g, int b, const char* str)
{
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	int i = 0;
	while (str[i] != '\0')
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
		i++;
	}
}
void Drawgrid(float X_M, float Y_M, int cena_del_x, int cena_del_y)
{
	int x_counter = 0, y_counter = 0; // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	float p, i, delta = 0.005, dlina_zasechki = (cena_del_x == 1 ? cena_del_x : cena_del_x / 2), dlina_zasechki_y = cena_del_y / 2;
	char buf[128];
	offset_X = X_M / 2;
	offset_Y = Y_M / 2;
	glOrtho(0.0, X_M, 0.0, Y_M, -1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//Отрисовка белого квадрата 
	glColor3f(1.0, 1.0, 1.0); //Выбираем белый цвет
	glBegin(GL_POLYGON);
	glVertex2f(0.0, 0.0); //Координаты квадрата
	glVertex2f(1.0, 0.0);
	glVertex2f(1.0, 1.0);
	glVertex2f(0.0, 1.0);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2);
	glBegin(GL_LINES);
	//Ось y
	glVertex2f(offset_X, 0.0);
	glVertex2f(offset_X, Y_M);
	//ось х
	glVertex2f(0.0, offset_Y);
	glVertex2f(X_M, offset_Y);
	glEnd();
	//Буквы Y,X
	DisplayText(offset_X + dlina_zasechki / 2, Y_M - dlina_zasechki_y, 0, 0, 0, "Y");
	DisplayText(X_M - dlina_zasechki / 6, offset_Y - 3 * dlina_zasechki_y, 0, 0, 0, "X");
	glLineWidth(2.8);
	glBegin(GL_LINES);
	//стрелочки на y
	glVertex2f(offset_X, Y_M);
	glVertex2f(offset_X + dlina_zasechki / 6, Y_M - dlina_zasechki_y);
	glVertex2f(offset_X, Y_M);
	glVertex2f(offset_X - dlina_zasechki / 6, Y_M - dlina_zasechki_y);
	//стрелочки на x
	glVertex2f(X_M, offset_Y);
	glVertex2f(X_M - dlina_zasechki / 6, offset_Y + dlina_zasechki_y);
	glVertex2f(X_M, offset_Y);
	glVertex2f(X_M - dlina_zasechki / 6, offset_Y - dlina_zasechki_y);
	glEnd();
	//засечки по горизонтали
	glLineWidth(1);
	for (i = offset_X, p = offset_X; i < X_M; i += cena_del_x, p -= cena_del_x)
	{
		if ((x_counter / cena_del_x) % 2)
		{
			glBegin(GL_LINES);
			//Длинные засечки, х>0
			glVertex2f(i, offset_Y - dlina_zasechki_y);
			glVertex2f(i, offset_Y + dlina_zasechki_y);
			//Длинные засечки, х<0
			glVertex2f(p, offset_Y - dlina_zasechki_y);
			glVertex2f(p, offset_Y + dlina_zasechki_y);
			glEnd();
			//Числа на оси Х
			_itoa(x_counter, buf, 10);
			DisplayText(i - (dlina_zasechki / 12) * (strlen(buf)) + 0.05, offset_Y - 2 * dlina_zasechki_y, 0, 0, 0, buf);
			DisplayText(p - (dlina_zasechki / 12) * (strlen(buf)) + 0.1, offset_Y - 2 * dlina_zasechki_y, 0, 0, 0, _itoa(-x_counter, buf, 10));
		}
		else
		{
			glBegin(GL_LINES);
			//короткие засечки, х>0
			glVertex2f(i, offset_Y - dlina_zasechki_y / 2);
			glVertex2f(i, offset_Y + dlina_zasechki_y / 2);
			//короткие засечки, х<0
			glVertex2f(p, offset_Y - dlina_zasechki_y / 2);
			glVertex2f(p, offset_Y + dlina_zasechki_y / 2);
			glEnd();
		}
		x_counter += cena_del_x;
	}
	//засечки по вертикали
	glLineWidth(0.25);
	for (i = offset_Y, p = offset_Y; i < Y_M - dlina_zasechki; i += cena_del_y, p -= cena_del_y) {
		if ((y_counter / cena_del_y) % 2)
		{
			glBegin(GL_LINES);
			//Длинные засечки, Y>0
			glVertex2f(offset_X - dlina_zasechki / 8, i);
			glVertex2f(offset_X + dlina_zasechki / 8, i);
			//Длинные засечки, Y<0
			glVertex2f(offset_X - dlina_zasechki / 8, p);
			glVertex2f(offset_X + dlina_zasechki / 8, p);
			glEnd();
			//Числа на оси Y
			_itoa(y_counter, buf, 10);
			DisplayText(offset_X - (strlen(buf)) * (dlina_zasechki / 8), i - dlina_zasechki_y / 4, 0, 0, 0, buf);
			if (y_counter > cena_del_y)
				DisplayText(offset_X - (strlen(buf)) * (dlina_zasechki / 8), p - dlina_zasechki_y / 4, 0, 0, 0, _itoa(-y_counter, buf, 10));
		}
		else
		{
			glBegin(GL_LINES);
			//короткие засечки, Y>0
			glVertex2f(offset_X - dlina_zasechki / 16, i);
			glVertex2f(offset_X + dlina_zasechki / 16, i);
			//короткие засечки, Y<0
			glVertex2f(offset_X - dlina_zasechki / 16, p);
			glVertex2f(offset_X + dlina_zasechki / 16, p);
			glEnd();
		}
		y_counter += cena_del_y;
	}
	glEnd();
}
void Draw()
{
	int matrixSize = 0; // количество строк и столбцов
	int action;
	Drawgrid(10, 1300, 1, 50);  //Масштаб изменять тут
	cout << "Введите количество строк и столбцов матрицы Ф: ";
	cin >> matrixSize;;

	// объявление двумерного динамического массива
	int** matrix = new int* [matrixSize];
	for (int count = 0; count < matrixSize; count++)
		matrix[count] = new int[matrixSize];

	//заполнение матрицы
	for (int ix = 0; ix < matrixSize; ix++)
		for (int jx = 0; jx < matrixSize; jx++)
		{
			cout << "matrix[" << (ix + 1) << "][" << (jx + 1) << "] = ";
			cin >> matrix[ix][jx];
		}
	// объявление одномерного динамического массива
	int* vector = new int[matrixSize];
	cout << "Введите элементы вектора X(0):\n";

	// заполнение вектора
	for (int ix = 0; ix < matrixSize; ix++)
	{
		cout << "vector[" << (ix + 1) << "] = ";
		cin >> vector[ix];

	}
	int p;
	cout << "Введите количество шагов N: ";
	cin >> p;

	cout << "\nВведенная матрица Ф:\n";
	for (int ix = 0; ix < matrixSize; ix++)
	{
		for (int jx = 0; jx < matrixSize; jx++)
		{
			cout << setw(4) << matrix[ix][jx];
		}
		cout << endl;
	}



	int** v_matr = new int* [matrixSize];
	for (int ix = 0; ix < matrixSize; ix++)
		v_matr[ix] = new int[p];

	//Вносим в матрицу 0-вой вектор
	for (int ix = 0; ix < matrixSize; ix++)
		v_matr[ix][0] = vector[ix];



	cout << "\nВведенный вектор X(0):\n";
	for (int ix = 0; ix < matrixSize; ix++)
	{
		cout << setw(4) << vector[ix] << endl;
	}

	for (int k = 0; k < p - 1; k++)
	{
		vector = multiplication(matrixSize, vector, matrix);
		cout << "\nРезультирующий вектор X(" << k + 1 << "):\n";
		for (int ix = 0; ix < matrixSize; ix++)
		{
			cout << setw(4) << vector[ix] << endl;
			//Вносим остальные вектора
			v_matr[ix][k + 1] = vector[ix];
		}

	}


	//Рисуем
	glColor3f(1, 0, 0);
	glLineWidth(0.5);
	for (int ix = 0; ix < matrixSize; ix++)
	{
		glBegin(GL_LINE_STRIP);
		for (int k = 0; k < p; k++)
		{
			glVertex2f(offset_X + k, offset_Y + v_matr[ix][k]);
		}
		glEnd();
		glColor3f(1 / (ix + 1), 0, 1);
	}
	// высвобождение памяти отводимой под двумерный динамический массив:
	for (int count = 0; count < matrixSize; count++)
		delete[] matrix[count];

	for (int count = 0; count < matrixSize; count++)
		delete[] v_matr[count];

	// высвобождение памяти отводимой под одномерный динамический массив
	delete[] vector;

	Screenshot(1200, 800, "result1.bmp");
	printf("runtime = %f", clock() / 1000.0);
	glFlush();
	system("pause");
}




