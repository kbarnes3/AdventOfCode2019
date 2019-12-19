// Day16_FlawedFrequencyTransmission_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include <iostream>

template<size_t Size>
void Solve(const std::array<int, Size>& data, unsigned int phaseCount)
{
    std::array<int, Size> prevPhase = data;
    for (unsigned int phase = 0; phase < phaseCount; phase++)
    {
        std::array<int, Size> newPhase;
        for (size_t i = 0; i < Size; i++)
        {
            int digit = 0;
            std::array<int, 4>::const_iterator patternIter = base_pattern.cbegin();
            size_t patternDigitCount = 1;

            for (size_t j = 0; j < Size; j++)
            {
                if (patternDigitCount >= i + 1)
                {
                    patternDigitCount = 0;
                    ++patternIter;
                    if (patternIter == base_pattern.cend())
                    {
                        patternIter = base_pattern.cbegin();
                    }
                }
                int value = prevPhase[j] * *patternIter;

                digit += value;
                patternDigitCount++;
            }

            digit = abs(digit) % 10;
            newPhase[i] = digit;
        }

        prevPhase = newPhase;
    }

    for (size_t out = 0; out < 8; out++)
    {
        std::wcout << prevPhase[out];
    }
    std::wcout << L'\n';
}

int main()
{
    Solve(real_data, 100);
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
