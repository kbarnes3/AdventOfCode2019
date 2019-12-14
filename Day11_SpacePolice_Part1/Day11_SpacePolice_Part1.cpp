// Day11_SpacePolice_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include "Computer.h"
#include <iostream>
#include "Robot.h"

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

    std::wcout << robot.PaintedPanelsCount() << L'\n';
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
