#define _USE_MATH_DEFINES
#include <graphics.h>
#include <iostream>
#include <math.h>
using namespace std;

class Location
{
protected:
	int X;
	int Y;
	int Radius;
public:
	Location(int, int, int);
	int GetX();
	int GetY();
	int GetRadius();
	void PutRadius(int);
	void PutX(int);
	void PutY(int);
	virtual void Show()=0; // чисто виртуальная функция – абстрактный метод
	virtual void Hide()=0; // чисто виртуальная функция – абстрактный метод
};
class Point: public Location // объявление класса Point
{
protected:
	int Color;
public:
	Point(int, int, int);
	int GetC();
	void PutColor(int);
	virtual void Show();
	void Hide();
	void MoveTo(int, int);
};
class Segment : public Point // класс Segment – наследник класса Point
{
protected:

	double Fi;
public:
	Segment(int, int, int, int, double);
	double GetFi();
	void PutFi(double);
	void Show();
};
class Ellipse1 : public Segment // класс Ellipse – наследник класса Segment
{
protected:
	int YRadius;
public:
	Ellipse1(int, int, int, int, int);
	int GetYRadius();
	void PutYRadius(int);
	void Show();
	double Area();
};
class Ellipsoid : public Ellipse1 // класс Ellipsoid – наследник класса Ellipse
{
protected:
	int ZRadius;
public:
	Ellipsoid(int, int, int, int, int, int);
	int GetZRadius();
	void PutZRadius(int);
	void Show();
	double Vol();
};

Location::Location(int X, int Y, int Radius)
{
	this->X = X;
	this->Y = Y;
	this->Radius = Radius;
}
int Location::GetX() { return X; }
int Location::GetY() { return Y; }
int Location::GetRadius() { return Radius; }
void Location::PutX(int X) { this->X = X; }
void Location::PutY(int Y) { this->Y = Y; }
void Location::PutRadius(int Radius) { this->Radius = Radius; }


Point::Point(int X, int Y, int Color) : Location(X, Y, 0) { this->Color = Color; }
int Point::GetC() { return (Color); }
void Point::PutColor(int Color) { this->Color = Color; }
void Point::Show() { putpixel(X, Y, Color); }
void Point::Hide()
{
	int TempColor;
	TempColor = GetC();
	PutColor(getbkcolor());
	Show();
	PutColor(TempColor);
}
void Point::MoveTo(int X, int Y) {
	Hide();
	PutX(X);
	PutY(Y);
	Show();
}

Segment::Segment(int X, int Y, int Color, int Radius, double Fi) : Point(X, Y, Color)
{
	this->Fi = Fi;
	this->PutRadius(Radius);
}
double Segment::GetFi() { return (Fi); }
void Segment::PutFi(double Fi) { this->Fi = Fi; }
void Segment::Show()
{
	int TempColor;
	TempColor = getcolor();
	setcolor(Color);
	line(X, Y, X + round(Radius * cos(Fi)), Y - round(Radius * sin(Fi)));
	setcolor(TempColor);
}

Ellipse1::Ellipse1(int X, int Y, int Color, int Radius, int YRadius) : Segment(X, Y, Color, Radius, 0)
{
	this->YRadius = YRadius;
}
int Ellipse1::GetYRadius() { return (YRadius); }
void Ellipse1::PutYRadius(int YRadius) { this->YRadius = YRadius; }
void Ellipse1::Show()
{
	int TempColor;
	TempColor = getcolor();
	setcolor(Color);
	ellipse(X, Y, 0, 360, Radius, YRadius);
	setcolor(TempColor);
}
double Ellipse1::Area()
{
	return(M_PI * Radius * YRadius);
}

Ellipsoid::Ellipsoid(int X, int Y, int Color, int Radius, int YRadius, int ZRadius) : Ellipse1(X, Y, Color, Radius, YRadius)
{
	this->ZRadius = ZRadius;
};
int Ellipsoid::GetZRadius() { return (ZRadius); }
void Ellipsoid::PutZRadius(int ZRadius) { this->ZRadius = ZRadius; }
void Ellipsoid::Show() {
	int TempColor;
	TempColor = getcolor();
	setcolor(Color);
	ellipse(X, Y, 0, 360, Radius, YRadius);
	ellipse(X, Y, -20, 20, Radius / 8, YRadius);
	ellipse(X, Y, 60, 300, Radius / 8, YRadius);
	ellipse(X, Y, 80, 100, Radius, YRadius / 8);
	ellipse(X, Y, 120, 420, Radius, YRadius / 8);
	setcolor(TempColor);
}
double Ellipsoid::Vol()
{
	return(4 / 3 * M_PI * Radius * YRadius * ZRadius);
}

void Move(int X, int Y, Location* pL)
{ // аргумент pL функции Move ― указатель на абстрактный объект
	pL->Hide();
	pL->PutX(X);
	pL->PutY(Y);
	pL->Show();
}

void Expand(int DXR, Location* pL)
{
	pL->Hide();
	pL->PutRadius(pL->GetRadius() +DXR);
	pL->Show();
}

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
	Point P1(50, 50, 4); // создание объекта P1 класса Point	
	Segment S1(50, 300, 9, 30, M_PI_4);
	Ellipse1 C1(300, 100, 12, 80, 30);
	Ellipsoid E1(300, 250, 10, 100, 50, 50);
	P1.Show();
	S1.Show();
	C1.Show();
	E1.Show();
	getch();
	Move(100, 100, &P1);
	Move(100, 350, &S1);
	Move(400, 100, &C1);
	Move(400, 300, &E1);
	getch();
	Expand(50, &S1);
	Expand(50, &C1);
	Expand(50, &E1);
	getch();
	Expand(-50, &S1);
	Expand(-50, &C1);
	Expand(-50, &E1);
	getch();
	P1.Hide();
	S1.Hide();
	C1.Hide();
	E1.Hide();
	getch();
	cout << "Площадь: " << C1.Area() << endl;
	cout << "Объем: " << E1.Vol() << endl;
	closegraph();
	return(0);
};