#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	cout.precision(7);
	cout << fixed;
	double x = 391.0 / 41, x1, y = -5.0 / 40, y1, z = 262.0 / 37, z1, e, delta, pogx, pogy, pogz;
	double arr[3][3] = { {0.0, -7.0 / 41, -6.0 / 41},
							{-9.0 / 30, 0.0, 1.0 / 40},
							{6.0 / -37, 7.0 / -37, 0.0} };
	//Высчитываем нормы
	double B1 = max(max((abs(arr[0][0]) + abs(arr[0][1]) + abs(arr[0][2])), (abs(arr[1][0]) + abs(arr[1][1]) + abs(arr[1][2]))), (abs(arr[2][0]) + abs(arr[2][1]) + abs(arr[2][2])));
	double B2 = max(max((abs(arr[0][0]) + abs(arr[1][0]) + abs(arr[2][0])), (abs(arr[0][1]) + abs(arr[1][1]) + abs(arr[2][1]))), (abs(arr[0][2]) + abs(arr[1][2]) + abs(arr[2][2])));
	double B = min(B1, B2);
	cout << "B1 = " << B1 << "; B2 = " << B2 << endl;
	if (B < 1) cout << "Минимальная из них B1, следовательно вычисляем бета; Т.к. B = " << B << " < 1, то итерационный процесс будет сходится к точному решению системы.\n";

	double beta = max(max(abs(x), abs(y)), abs(z));
	cout << "beta = " << beta << endl;

	cout << "№\t x\t\t y\t\t z\t\t e\t\t delta\n";
	cout << 0 << "\t" << x << "\t" << y << "\t" << z << endl;
	int k = 1;
	do
	{
		x1 = x;
		y1 = y;
		z1 = z;

		x = (-7 * y - 6 * z + 391) / 41;
		y = (-9 * x + z - 5) / 40;
		z = (6 * x + 7 * y - 262) / (-37);
		pogx = abs(x - x1);
		pogy = abs(y - y1);
		pogz = abs(z - z1);
		delta = max(max(pogx, pogy), pogz);
		e = pow(B, k) / (1 - B) * beta;

		cout << k << "\t" << x << "\t" << y << "\t" << z << "\t" << e << "\t" << delta << "\n";

		k++;
	} while (k <= 5);
	system("pause");
	return 0;

}