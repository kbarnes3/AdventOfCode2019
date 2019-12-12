// Day10_MonitoringStation_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include <iostream>
#include <numeric>

template<size_t Width, size_t Height>
bool IsAsteroidVisible(
    const std::array<std::array<bool, Width>, Height>& data,
    size_t x1,
    size_t y1,
    size_t x2,
    size_t y2)
{
    ptrdiff_t xDiff = x2 - x1;
    ptrdiff_t yDiff = y2 - y1;

    // The two asteroids are visible if nothing is in between them
    ptrdiff_t gcd = std::gcd(xDiff, yDiff);

    ptrdiff_t xStep = xDiff / gcd;
    ptrdiff_t yStep = yDiff / gcd;

    size_t x = x1 + xStep;
    size_t y = y1 + yStep;

    while (x != x2 || y != y2)
    {
        if (data[y][x])
        {
            return false;
        }

        x += xStep;
        y += yStep;
    }

    return true;
}

template<size_t Width, size_t Height>
unsigned int CountVisibleAsteroids(
    const std::array<std::array<bool, Width>, Height>& data,
    size_t targetX,
    size_t targetY)
{
    unsigned int visible = 0;

    for (size_t y = 0; y < Height; y++)
    {
        for (size_t x = 0; x < Width; x++)
        {
            if (data[y][x] &&
                !(x == targetX && y == targetY))
            {
                if (IsAsteroidVisible(data, targetX, targetY, x, y))
                {
                    visible++;
                }
            }
        }
    }

    return visible;
}

template<size_t Width, size_t Height>
void Solve(const std::array<std::array<bool, Width>, Height>& data)
{
    unsigned int maxVisible = 0;

    for (size_t y = 0; y < Height; y++)
    {
        for (size_t x = 0; x < Width; x++)
        {
            if (data[y][x])
            {
                unsigned int visible = CountVisibleAsteroids(data, x, y);
                maxVisible = std::max(maxVisible, visible);
            }
        }
    }

    std::wcout << maxVisible << L'\n';

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
