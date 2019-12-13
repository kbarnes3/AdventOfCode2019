// Day01_TheTyrannyOfTheRocketEquation_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Data.h>
#include <algorithm>
#include <numeric>

int ComputeFuel(int mass)
{
    int fuel = mass / 3;
    fuel -= 2;

    return fuel;
}

template<size_t Size>
void Solve(const std::array<int, Size>& masses)
{
    std::array<int, Size> fuels;
    std::transform(masses.begin(), masses.end(), fuels.begin(), ComputeFuel);

    int totalFuel = 0;
    totalFuel = std::accumulate(fuels.begin(), fuels.end(), totalFuel);

    std::wcout << totalFuel << L'\n';
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
