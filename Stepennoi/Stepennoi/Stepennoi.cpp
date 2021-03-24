#include <iostream>
#include <cmath>

using namespace std;

const int N = 3;
void matrix_multiply(double (*a)[3], double* b, double* c)
{
    for (int i = 0; i < N; i++)
    {
        c[i] = 0;
        for (int j = 0; j < N; j++)
            c[i] += a[i][j] * b[j];
    }
}
double vector_multiply(double* a, double* b, int n)//Скалярное произведение векторов
{
    double c=0;
    for (int i = 0; i < n; i++)
        c += a[i] * b[i];
    return c;

}
int main()
{
    setlocale(LC_ALL, "Russian");

    cout.precision(7);
    cout << fixed;
    double p, v_norm;
    int iter = 10;
    double A[N][N] = {
        {5, -2, 8},
        {-2, 8, -16},
        {8, -16, 13}
    };
    double V[N], W[N] = { 1.0 / sqrt(3), 1.0 / sqrt(3), 1.0 / sqrt(3) };

    cout << "Вектор\t v1(w1)\t\t v2(w2)\t\t v3(w3)\t\t p\n";
    for (int i = 0; i < iter; i++)
    {

        cout << "W("<<i<<")\t";
        for (int j = 0; j < N; j++)
            cout << W[j] << "\t";


        matrix_multiply(A, W, V);
        p = vector_multiply(V, W, N);

        cout << "\nV(" << i+1 << ")\t";
        for (int j = 0; j < N; j++)
            cout << V[j] << "\t";
        cout << p << "\n";

        //Нормализуем вектор V
        v_norm = 0;
        for (int j = 0; j < N; j++)
            v_norm += V[j] * V[j];
        v_norm = sqrt(v_norm);
        // cout << v_norm << " нормализованный вектор\n";

        for (int j = 0; j < N; j++)
            W[j] = V[j] / v_norm;
    }
    system("pause");
}

