// Day09_SensorBoost_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include "Computer.h"
#include <iostream>

template<typename T, size_t Size>
void Solve(const std::array<T, Size>& data)
{
    Computer<T, false> computer(data.cbegin(), data.cend());

    computer.AddInput(2);
    std::vector<T> output = computer.Process();

    for (T out : output)
    {
        std::wcout << out << L'\n';
    }
}

int main()
{
    Solve(real_data);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
