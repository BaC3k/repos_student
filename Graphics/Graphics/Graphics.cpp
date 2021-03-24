#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <math.h> 
#include <cstdlib> 
#include <string> 
#include <fstream> 
#include <GL/freeglut.h>
//#include <glut.h>
#include <windows.h>
#include <ctime>

using namespace std;


class Graphics;
static Graphics* currentInstance;/*Использование currentInstance и drawCallback необходимо, так как glut сам по себе не воспринимает this,
								 необходимый для привязки его к классу. Использование статических функций позволяет избежать такой ошибки.*/
class Graphics
{
private:
	double* X;
	int N, w, h;
	int error_file;
public:
	Graphics(int);
	~Graphics();
	void Fill_Rand(int, int);
	void Fill_File();
	int Get_Error();
	void Set_Error();
	void Reset_Error();
	void Printing_Arrays_into_Files();
	void Graph_Draw1(int argc, char* argv[]);
	void Graph_Draw2(int argc, char* argv[]);
	void Graph_Draw3(int argc, char* argv[]);
private:
	static void drawCallback1();
	static void drawCallback2();
	static void drawCallback3();
	void Graphics_Creation1();
	void Graphics_Creation2();
	void Graphics_Creation3();
	void PrintText(float x, float y, int r, int g, int b, string string);
	void ScreenShot1(int W, int H);
	void ScreenShot2(int W, int H);
	void ScreenShot3(int W, int H);
};

void Graphics::drawCallback1() { currentInstance->Graphics_Creation1(); }
void Graphics::drawCallback2() { currentInstance->Graphics_Creation2(); }
void Graphics::drawCallback3() { currentInstance->Graphics_Creation3(); }

int Graphics::Get_Error() { return error_file; }

void Graphics::Set_Error() { error_file = 0; };

void Graphics::Reset_Error() { error_file = 1; };

Graphics::Graphics(int N1)
{
	N = N1;
	w = 1900;
	error_file = 1;
	h = 1000;
	X = new double[N1];
}

Graphics::~Graphics()
{
	delete[] X;
}

void Graphics::Fill_Rand(int range, int min)
{
	srand(time(NULL));
	for (int i = 0; i < N; i++)
		X[i] = rand() % range + min;
}

void Graphics::Fill_File()
{
	ifstream fin("KursovayaInput.txt");
	string tmp;
	char tmpc;
	int i;
	if (!fin.is_open())
	{
		cout << "Файл открыть не удалось. Пожалуйста, проверьте наличие файла.\nИмя файла по умолчанию - KursovayaInput.txt" << endl;
		Set_Error();
		return;
	}
	for (i = 0; i < N; i++)
	{
		fin >> tmp;
		if (fin.bad())
		{
			cout << "Произошла ошибка считывания.";
			Set_Error();
			fin.close();
			return;
		}
		for (int j = 0; j < tmp.length(); j++)
		{
			tmpc = tmp[j];
			if (!isdigit(tmpc) && tmpc != '.' && tmpc != ',' && tmpc != '-' && (tmp.find(".") != tmp.rfind(".")) && (tmp.find(".") > -1 && tmp.find(",") > -1))
			{
				cout << "Ошибка. Наличие постороннего символа (написано не число). Возврат в меню." << endl;
				Set_Error();
				fin.close();
				return;
			}
		}

		while (tmp.find(".") != -1)
		{
			tmp.replace(tmp.find("."), 1, ",");
		}
		X[i] = stod(tmp);

	}
	fin.close();
}

void Graphics::Graph_Draw1(int argc, char* argv[])
{
	currentInstance = this;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(w, h);
	glutCreateWindow("Графики массивов");

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutDisplayFunc(drawCallback1);

	glutMainLoop();
}

void Graphics::Graph_Draw2(int argc, char* argv[])
{
	currentInstance = this;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(w, h);
	glutCreateWindow("Графики массивов");

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutDisplayFunc(drawCallback2);

	glutMainLoop();
}

void Graphics::Graph_Draw3(int argc, char* argv[])
{
	currentInstance = this;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(w, h);
	glutCreateWindow("Графики массивов");

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutDisplayFunc(drawCallback3);

	glutMainLoop();
}

