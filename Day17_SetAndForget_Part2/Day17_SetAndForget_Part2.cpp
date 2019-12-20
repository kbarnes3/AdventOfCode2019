// Day17_SetAndForget_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Computer.h>
#include <Data.h>
#include <iostream>
#include <string>
#include <vector>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void PrintCameraOutput(HANDLE consoleOut, const std::vector<std::vector<char>>& output)
{
    SetConsoleCursorPosition(consoleOut, { 0, 0 });
    for (const std::vector<char>& row : output)
    {
        for (char character : row)
        {
            std::cout << character;
        }
        std::cout << '\n';
    }
    Sleep(100);
}

template<size_t Size>
void Solve(const std::array<long long, Size>& intCode)
{
    HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);

    const std::string program = "A,B,A,C,A,B,C,A,B,C\nR,12,R,4,R,10,R,12\nR,6,L,8,R,10\nL,8,R,4,R,4,R,6\ny\n";
    Computer<long long, true> computer(intCode.cbegin(), intCode.cend());
    std::vector<std::vector<char>> cameraOutput;

    for (char instruction : program)
    {
        computer.AddInput(instruction);
    }

    computer.HackMemory(0, 2);

    std::vector<std::vector<char>>::iterator currentRow =
        cameraOutput.insert(cameraOutput.cend(), std::vector<char>());

    std::optional<long long> output;
    long long lastOutput = 0;
    do
    {
        output = computer.Process();
        if (!output.has_value())
        {
            break;
        }

        lastOutput = output.value();

        if (output.value() == 10)
        {
            // End of line, make a new line or print the output if this an empty line
            if (currentRow->empty())
            {
                cameraOutput.erase(currentRow);
                PrintCameraOutput(consoleOut, cameraOutput);
                cameraOutput.clear();
                currentRow = cameraOutput.insert(cameraOutput.cend(), std::vector<char>());
            }
            currentRow = cameraOutput.insert(cameraOutput.cend(), std::vector<char>());
        }
        else
        {
            currentRow->push_back(static_cast<char>(output.value()));
        }

    } while (output.has_value());

    if (!computer.Terminated())
    {
        FAIL_FAST();
    }

    std::cout << lastOutput << '\n';
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
