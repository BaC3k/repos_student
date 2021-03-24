
#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    const int N = 9;
    double a_i, b_i, c_i, d_i;
    double A[N][N+1] = {
    {-8,-1,  0,   0,  0,  0,  0,  0,   0, -20},
    {-4, 7, -3,   0,  0,  0,  0,  0,   0, -34},
    { 0, 2, 10,   4,  0,  0,  0,  0,   0, -44},
    { 0, 0, -4, -10, -3,  0,  0,  0,   0,  45},
    { 0, 0,  0,  -4,  8, -5,  0,  0,   0,  49},
    { 0, 0,  0,   0,  2,  9,  3,  0,   0, -28},
    { 0, 0,  0,   0,  0, -4,  7,  1,   0,  60},
    { 0, 0,  0,   0,  0,  0, -5, -7,  -3, -57},
    { 0, 0,  0,   0,  0,  0,  0,  5, -10,  35},
    };
    double P[N+1], Q[N+1], X[N+1];
    //Прямой ход прогонки
    P[0] = 0;
    Q[0] = 0;

    //Расчёт коэффициентов
    for (int i = 0; i < N; i++)
    {
        if (i > 0)
            a_i = A[i][i - 1];
        else a_i = 0;
    
        b_i = A[i][i];

        if (i < N - 1)
            c_i = A[i][i + 1];
        else c_i = 0;

        d_i = A[i][N];
    
        P[i+1] = -c_i / (b_i + (a_i * P[i]));
        Q[i+1] = (d_i - a_i * Q[i]) / (b_i + (a_i * P[i]));
    }
    
    //Обратный ход прогонки
    X[N] = Q[N];

    cout.precision(7);
    cout << fixed;
    cout << "№\t X\t\t P\t\t Q\n";
    cout << 9<<"\t"<<X[N]<<"\t"<<P[N]<<"\t"<<Q[N]<<"\n";

    for (int i = N - 1; i > 0; i--)
    {
        X[i] = Q[i] + (P[i] * X[i + 1]);
        cout << i << "\t" << X[i] << "\t" << P[i] << "\t" << Q[i] << "\n";
    }
    system("pause");
}