void Graphics::Printing_Arrays_into_Files()
{
	int k;
	ofstream out;
	string tmp;
	out.open("KursovayaOutput.txt");
	if (!out.is_open())
	{
		cout << "Файл для записи массивов: KursovayaOutput.txt - открыть не удалось." << endl;
		Set_Error();
		return;
	}
	out << "Массив X[k]:" << endl;
	for (k = 0; k < N; k++) { out << "X[" << k << "] = " << X[k] << endl; }
	out.close();
}

void Graphics::Graphics_Creation1()
{
	string changer;
	int length_x = w - 15;
	int length_y = floor(h - 60);
	double y_max, y_min, length;
	int k, i, y;
	double mast_y;
	double mast_x = floor(w - 15 / N);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(length_x/2, h - 30);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(length_x / 2, h - 30 - length_y);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(length_x / 2, h - 30);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(length_x / 2-5, h - 30 - 10);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(length_x / 2, h - 30);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(length_x / 2+5, h - 30 - 10);
	glEnd();

	y_max = 200;
	y_min = -200;

	for (i = 1; i < N; i++)
	{
		if (y_max < X[i]) { y_max = X[i]; }
		else if (y_min > X[i]) { y_min = X[i]; }
	}

	length = y_max - y_min;
	mast_y = length_y / length;
	y = h - 30 - length_y * y_max / length;
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(length_x / 2, y);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w, y);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w, y);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w - 10, y - 5);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w, y);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w - 10, y + 5);
	glEnd();

	PrintText(length_x / 2+10, h - 30, 0, 0, 0, "X[i]");
	PrintText(w - 10, y - 20, 0, 0, 0, "i");

	for (i = 0; i < N; i++)
	{
		glBegin(GL_LINES); //X[k]
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(length_x / 2 + mast_x * i / N, y + 5);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(length_x / 2 + mast_x * i / N, y - 5);
		glEnd();
		PrintText(length_x / 2 + mast_x * i / N, y - 20, 0, 0, 0, to_string(i));
	}

	for (k = 1; k <= 19; k++)
	{

		if (y - k * length_y / 20 >= h - 30 - length_y)
		{
			glBegin(GL_LINES); //X[k]
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(length_x / 2, y - k * length_y / 20);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(length_x / 2+5, y - k * length_y / 20);
			glEnd();
			changer = to_string(-(y_max - y_min) / 20 * k);
			if (-(y_max - y_min) / 20 * k + floor(-(y_max - y_min) / 20 * k) <= 0.000001) { changer.erase(changer.find(","), changer.length() - changer.find(",")); }
			if (k != 0) { PrintText(length_x / 2+10, y - k * length_y / 20 - 5, 0, 0, 0, changer); }
		}
		else
		{
			glBegin(GL_LINES); //X[k]
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(length_x / 2, y + (20 - k) * length_y / 20);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(length_x / 2+5, y + (20 - k) * length_y / 20);
			glEnd();
			changer = to_string((y_max - y_min) / 20 * (20 - k));
			if ((y_max - y_min) / 20 * (20 - k) - floor((y_max - y_min) / 20 * (20 - k)) <= 0.000001)
			{
				changer.erase(changer.find(","), changer.length() - changer.find(","));
			}
			PrintText(length_x / 2+10, y + (20 - k) * length_y / 20 - 5, 0, 0, 0, changer);
		}
	}

	for (k = 0; k < N; k++)
	{
		if (k != N - 1)
		{
			glBegin(GL_LINES);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(5 + k * mast_x / N, y + X[k] * mast_y);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(length_x / 2 + (k + 1) * mast_x / N, y + X[k + 1] * mast_y);
			glEnd();

		}
		glPointSize(5);
		glBegin(GL_POINTS);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(length_x / 2 + mast_x * k / N, y + X[k] * mast_y);
		glEnd();
	}

	ScreenShot1(w, h);
	glutSwapBuffers();
}

