// Day04_SecureContainer_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include <array>
#include <iostream>

std::array<int, 6> Decompose(int sixDigitNumber)
{
    int remainingDigits = sixDigitNumber;
    std::array<int, 6> decomposed;

    for (size_t i = 6; i > 0; i--)
    {
        int digit = remainingDigits % 10;
        decomposed[i - 1] = digit;
        remainingDigits = remainingDigits / 10;
    }

    return decomposed;
}

bool HasAdjacentMatch(const std::array<int, 6>& digits)
{
    int streakingNumber = digits[0];
    size_t streak = 1;

    for (size_t i = 1; i < 6; i++)
    {
        if (digits[i] == streakingNumber)
        {
            streak++;
        }
        else
        {
            if (streak == 2)
            {
                return true;
            }
            streakingNumber = digits[i];
            streak = 1;
        }
    }

    return streak == 2;
}

bool IsNeverDecreasing(const std::array<int, 6>& digits)
{
    for (size_t i = 1; i < 6; i++)
    {
        if (digits[i] < digits[i - 1])
        {
            return false;
        }
    }

    return true;
}

void Solve(const std::pair<int, int>& range)
{
    unsigned int matches = 0;
    for (int test = range.first; test <= range.second; test++)
    {
        std::array<int, 6> digits = Decompose(test);
        bool hasAdjacentMatch = HasAdjacentMatch(digits);
        if (hasAdjacentMatch)
        {
            bool isNeverDecreasing = IsNeverDecreasing(digits);
            if (isNeverDecreasing)
            {
                matches++;
            }
        }
    }

    std::wcout << matches << L'\n';
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
