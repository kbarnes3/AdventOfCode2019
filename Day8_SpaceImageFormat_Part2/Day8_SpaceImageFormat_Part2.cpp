// Day8_SpaceImageFormat_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include <algorithm>
#include <iostream>
#include <numeric>

template<unsigned int Size, unsigned int Width, unsigned int Height>
std::array<int, Width * Height> Flatten(const std::array<int, Size>& data)
{
    std::array<int, Width * Height> flat;
    flat.fill(2);

    typename std::array<int, Width * Height>::iterator flatIter = flat.begin();
    typename std::array<int, Size>::const_iterator layerIter = data.cbegin();

    while (layerIter != data.cend())
    {
        if (*flatIter == 2)
        {
            *flatIter = *layerIter;
        }

        ++flatIter;
        if (flatIter == flat.end())
        {
            flatIter = flat.begin();
        }
        ++layerIter;
    }

    return flat;
}

template<size_t Size, unsigned int Width, unsigned int Height>
void Solve(const std::array<int, Size>& data)
{
    std::array<int, Width * Height> flat = Flatten<Size, Width, Height>(data);
    typename std::array<int, Width * Height>::const_iterator flatIter = flat.cbegin();

    while (flatIter != flat.cend())
    {
        for (unsigned int w = 0; w < Width; w++)
        {
            if (*flatIter == 0)
            {
                std::wcout << L' ';
            }
            else if (*flatIter == 1)
            {
                std::wcout << L'X';
            }
            else
            {
                std::wcout << *flatIter;
            }
            ++flatIter;
        }
        std::wcout << L'\n';
    }
}

int main()
{
    Solve<real_data.size(), real_data_width, real_data_height>(real_data);
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
