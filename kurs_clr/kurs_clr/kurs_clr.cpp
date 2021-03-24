#include "pch.h"
#include <stdio.h>
#include <chrono>
using namespace System;

int main(array<System::String^>^ args)
{

        auto t1 = std::chrono::high_resolution_clock::now();

        unsigned int N = 100000;
        unsigned int* arr = new unsigned int[N];

        for (unsigned int i = 0; i < N; i++)
        {
            arr[i] = i;
        }

        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = t2 - t1;

        printf("%f seconds\n", elapsed_seconds.count());
    return 0;
}