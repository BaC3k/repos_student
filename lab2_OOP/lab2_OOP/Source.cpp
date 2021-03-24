#include <graphics.h>
#include <iostream>
#include <conio.h>
using namespace std;
class Point // объ€вление класса Point
{
protected:
	int X;
	int Y;
	int Color;
public:
	Point(int, int, int);
	int GetX();
	int GetY();
	int GetC(); // возвращает значение пол€ Color
	void PutX(int);
	void PutY(int);
	void PutColor(int);
	void Show();
	void Hide();
	void MoveTo(int, int);
};
class Circle : public Point // класс —ircle Ц наследник класса Point
{
protected:
	int Radius;
public:
	Circle(int, int, int, int);
	int GetRadius();
	void PutRadius(int);
	void Draw();
	void Clean();
	void Expand(int);
	void Move(int, int);
};
/* определение методов объ€вленных классов */
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
void Point::Hide() { putpixel(X, Y, getbkcolor()); }
void Point::MoveTo(int X, int Y) {
	Hide();
	PutX(X);
	PutY(Y);
	Show();
}
Circle::Circle(int X, int Y, int Color, int Radius) : Point(X, Y, Color)
// вызов конструктора класса-предка
{
	this->Radius = Radius;
} // инициализаци€ нового пол€ данных
int Circle::GetRadius() { return (Radius); }
void Circle::PutRadius(int Radius) { this->Radius = Radius; }
void Circle::Draw() {
	int TempColor;
	TempColor = getcolor();
	setcolor(Color);
	circle(X, Y, Radius);
	setcolor(TempColor);
}
void Circle::Clean() {
	int TempColor;
	TempColor = GetC();
	PutColor(getbkcolor());
	Draw();
	PutColor(TempColor);
}
void Circle::Expand(int DR)
{
	Clean();
	if (GetRadius() >= -DR) PutRadius(Radius + DR);
	Draw();
}

void Circle::Move(int X, int Y) {
	Clean();
	PutX(X);
	PutY(Y);
	Draw();
}
/* использование созданных классов в основной программе */
int main()
{
	int gdriver = DETECT, gmode, errorcode;
	char path[] = "";
	initgraph(&gdriver, &gmode, path);
	errorcode = graphresult();
	if (errorcode != grOk)
	{
		std::cout << "ќшибка графики: " << grapherrormsg(errorcode) << std::endl;
		std::cout << "Ќажмите любую клавишу дл€ прерывани€:" << std::endl;
		getch(); return(1);
	}
	setcolor(getmaxcolor());
	Point P1(100, 100, getcolor()); // создание объекта P1 класса Point
	P1.Show(); getch();
	P1.MoveTo(150, 150); getch();
	P1.Hide();
	Point P2 = Point(200, 200, 5); // создание объекта P2 класса Point
	P2.Show(); getch();
	P2.Hide();
	P2.PutX(360);
	P2.Show(); getch();
	P2.Hide();
	P2.PutY(250);
	P2.Show(); getch();
	P2.Hide();
	Circle C1(295, 100, 12, 70), C2(150, 250, 13, 50); // объекты C1 и C2 класса Circle
	C1.Draw(); getch();
	C1.Clean(); getch();
	C1.Draw(); getch();
	C1.Expand(10); getch();
	C1.Expand(-10); getch();
	C1.Clean(); getch();
	C2.Draw(); getch();
	C2.Clean();
	C2.PutX(360);
	C2.Draw(); getch();
	C2.Move(400, 300); getch();
	C2.Clean(); getch();
	closegraph();
	return(0);
};