void Graphics::Graphics_Creation2()
{
	string changer;
	int length_x = w - 15;
	int length_y = h - 60;
	double y_max, y_min, length;
	int u, i, y;
	double mast_y;
	double mast_x = floor(w - 15 / N);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(5, h - 30);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(5, h - 30 - length_y);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(5, h - 30);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(0, h - 40);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(5, h - 30);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(10, h - 40);
	glEnd();

	y_max = 200;
	y_min = -200;
	for (i = 1; i < N; i++)
	{
		if (y_max < X[i]) { y_max = X[i]; }
		else if (y_min > X[i]) { y_min = X[i]; }
	}
	length = y_max - y_min;
	mast_y = length_y / length;
	y = h - 30 - length_y * y_max / length;

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(5, y);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w, y);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w, y);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w - 10, y - 5);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w, y);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w - 10, y + 5);
	glEnd();

	PrintText(15, h - 30, 0, 0, 0, "X[i]");
	PrintText(w - 10, y - 20, 0, 0, 0, "i");

	for (u = 0; u < N; u++)
	{
		glBegin(GL_LINES); //X[k]
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(5 + mast_x * u / N, y + 5);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(5 + mast_x * u / N, y - 5);
		glEnd();
		PrintText(5 + mast_x * u / N, y - 20, 0, 0, 0, to_string(u));
	}

	for (u = 1; u <= 19; u++)
	{
		if (y - u * length_y / 20 >= h - 30 - length_y)
		{
			glBegin(GL_LINES); //X[k]
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(0, y - u * length_y / 20);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(10, y - u * length_y / 20);
			glEnd();
			if (u != 0)
			{
				changer = to_string(-(y_max - y_min) / 20 * u);
				if (-(y_max - y_min) / 20 * u + floor(-(y_max - y_min) / 20 * u) <= 0.000001) { changer.erase(changer.find(","), changer.length() - changer.find(",")); }
				PrintText(15, y - u * length_y / 20 - 5, 0, 0, 0, changer);
			}
		}
		else
		{
			glBegin(GL_LINES); //X[k]
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(0, y + (20 - u) * length_y / 20);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(10, y + (20 - u) * length_y / 20);
			glEnd();
			changer = to_string((y_max - y_min) / 20 * (20 - u));
			if ((y_max - y_min) / 20 * (20 - u) - floor((y_max - y_min) / 20 * (20 - u)) <= 0.000001) { changer.erase(changer.find(","), changer.length() - changer.find(",")); }
			PrintText(15, y + (20 - u) * length_y / 20 - 5, 0, 0, 0, changer);
		}
	}

	for (u = 0; u < N; u++)
	{
		glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(5 + u * mast_x / N, y);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(5 + (u)*mast_x / N, y + X[u] * mast_y);
		glEnd();
		glPointSize(5);
		glBegin(GL_POINTS);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(5 + mast_x * u / N, y + X[u] * mast_y);
		glEnd();

	}

	ScreenShot2(w, h);
	glutSwapBuffers();
}

