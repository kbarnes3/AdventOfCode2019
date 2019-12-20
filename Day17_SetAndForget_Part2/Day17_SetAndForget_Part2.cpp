// Day17_SetAndForget_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Computer.h>
#include <Data.h>
#include <iostream>
#include <vector>

void PrintCameraOutput(const std::vector<std::vector<char>>& output)
{
    for (const std::vector<char>& row : output)
    {
        for (char character : row)
        {
            std::cout << character;
        }
        std::cout /*<< "\\n"*/ << '\n';
    }
}

template<size_t Size>
void Solve(const std::array<long long, Size>& intCode)
{
    Computer<long long, true> computer(intCode.cbegin(), intCode.cend());
    std::vector<std::vector<char>> cameraOutput;

    std::vector<std::vector<char>>::iterator currentRow =
        cameraOutput.insert(cameraOutput.cend(), std::vector<char>());

    std::optional<long long> output;
    do
    {
        output = computer.Process();
        if (!output.has_value())
        {
            break;
        }

        if (output.value() == 10)
        {
            // End of line, make a new line
            currentRow = cameraOutput.insert(cameraOutput.cend(), std::vector<char>());
        }
        else
        {
            currentRow->push_back(static_cast<char>(output.value()));
        }

    } while (output.has_value());

    // PrintCameraOutput(cameraOutput);

    // Intersections can't occur on the outside edges
    size_t alignmentSum = 0;
    for (size_t y = 1; y < cameraOutput.size() - 1; y++)
    {
        if (cameraOutput[y].size() < 2)
        {
            continue;
        }
        for (size_t x = 1; x < cameraOutput[y].size() - 1; x++)
        {
            if (cameraOutput[y - 1].size() > x&&
                cameraOutput[y + 1].size())
            {
                if (cameraOutput[y][x] != '.' &&
                    cameraOutput[y][x - 1] != '.' &&
                    cameraOutput[y][x + 1] != '.' &&
                    cameraOutput[y - 1][x] != '.' &&
                    cameraOutput[y + 1][x] != '.')
                {
                    alignmentSum += x * y;
                }
            }
        }
    }

    std::wcout << alignmentSum << L'\n';
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
