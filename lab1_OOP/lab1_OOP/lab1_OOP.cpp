#define _USE_MATH_DEFINES
#include<graphics.h>
#include<iostream>
#include<math.h>
//#include<dos>
using namespace std;

class Quadrate//объявление класса
{
private:
	int X, Y;// координаты центра квадрата
	int X_C, Y_C;//координаты внешнего центра вращения
	int R;// радиус от центра квадрата до вершин
	int Rad;//Радиус от центра вращения до центра квадрата
	double Fi;// угол поворота квадрата
	double Alpha;//угол поворота относительно внешнего центра вращения
public:
	Quadrate(int, int, int, double, int, int,int, double);// конструктор
	void PutX(int);// методы-
	int GetX();// акцессоры
	void PutY(int);
	int GetY();
	void PutFi(double);//класса
	void PutAlpha(double);
	void Show();// «показать» объект
	void Hide();      // «спрятать» объект
	void Round(double);     // вращение вокруг внешнего центра
	void Turn(double);    // вращение квадрата
	void Orbit(double);    //верхние два варещния одоновременно
};
/*  определение методов объявленного класса*/
Quadrate::Quadrate(int X, int Y, int R, double Fi, int X_C, int Y_C,int Rad, double Alpha)
{
	this->X = X;
	this->Y = Y;
	this->R = R;
	this->Fi = Fi;
	this->X_C = X_C;
	this->Y_C = Y_C;
	this->Alpha = Alpha;
	this->Rad = Rad;
}
int Quadrate::GetX() { return(X); }
void Quadrate::PutX(int X) { this->X = X; }
int Quadrate::GetY() { return(Y); }
void Quadrate::PutY(int Y) { this->Y = Y; }
void Quadrate::PutFi(double Fi) { this->Fi = Fi; }
void Quadrate::PutAlpha(double Alpha) { this->Alpha = Alpha; }

void Quadrate::Show()
{
	int X1, Y1, X2, Y2;  // рабочие переменные-координаты концов
	int X3, Y3, X4, Y4; //двух пересекающихся осей колеса
	X1 = X + R * sin(Fi+M_PI_4);//
	Y1 = Y - R * cos(Fi+ M_PI_4);//  расчёт
	X2 = X + R * sin(Fi + 3*M_PI_4);// координат
	Y2 = Y - R * cos(Fi + 3*M_PI_4);// 
	X3 = X + R * sin(Fi + 5*M_PI_4);//
	Y3 = Y - R * cos(Fi + 5* M_PI_4);// вершин
	X4 = X + R * sin(Fi + 7*M_PI_4);// 
	Y4 = Y - R * cos(Fi + 7*M_PI_4);// квадрата
	line(X1, Y1, X2, Y2);
	line(X2, Y2, X3, Y3);
	line(X3, Y3, X4, Y4);
	line(X4, Y4, X1, Y1);
}
void Quadrate::Hide()
{ 
	//Чтобы спрятать объект, нужно:
	unsigned TempColor;// создать рабочую переменную, 
	TempColor = getcolor();// запомнить текущий цвет линий,
	setcolor(getbkcolor());//изменить цвет линий на цвет фона,
	Show();               //нарисовать объект цветом фона,
	setcolor(TempColor); //вернуть прежний цвет линий.
}
void Quadrate::Round(double D_Alpha)
{
	Hide();             // спрятать квадрат
	PutAlpha(Alpha + D_Alpha);
	PutX(X_C - Rad * sin(Alpha)); // изменить координату центра
	PutY(Y_C + Rad * cos(Alpha));
	Show();//показать квадрат
}
void Quadrate::Turn(double DFi)
{
	// Чтобы повернуть квадрат, нужно
	Hide();// спрятать квадрат,
	PutFi(Fi + DFi);// изменить угол поворота
	Show();            // и показать квадрат
}
void Quadrate::Orbit(double DFi)
{
	Turn(DFi); //Вращаем
	Round(DFi); //Угол один и тот же чтобы синхронизировать вращениe
}
/*создание и использование графических объектов в основной программе */
int main()
{
	char path[] = "";
	int gdriver = DETECT, gmode, errorcode;// блок
	initgraph(&gdriver, &gmode, path);// инициализации
	errorcode = graphresult();// графического режима
	if (errorcode != grOk)
	{
		cout << "Graphic error: " << grapherrormsg(errorcode) << endl;
		cout << "Press any key to halt:" << endl;
		getch();
		return(1);
	}
	setcolor(15);// цвет линий–ярко белый
	Quadrate W1(320, 50, 20, 0, 0, 0, 0, 0);// создание объектов класса Wheel 
	Quadrate W2(100, 250, 20, 0, 200, 250, 100, 0);  
	Quadrate W3(500, 300, 20, 0, 400, 250, 100, 0);          
	W1.Show();
	
	getch();//остановить программу и ждать нажатия клавиши 
	while (!kbhit())// повторять до нажатия клавиши
	{
		W1.Turn(0.2);
		W2.Round(0.1);  
		W3.Orbit(0.1);    
		delay(100);// задержка изображения на экране
	};
	getch();
	closegraph();
	return(0);
};