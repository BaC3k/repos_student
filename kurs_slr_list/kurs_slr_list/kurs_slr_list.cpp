#include "pch.h"
#include <stdio.h>
#include <chrono>
#include <vector>
using namespace System;

int main(array<System::String^>^ args)
{
    auto t1 = std::chrono::high_resolution_clock::now();

    unsigned int N = 100;
    std::vector<unsigned int> arr;
    for (unsigned int i = 0; i < N; i++)
    {
        arr.push_back(i);
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = t2 - t1;

    printf(" %f seconds\n", elapsed_seconds.count());
    return 0;
}