// Day16_FlawedFrequencyTransmission_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include <iostream>
#include <utility>
#include <vector>

template<size_t Size>
void Solve(const std::array<int, Size>& data, unsigned int phaseCount)
{
    constexpr size_t repeatCount = 10000;
    constexpr size_t signalSize = Size * repeatCount;

    std::vector<int> prevPhase;
    prevPhase.reserve(signalSize);
    for (size_t i = 0; i < repeatCount; i++)
    {
        prevPhase.insert(prevPhase.cend(), data.cbegin(), data.cend());
    }

    const size_t outStart = data[0] * 1000000ull +
                            data[1] *  100000ull +
                            data[2] *   10000ull +
                            data[3] *    1000ull +
                            data[4] *     100ull +
                            data[5] *      10ull +
                            data[6] *       1ull;
    const size_t outEnd = outStart + 8;

    for (unsigned int phase = 0; phase < phaseCount; phase++)
    {
        std::wcout << L"Starting phase " << phase << L'\n';
        std::vector<int> newPhase(signalSize);
        newPhase[signalSize - 1] = prevPhase[signalSize - 1];

        size_t secondHalfEnd = std::max(signalSize / 2, outStart - 1);

        for (size_t i = signalSize - 2; i > secondHalfEnd; i--)
        {
            newPhase[i] = (newPhase[i + 1] + prevPhase[i]) % 10;
        }
        for (size_t i = outStart; i <= signalSize / 2; i++)
        {
            if (i % 1000 == 0)
            {
                std::wcout << L"Starting digit " << i << L'\n';
            }
            int digit = 0;
            std::array<int, 4>::const_iterator patternIter = base_pattern.cbegin() + 1;
            size_t patternDigitCount = 0;

            for (size_t j = i; j < signalSize; j++)
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

        prevPhase = std::move(newPhase);
    }

    for (size_t out = outStart; out < outEnd; out++)
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