void Graphics::Graphics_Creation3()
{
	string changer;
	int length_x = w - 15;
	int length_y = floor(h - 60);
	double x_max, x_min, length, mast_num;
	int Y[10] = { 0,0,0,0,0,0,0,0,0,0 };

	int k, i, x, f;
	double mast_y;
	double mast_x;
	glClear(GL_COLOR_BUFFER_BIT);

	x_max = 0; x_min = 0;
	for (i = 0; i < N; i++)
	{
		if (X[i] > x_max)
			x_max = X[i];
		if (X[i] < x_min)
			x_min = X[i];
	}
	length = x_max - x_min;
	mast_num = length / 10;
	mast_x = length_x / 10;
	x = w - 15 - length_x * x_max / length;

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(x + 5, h - 30);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(x + 5, h - 30 - length_y - 5);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(x + 5, h - 30);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(x, h - 40);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(x + 5, h - 30);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(x + 10, h - 40);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(5, 30);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w - 10, 30);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w - 10, 30);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w - 15, 20);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w - 10, 30);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w - 15, 40);
	glEnd();

	PrintText(x + 10, 0, 0, 0, 0, "0");

	for (i = 0; i < N; i++)
	{
		for (k = 0; k < 10; k++)
		{
			if (k == 0)
			{
				if (((X[i] > x_min) && (X[i] < x_min + mast_num)) || (fabs(X[i] - x_min) < 0.000001) || (fabs(X[i] - x_min - mast_num) < 0.000001))
				{
					Y[k]++;
					continue;
				}
			}
			else
			{
				if (((X[i] > x_min + mast_num * k) && (X[i] < x_min + mast_num * (k + 1))) || (fabs(X[i] - (x_min + mast_num * (k + 1))) < 0.000001))
				{
					Y[k]++;
					continue;
				}
			}
		}
	}
	int y_max = Y[0], y_min = 0;
	for (i = 1; i < 10; i++)
		if (y_max < Y[i]) y_max = Y[i];
	mast_y = length_y / y_max;

	PrintText(w - 30, 40, 0, 0, 0, "X[i]");
	PrintText(x + 20, h - 30, 0, 0, 0, "Raspredelenie chisel po otrezkam");

	for (i = 0; i < 10; i++)
	{
		glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(x, 30 + mast_y * Y[i]);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(x + 10, 30 + mast_y * Y[i]);
		glEnd();
		PrintText(x - 20, 30 + mast_y * Y[i], 0, 0, 0, to_string(Y[i]));
	}
	for (i = 0; i <= 10; i++)
	{
		glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(5 + mast_x * i, h - 30 - length_y + 5);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(5 + mast_x * i, h - 30 - length_y - 5);
		glEnd();
		changer = to_string(x_min + mast_num * i);
		while (changer.rfind("0") == changer.length() - 1)
		{
			changer.erase(changer.length() - 1, 1);
		}
		if (changer.rfind(",") == changer.length() - 1) changer.erase(changer.length() - 1, 1);
		PrintText(mast_x * i, h - 30 - length_y - 20, 0, 0, 0, changer);
	}

	for (i = 0; i < 10; i++)
	{
		glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(5 + mast_x * i, 30);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(5 + mast_x * i, 30 + mast_y * Y[i]);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(5 + mast_x * (i + 1), 30);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(5 + mast_x * (i + 1), 30 + mast_y * Y[i]);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(5 + mast_x * i, 30 + mast_y * Y[i]);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(5 + mast_x * (i + 1), 30 + mast_y * Y[i]);
		glEnd();
	}
	/*
	y_max = 200;
	y_min = -200;

	for (i = 1; i < N; i++)
	{
		if (y_max < X[i]) {y_max = X[i];}
		else if (y_min > X[i]) {y_min = X[i];}
	}

	length = y_max - y_min;
	mast_y = length_y / length;
	y = h - 30 - length_y * y_max / length;
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(5, y);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w, y);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w, y);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w - 10, y - 5);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w, y);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(w - 10, y + 5);
	glEnd();

	PrintText(15, h - 30, 0, 0, 0, "X[i]");
	PrintText(w - 10, y - 15, 0, 0, 0, "i");
	for (i = 0; i < N; i++)
	{
		glBegin(GL_LINES); //X[k]
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(5 + mast_x * i / N, y + 5);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(5 + mast_x * i / N, y - 5);
		glEnd();
		PrintText(5 + mast_x * i / N, y - 17, 0, 0, 0, to_string(i));
	}
	for (k = 1; k <= 19; k++)
	{
		if (y - k * length_y / 20 >= h - 30 - length_y)
		{
			glBegin(GL_LINES); //X[k]
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(0, y - k * length_y / 20);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(10, y - k * length_y / 20);
			glEnd();
			changer = to_string(-(y_max - y_min) / 20 * k);
			if (-(y_max - y_min) / 20 * k + floor(-(y_max - y_min) / 20 * k) <= 0.000001) {changer.erase(changer.find(","), changer.length() - changer.find(","));}
			if (k != 0) {PrintText(15, y - k * length_y / 20 - 5, 0, 0, 0, changer);}
		}
		else
		{
			glBegin(GL_LINES); //X[k]
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(0, y + (20 - k) * length_y / 20);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(10, y + (20 - k) * length_y / 20);
			glEnd();
			changer = to_string((y_max - y_min) / 20 * (20 - k));
			if ((y_max - y_min) / 20 * (20 - k) - floor((y_max - y_min) / 20 * (20 - k)) <= 0.000001) { changer.erase(changer.find(","), changer.length() - changer.find(",")); }
			PrintText(15, y + (20 - k) * length_y / 20 - 5, 0, 0, 0, changer);
		}
	}

	for (k = 0; k < N; k++)
	{
			glBegin(GL_LINES); //X[k]
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(5 + k * mast_x / N, y);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(5 + k * mast_x / N, y + X[k] * mast_y);
			glEnd();

			glBegin(GL_LINES);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(5 + (k + 1) * mast_x / N, y);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(5 + (k + 1)* mast_x / N, y + X[k] * mast_y);
			glEnd();

			glBegin(GL_LINES); //X[k]
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(5 + k * mast_x / N, y + X[k] * mast_y);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2i(5 + (k + 1)* mast_x / N, y + X[k] * mast_y);
			glEnd();
	}*/

	ScreenShot3(w, h);
	glutSwapBuffers();
}

