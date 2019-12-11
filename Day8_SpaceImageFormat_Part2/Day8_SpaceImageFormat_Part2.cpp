// Day8_SpaceImageFormat_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include <algorithm>
#include <iostream>
#include <numeric>

template<size_t Size>
void Solve(const std::array<int, Size>& data, unsigned int width, unsigned int height)
{
    const unsigned int pixelsInLayer = width * height;
    typename std::array<int, Size>::const_iterator layerStart = data.cbegin();
    unsigned int minZeros = std::numeric_limits<unsigned int>::max();
    unsigned int product = 0;

    while (layerStart != data.cend())
    {
        typename std::array<int, Size>::const_iterator layerIter = layerStart;
        typename std::array<int, Size>::const_iterator layerEnd = layerStart + pixelsInLayer;
        unsigned int numZeros = 0;
        unsigned int numOnes = 0;
        unsigned int numTwos = 0;

        while (layerIter != layerEnd)
        {
            switch (*layerIter)
            {
            case 0:
                numZeros++;
                break;
            case 1:
                numOnes++;
                break;
            case 2:
                numTwos++;
                break;
            }

            ++layerIter;
        }

        if (numZeros < minZeros)
        {
            minZeros = numZeros;
            product = numOnes * numTwos;
        }

        layerStart = layerEnd;
    }

    std::wcout << product << L'\n';
}

int main()
{
    Solve(real_data, real_data_width, real_data_height);
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
