#include <iostream>
#include <math.h>
#include <cstdlib>
#include <locale>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	cout.precision(4);
	cout << fixed;
	int i = 0;
	double x, y, z, y1 = 0, z1 = 5, h = 0.1, f;

	for (x = 0.1; x <= 3; x += h)
	{
		i++;
		y = y1 + h * z1;
		z = z1 + h * (-50 * sin(y1) * cos(y1) * cos(y1) * cos(y1));
		f = -50 * sin(y) * cos(y) * cos(y) * cos(y);
		cout<< i <<"-тая итерация:"<<endl<< endl;
		cout << "x = " << x << endl;
		cout << "y = " << y << endl;
		cout << "z = " << z << endl;
		cout << "f = " << f << endl<< endl;
		y1 = y;
		z1 = z;
	}
	system("pause");
	return 0;

}