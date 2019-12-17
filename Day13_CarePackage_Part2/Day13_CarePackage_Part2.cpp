// Day13_CarePackage_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Computer.h"
#include <Data.h>
#include <iostream>
#include "ScreenState.h"

bool IsKeyDown(int key)
{
    constexpr short shifted = 0x80;
    short keyState = GetKeyState(key);

    return keyState & shifted;
}

long long GetJoystickInput()
{
    if (IsKeyDown(VK_LEFT))
    {
        return -1;
    }
    else if (IsKeyDown(VK_RIGHT))
    {
        return 1;
    }

    return 0;
}

long long SimulateJoystickInput(const ScreenState& screen)
{
    std::pair<long long, long long> paddle = screen.GetFirstTile(ScreenTile::Paddle);
    std::pair<long long, long long> ball = screen.GetFirstTile(ScreenTile::Ball);

    if (ball.first == paddle.first)
    {
        return 0;
    }

    if (ball.first < paddle.first)
    {
        return -1;
    }

    return 1;
}

template<size_t Size>
void Solve(const std::array<long long, Size>& data)
{
    Computer<long long, true> computer(data.cbegin(), data.cend());
    ScreenState screen;

    Sleep(1000);
    computer.HackMemory(0, 2);

    while (!computer.Terminated())
    {
        std::optional<long long> output = computer.Process();

        // Process() returns for one of three reasons:
        // 1. It terminated
        // 2. It generated data for the screen
        // 3. It needs input from the joystick
        if (computer.Terminated())
        {
            break;
        }
        if (output.has_value())
        {
            screen.Input(output.value());
        }
        else
        {
            Sleep(16);
            long long joystick = SimulateJoystickInput(screen);
            computer.AddInput(joystick);
        }
    }
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