void Graphics::PrintText(float x, float y, int r, int g, int b, string string)
{
	char* text = new char[string.length()];
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for (int i = 0; i < string.length(); i++)
		text[i] = string[i];
	for (int i = 0; i < string.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		x += 2;
	}
	delete[] text;
}

void Graphics::ScreenShot1(int W, int H)
{
	FILE* F = fopen("Graphs1.bmp", "w");
	if (F == NULL)
	{
		cout << "Файл для записи графика массива X[k] открыть/создать не удалось." << endl;
		Set_Error();
		return;
	}

	const int imSize = W * H * 3;
	unsigned char* image = new unsigned char[imSize];

	if (!image)
	{
		cout << "Не удалось выделить память под массивы." << endl;
		Set_Error();
		return;
	}

	memset(image, 0, imSize);
	glReadPixels(0, 0, W, H, GL_RGB, GL_UNSIGNED_BYTE, image);
	BITMAPINFO bmi;
	unsigned char BMI = sizeof(BITMAPINFOHEADER);
	unsigned char BMF = sizeof(BITMAPFILEHEADER);
	memset(&bmi, 0, BMI);
	bmi.bmiHeader.biSize = BMI;
	bmi.bmiHeader.biHeight = H;
	bmi.bmiHeader.biWidth = W;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = imSize;

	int nBitsOffset = BMF + BMI;
	LONG lImageSize = imSize;
	LONG lFileSize = nBitsOffset + lImageSize;
	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 0x4D42;
	bmfh.bfOffBits = nBitsOffset;
	bmfh.bfSize = lFileSize;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;

	UINT nWrittenFileHeaderSize = fwrite(&bmfh, 1, BMF, F);
	UINT nWrittenInfoHeaderSize = fwrite(&bmi, 1, BMI, F);
	UINT nWrittenDIBDataSize = fwrite(image, 1, imSize, F);
	UINT total = nWrittenDIBDataSize + nWrittenInfoHeaderSize + nWrittenFileHeaderSize;
	delete[] image;
	fclose(F);
}

void Graphics::ScreenShot2(int W, int H)
{
	FILE* F = fopen("Graphs2.bmp", "w");
	if (F == NULL)
	{
		cout << "Файл для записи графика массива X[k] открыть/создать не удалось." << endl;
		Set_Error();
		return;
	}

	const int imSize = W * H * 3;
	unsigned char* image = new unsigned char[imSize];

	if (!image)
	{
		cout << "Не удалось выделить память под массивы." << endl;
		Set_Error();
		return;
	}

	memset(image, 0, imSize);
	glReadPixels(0, 0, W, H, GL_RGB, GL_UNSIGNED_BYTE, image);
	BITMAPINFO bmi;
	unsigned char BMI = sizeof(BITMAPINFOHEADER);
	unsigned char BMF = sizeof(BITMAPFILEHEADER);
	memset(&bmi, 0, BMI);
	bmi.bmiHeader.biSize = BMI;
	bmi.bmiHeader.biHeight = H;
	bmi.bmiHeader.biWidth = W;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = imSize;

	int nBitsOffset = BMF + BMI;
	LONG lImageSize = imSize;
	LONG lFileSize = nBitsOffset + lImageSize;
	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 0x4D42;
	bmfh.bfOffBits = nBitsOffset;
	bmfh.bfSize = lFileSize;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;

	UINT nWrittenFileHeaderSize = fwrite(&bmfh, 1, BMF, F);
	UINT nWrittenInfoHeaderSize = fwrite(&bmi, 1, BMI, F);
	UINT nWrittenDIBDataSize = fwrite(image, 1, imSize, F);
	UINT total = nWrittenDIBDataSize + nWrittenInfoHeaderSize + nWrittenFileHeaderSize;
	delete[] image;
	fclose(F);
}

