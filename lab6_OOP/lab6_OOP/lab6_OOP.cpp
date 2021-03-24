#define _USE_MATH_DEFINES
#include <graphics.h>
#include <iostream>
#include <math.h>

using namespace std;
class Point // объявление класса Point
{
protected:
	int X;
	int Y;
	int Color;
public:
	Point(int, int, int);
	Point() {};
	int GetX();
	int GetY();
	int GetC(); // возвращает значение поля Color
	void PutX(int);
	void PutY(int);
	void PutColor(int);
	void Show();
	void Hide();
	void MoveTo(int, int);
};

class Line
{
protected:
	Point P1;
	Point P2;
public:
	Line(Point, Point);
	Line();
	void Show();
	void Hide();
	void MoveTo(int,int);
	int Len();
};

class Ellipse1
{
protected:
	Point Center;
	Line L1;
	Line L2;
public:
	Ellipse1(Point, Line, Line);
	Ellipse1();
	void Show();
	void Hide();
};

class Ellipsoid
{
protected:
	Ellipse1 Ellipsoid_mas[3];
public:
	Ellipsoid(Ellipse1, Ellipse1, Ellipse1);
	void Show();
	void Hide();
};

/* определение методов объявленных классов */

Point::Point(int X, int Y, int Color) {
	this->X = X;
	this->Y = Y;
	this->Color = Color;
}

int Point::GetX() { return (X); }
int Point::GetY() { return (Y); }
int Point::GetC() { return (Color); }
void Point::PutX(int X) { this->X = X; }
void Point::PutY(int Y) { this->Y = Y; }
void Point::PutColor(int Color) { this->Color = Color; }
void Point::Show() { putpixel(X, Y, Color); }
void Point::Hide()
{
	unsigned char TempColor; // создать рабочую переменную,
	TempColor = getcolor(); // запомнить текущий цвет линий,
	setcolor(getbkcolor()); // изменить цвет линий на цвет фона,
	Show(); // нарисовать объект цветом фона,
	setcolor(TempColor); // вернуть прежний цвет линий.
}

void Point::MoveTo(int X, int Y) {
	Hide();
	PutX(X);
	PutY(Y);
	Show();
}

Line::Line(Point P1, Point P2)
{
	this->P1 = P1;
	this->P2 = P2;
}

Line::Line() {};
void Line::Show() { line(P1.GetX(), P1.GetY(), P2.GetX(), P2.GetY()); }

void Line::Hide()
{
	unsigned char TempColor; // создать рабочую переменную,
	TempColor = getcolor(); // запомнить текущий цвет линий,
	setcolor(getbkcolor()); // изменить цвет линий на цвет фона,
	Show(); // нарисовать объект цветом фона,
	setcolor(TempColor); // вернуть прежний цвет линий.
}
void Line::MoveTo(int DX, int DY)
{
	Hide();
	P1.PutX(P1.GetX() + DX);
	P1.PutY(P1.GetY() + DY);
	P2.PutX(P2.GetX() + DX);
	P2.PutY(P2.GetY() + DY);
	Show();
}
int Line::Len()
{
	return(sqrt((P2.GetX() - P1.GetX()) * (P2.GetX() - P1.GetX()) + (P2.GetY() - P1.GetY()) * (P2.GetY() - P1.GetY())));
}
Ellipse1::Ellipse1(Point Center, Line L1, Line L2)
{
	this->Center = Center;
	this->L1 = L1;
	this->L2 = L2;
}

Ellipse1::Ellipse1() {}
void Ellipse1::Show() { ellipse(Center.GetX(), Center.GetY(), 0, 360, L1.Len(), L2.Len()); }

void Ellipse1::Hide()
{
	unsigned char TempColor; // создать рабочую переменную,
	TempColor = getcolor(); // запомнить текущий цвет линий,
	setcolor(getbkcolor()); // изменить цвет линий на цвет фона,
	Show(); // нарисовать объект цветом фона,
	setcolor(TempColor); // вернуть прежний цвет линий.
}

Ellipsoid::Ellipsoid(Ellipse1 p1, Ellipse1 p2, Ellipse1 p3)
{
	this->Ellipsoid_mas[0] = p1;
	this->Ellipsoid_mas[1] = p2;
	this->Ellipsoid_mas[2] = p3;
}

void Ellipsoid::Show()
{
	for (int i = 0; i < 3; i++)
		Ellipsoid_mas[i].Show();
}

void Ellipsoid::Hide()
{
	unsigned char TempColor; // создать рабочую переменную,
	TempColor = getcolor(); // запомнить текущий цвет линий,
	setcolor(WHITE); // изменить цвет линий на цвет фона,
	Show(); // нарисовать объект цветом фона,
	setcolor(TempColor); // вернуть прежний цвет линий.
}

int main()
{
	int gdriver = DETECT, gmode, errorcode;
	char path[] = "";
	initgraph(&gdriver, &gmode, path);
	errorcode = graphresult();
	if (errorcode != grOk)
	{
		cout << "Ошибка графики: " << grapherrormsg(errorcode) << endl;
		cout << "Нажмите любую клавишу для прерывания:" << endl;
		getch(); return(1);
	}

	setcolor(15);
	bar(0, 0, getmaxx(), getmaxy());
	setbkcolor(15);
	setcolor(0);

	Point P1(60, 20, 4); // создание объекта P1 класса Point
	Point P2(150, 40, 4);
	Point C1(300, 150, 4);
	Point C2(350, 200, 4);
	Line L1(P1, P2); // создание объекта P2 класса Line
	Line L2(C1, C2);
	Ellipse1 E1(C1, L1, L2);
	//Ellipse1 E2(MP1, 70, 40);
	//Ellipse1 E3(MP1, 20, 40);
	//Ellipse1 E4(MP1, 70, 10);
	//Ellipsoid f1(E2, E3, E4);
	//outtext("C++");
	getch();
	L1.Show();
	E1.Show();
	//f1.Show();
	getch();
	closegraph();
	return(0);

};
/* использование разработанных классов в основной программе 
int main()
{
	setlocale(LC_ALL, "Russian");
	int gdriver = DETECT, gmode, errorcode;
	char path[] = "";
	initgraph(&gdriver, &gmode, path);
	errorcode = graphresult();
	if (errorcode != grOk)
	{
		cout << "Ошибка графики: " << grapherrormsg(errorcode) << endl;
		cout << "Нажмите любую клавишу для прерывания:" << endl;
		getch(); return(1);
	}
	setcolor(15);
	bar(0, 0, getmaxx(), getmaxy());
	setbkcolor(15);
	setcolor(0);
	Point P1(100, 100); // создание объекта "точка"
	P1.Show(); getch();
	Point P2 = Point(200, 200); // создание объекта "точка"
	P2.Show(); getch();
	Line L(P1, P2); // создание объекта с использованием "точек"
	L.Show();
	getch();
	closegraph();
	return(0);
};*/