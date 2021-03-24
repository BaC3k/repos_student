#include <math.h>
#include <iostream>

using namespace std;
void solve_equation(double, double);
void solve_integral(double, double, double, int);
double f2(double x);
int main()
{
	solve_equation(0.001, 1.3077);
	cout << endl;
	solve_integral(0.001, 1, 4, 52);
	system("pause");
	return 0;
}

void solve_equation(double e, double x0)
{
	double x=x0, x1;
	int k = 1;
	do
	{
		x1 = x;
		x = 2 * sin(1 / x1);
		k++;
	} while (abs(x - x1) > e);
	cout << k << " iterations" << endl;
	cout << "x = 2*sin(1/x) = " << x << endl;
	cout << "x accuracy = " << abs(x - x1) << endl;
}

void solve_integral(double precision, double a, double b, int n)
{
	double S0 = 0, S1 = 0, h;
	int k = 5, i, j = 1;

	h = fabs(b - a) / n;

	for (i = 0; i < n; i++)
		S0 += f2(a + h * i) * h;

	S0 += (f2(a) + f2(b)) * h / 2;

	while (1)
	{
		j++;
		n += k;
		h = fabs(b - a) / n;
		S1 = 0;

		for (i = 0; i < n; i++)
			S1 += f2(a + h * i) * h;

		S1 += (f2(a) + f2(b)) * h / 2;

		if ((fabs(S0 - S1) <= precision))
		{
			cout << "Value of integral = " << S1 << endl;
			cout << "Integral was found during " << j << " iterations.\n";
			return;
		}

		else
			S0 = S1;
	}
}

double f2(double x)
{
	if (fabs(x) < 0.0005 / 2)
	{
		cout << "Error'\n";
		return (0);
	}
	return (log(x) * log(x) / x);
}