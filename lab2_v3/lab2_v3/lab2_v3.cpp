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
	int GetX();
	int GetY();
	int GetC();
	void PutX(int);
	void PutY(int);
	void PutColor(int);
	void Show();
	void Hide();
	void MoveTo(int, int);
};
class Segment : public Point // класс Segment – наследник класса Point
{
protected:
	int Radius;
	double Fi;
public:
	Segment(int, int, int, int, double);
	int GetRadius();
	void PutRadius(int);
	double GetFi();
	void PutFi(double);
	void Draw();
	void Clean();
	void Move(int, int);
	void Expand(int);
};
class Ellipse1 : public Segment // класс Ellipse – наследник класса Segment
{
protected:
	int YRadius;
public:
	Ellipse1(int, int, int, int, int);
	int GetYRadius();
	void PutYRadius(int);
	void Draw2();
	void Clean2();
	void Expand2(int, int);
	void Move2(int, int);
	double Area();
};
class Ellipsoid : public Ellipse1 // класс Ellipsoid – наследник класса Ellipse
{
protected:
	int ZRadius;
public:
	Ellipsoid(int, int, int, int, int, int);
	void Draw3();
	void Clean3();
	void Expand3(int, int);
	void Move3(int, int);
	double Vol();
};

Point::Point(int X, int Y, int Color)
{
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
void Point::Hide() { putpixel(X, Y, getbkcolor()); }
void Point::MoveTo(int X, int Y) {
	Hide();
	PutX(X);
	PutY(Y);
	Show();
}

Segment::Segment(int X, int Y, int Color, int Radius, double Fi) : Point(X, Y, Color)
{
	this->Fi = Fi;
	this->Radius = Radius;
}
int Segment::GetRadius() { return (Radius); }
void Segment::PutRadius(int Radius) { this->Radius = Radius; }
double Segment::GetFi() { return (Fi); }
void Segment::PutFi(double Fi) { this->Fi = Fi; }
void Segment::Draw()
{
	int TempColor;
	TempColor = getcolor();
	setcolor(Color);
	line(X, Y, X + round(Radius * cos(Fi)), Y - round(Radius * sin(Fi)));
	setcolor(TempColor);
}
void Segment::Clean()
{
	int TempColor;
	TempColor = GetC();
	PutColor(getbkcolor());
	Draw();
	PutColor(TempColor);
}
void Segment::Move(int X, int Y)
{
	Clean();
	PutX(X);
	PutY(Y);
	Draw();
}
void Segment::Expand(int DR)
{
	Clean();
	PutRadius(Radius + DR);
	Draw();
}

Ellipse1::Ellipse1(int X, int Y, int Color, int Radius, int YRadius) : Segment(X, Y, Color, Radius, 0)
{
	this->YRadius = YRadius;
}
int Ellipse1::GetYRadius() { return (YRadius); }
void Ellipse1::PutYRadius(int YRadius) { this->YRadius = YRadius; }
void Ellipse1::Draw2()
{
	int TempColor;
	TempColor = getcolor();
	setcolor(Color);
	ellipse(X, Y, 0, 360, Radius, YRadius);
	setcolor(TempColor);
}
void Ellipse1::Clean2()
{
	int TempColor;
	TempColor = GetC();
	PutColor(getbkcolor());
	Draw2();
	PutColor(TempColor);
}
void Ellipse1::Expand2(int DXR, int DYR)
{
	Clean2();
	if (GetRadius() >= -DXR) PutRadius(Radius + DXR);
	if (GetYRadius() >= -DYR) PutYRadius(YRadius + DYR);
	Draw2();
}
void Ellipse1::Move2(int X, int Y)
{
	Clean2();
	PutX(X);
	PutY(Y);
	Draw2();
}
double Ellipse1::Area()
{
	return(M_PI * Radius * YRadius);
}

Ellipsoid::Ellipsoid(int X, int Y, int Color, int Radius, int YRadius, int ZRadius) : Ellipse1(X, Y, Color, Radius, YRadius)
{
	this->ZRadius = ZRadius;
};
void Ellipsoid::Draw3() {
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
void Ellipsoid::Clean3() {
	int TempColor;
	TempColor = GetC();
	PutColor(getbkcolor());
	Draw3();
	PutColor(TempColor);
}
void Ellipsoid::Expand3(int DXR, int DYR)
{
	Clean3();
	if (GetRadius() >= -DXR) PutRadius(Radius + DXR);
	if (GetYRadius() >= -DYR) PutYRadius(YRadius + DYR);
	Draw3();
}
void Ellipsoid::Move3(int X, int Y)
{
	Clean3();
	PutX(X);
	PutY(Y);
	Draw3();
}
double Ellipsoid::Vol()
{
	return(4 / 3 * M_PI * Radius * YRadius * ZRadius);
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
	S1.Draw();
	C1.Draw2();
	E1.Draw3();
	getch();
	P1.MoveTo(100, 100);
	S1.Move(100, 350);
	C1.Move2(400, 100);
	E1.Move3(400, 300);
	getch();
	S1.Expand(50);
	C1.Expand2(50, 0);
	E1.Expand3(50, 0);
	getch();
	S1.Expand(-50);
	C1.Expand2(-50, 0);
	E1.Expand3(-50, 0);
	getch();
	C1.Expand2(0, 50);
	E1.Expand3(0, 70);
	getch();
	C1.Expand2(0, -50);
	E1.Expand3(0, -70);
	getch();
	P1.Hide();
	S1.Clean();
	C1.Clean2();
	E1.Clean3();
	getch();
	cout << "Площадь: " << C1.Area() << endl;
	cout << "Объем: " << E1.Vol() << endl;
	closegraph();
	return(0);
};