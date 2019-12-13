// Day03_CrossedWires_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <utility>
#include <vector>
#include <intrin.h>

typedef std::function<void(int, int, int)> TracingCallback;

template<size_t Size>
void trace_path(const std::array<Movement, Size>& path, TracingCallback callback)
{
    int x = 0;
    int y = 0;
    int length = 0;

    for (const Movement& move : path)
    {
        for (int i = 0; i < move.distance; i++)
        {
            length++;
            switch (move.direction)
            {
            case Direction::Up:
                y++;
                break;
            case Direction::Down:
                y--;
                break;
            case Direction::Left:
                x--;
                break;
            case Direction::Right:
                x++;
                break;
            default:
                __fastfail(-1);
            }

            callback(x, y, length);
        }
    }
}

template<size_t Size1, size_t Size2>
void solve(const std::array<Movement, Size1>& path1, const std::array<Movement, Size2>& path2)
{
    std::map<std::pair<int, int>, int> path1Trace;

    trace_path(path1, [&path1Trace](int x, int y, int length) {
        path1Trace.insert_or_assign(std::make_pair(x, y), length);
        });

    int shortestIntersection = std::numeric_limits<int>::max();

    trace_path(path2, [&path1Trace, &shortestIntersection](int x, int y, int length) {
        std::pair<int, int> point = std::make_pair(x, y);
        std::map<std::pair<int, int>, int>::const_iterator iter =
            path1Trace.find(point);
        if (iter != path1Trace.cend())
        {
            int intersectionLength = iter->second + length;
            shortestIntersection = std::min(shortestIntersection, intersectionLength);
        }
        });

    std::wcout << shortestIntersection << L'\n';

}

int main()
{
    solve(real_path_1, real_path_2);
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
