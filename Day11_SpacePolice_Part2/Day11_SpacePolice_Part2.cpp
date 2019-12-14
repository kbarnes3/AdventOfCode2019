// Day11_SpacePolice_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <Data.h>
#include "Computer.h"
#include <iostream>
#include <numeric>
#include "Robot.h"

PanelColor GetPanelColor(const std::map<std::pair<long long, long long>, PanelColor>& panels, long long x, long long y)
{
    std::map<std::pair<long long, long long>, PanelColor>::const_iterator iter =
        panels.find(std::make_pair(x, y));

    if (iter != panels.cend())
    {
        return iter->second;
    }
    else
    {
        return PanelColor::Black;
    }
}

void Print(const std::map<std::pair<long long, long long>, PanelColor>& panels)
{
    long long minX = std::numeric_limits<long long>::max();
    long long maxX = std::numeric_limits<long long>::min();
    long long minY = std::numeric_limits<long long>::max();
    long long maxY = std::numeric_limits<long long>::min();

    for (const std::pair<std::pair<long long, long long>, PanelColor>& entry : panels)
    {
        minX = std::min(minX, entry.first.first);
        maxX = std::max(maxX, entry.first.first);
        minY = std::min(minY, entry.first.second);
        maxY = std::max(maxY, entry.first.second);
    }

    for (long long y = maxY; y >= minY; y--)
    {
        for (long long x = maxX; x >= minX; x--)
        {
            PanelColor color = GetPanelColor(panels, x, y);
            wchar_t output = ( color == PanelColor::White) ? L'#' : L' ';
            std::wcout << output;
        }
        std::wcout << L'\n';
    }
}

template<typename T, size_t Size>
void Solve(const std::array<T, Size>& data)
{
    Computer<T, true> computer(data.cbegin(), data.cend());
    Robot robot;

    while (!computer.Terminated())
    {
        std::optional<T> output = computer.Process();

        // Process() returns for one of three reasons:
        // 1. It terminated
        // 2. It generated data for the robot
        // 3. It needs input from the robot
        if (computer.Terminated())
        {
            break;
        }
        if (output.has_value())
        {
            robot.Input(output.value());
        }
        else
        {
            PanelColor color = robot.GetPanelColor();
            computer.AddInput(static_cast<T>(color));
        }
    }

    const std::map<std::pair<long long, long long>, PanelColor> panels = robot.GetPanels();
    Print(panels);
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