void Graphics::ScreenShot3(int W, int H)
{
	FILE* F = fopen("Graphs3.bmp", "w");
	if (F == NULL)
	{
		cout << "Файл для записи графика массива X[k] открыть/создать не удалось." << endl;
		Set_Error();
		return;
	}

	const int imSize = W * H * 3;
	unsigned char* image = new unsigned char[imSize];

	if (!image)
	{
		cout << "Не удалось выделить память под массивы." << endl;
		Set_Error();
		return;
	}

	memset(image, 0, imSize);
	glReadPixels(0, 0, W, H, GL_RGB, GL_UNSIGNED_BYTE, image);
	BITMAPINFO bmi;
	unsigned char BMI = sizeof(BITMAPINFOHEADER);
	unsigned char BMF = sizeof(BITMAPFILEHEADER);
	memset(&bmi, 0, BMI);
	bmi.bmiHeader.biSize = BMI;
	bmi.bmiHeader.biHeight = H;
	bmi.bmiHeader.biWidth = W;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = imSize;

	int nBitsOffset = BMF + BMI;
	LONG lImageSize = imSize;
	LONG lFileSize = nBitsOffset + lImageSize;
	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 0x4D42;
	bmfh.bfOffBits = nBitsOffset;
	bmfh.bfSize = lFileSize;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;

	UINT nWrittenFileHeaderSize = fwrite(&bmfh, 1, BMF, F);
	UINT nWrittenInfoHeaderSize = fwrite(&bmi, 1, BMI, F);
	UINT nWrittenDIBDataSize = fwrite(image, 1, imSize, F);
	UINT total = nWrittenDIBDataSize + nWrittenInfoHeaderSize + nWrittenFileHeaderSize;
	delete[] image;
	fclose(F);
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RUSSIAN");
	string key, key1;
	int N, range, min;

	cout << "Программа, рисующая график, частотную характеристику и гистограмму" << endl;
	while (1)
	{
		cout << "Выберите режим работы программы:\n1 - создание массива.\n0 - выход из программы.\nПримечание: название файла: KursovayaInput.txt\"" << endl << "Выбрано ";
		getline(cin, key);
		if (key == "1")
		{
			cout << "Введите размер массива:" << endl;
			cin >> N;
			Graphics* Mas;
			Mas = new Graphics(N);
			cout << "Введите режим создания массива:\n1 - массив, созданный генератором случайных чисел.\n2 - массив, полученный из файла." << endl;
			cin.ignore();
			getline(cin, key1);
			if (key1 == "1")
			{
				cout << "Введите диапазон массива:" << endl;
				cin >> range;
				cout << "Введите минимальное возможное значение массива:" << endl;
				cin >> min;
				Mas->Fill_Rand(range, min);
				Mas->Printing_Arrays_into_Files();
				if (Mas->Get_Error() == 0)
				{
					cout << "Не удалось записать массив в файл. Возврат в меню." << endl;
					continue;
				}
				Mas->Graph_Draw1(argc, argv);
				if (Mas->Get_Error() == 0) { cout << "Не удалось сохранить рисунок в файл. Возврат в меню." << endl;	continue; }
				Mas->Graph_Draw2(argc, argv);
				if (Mas->Get_Error() == 0) { cout << "Не удалось сохранить рисунок в файл. Возврат в меню." << endl;	continue; }
				Mas->Graph_Draw3(argc, argv);
				if (Mas->Get_Error() == 0) { cout << "Не удалось сохранить рисунок в файл. Возврат в меню." << endl;	continue; }
				cin.ignore();
				continue;
			}
			else if (key1 == "2")
			{
				Mas->Fill_File();
				if (Mas->Get_Error() == 0)
				{
					cout << "Не удалось записать массив в файл. Возврат в меню." << endl;
					continue;
				}
				Mas->Printing_Arrays_into_Files();
				if (Mas->Get_Error() == 0) { continue; }
				Mas->Graph_Draw1(argc, argv);
				if (Mas->Get_Error() == 0) { cout << "Не удалось сохранить рисунок в файл. Возврат в меню." << endl;	continue; }
				Mas->Graph_Draw2(argc, argv);
				if (Mas->Get_Error() == 0) { cout << "Не удалось сохранить рисунок в файл. Возврат в меню." << endl;	continue; }
				Mas->Graph_Draw3(argc, argv);
				if (Mas->Get_Error() == 0) { cout << "Не удалось сохранить рисунок в файл. Возврат в меню." << endl;	continue; }
				continue;
			}
			else
			{
				cout << "Такой команды не существует в данной программе. Возврат в меню." << endl;
				continue;
			}
		}
		else if (key == "0")
		{
			cout << "Завершение работы программы." << endl;
			return 0;
		}
		else { cout << "Такой команды не существует в данной программе. Возврат в меню." << endl; }
	}
}