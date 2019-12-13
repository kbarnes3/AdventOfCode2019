// Day02_1202ProgramAlarm_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include <intrin.h>
#include <iostream>

__declspec(noreturn)
void FAIL_FAST()
{
    __fastfail(1);
}

template<size_t Size>
bool ProcessOperation(std::array<size_t, Size>& intCode, typename std::array<size_t, Size>::iterator opcode)
{
    switch (*opcode)
    {
    case 1:
    {
        size_t operand1Loc = *(opcode + 1);
        size_t operand2Loc = *(opcode + 2);
        size_t resultLoc = *(opcode + 3);

        size_t result = intCode[operand1Loc] + intCode[operand2Loc];
        intCode[resultLoc] = result;

        return true;
    }
    case 2:
    {
        size_t operand1Loc = *(opcode + 1);
        size_t operand2Loc = *(opcode + 2);
        size_t resultLoc = *(opcode + 3);

        size_t result = intCode[operand1Loc] * intCode[operand2Loc];
        intCode[resultLoc] = result;

        return true;
    }
    case 99:
        return false;
    default:
        std::wcout << L"Invalid opcode: " << *opcode << L'\n';
        FAIL_FAST();
    }
}

template<size_t Size>
void TrySolve(std::array<size_t, Size>& intCode)
{
    typename std::array<size_t, Size>::iterator opcode = intCode.begin();
    bool running = true;
    while (running)
    {
        running = ProcessOperation(intCode, opcode);
        if (running)
        {
            opcode += 4;
        }
    }
}

template<size_t Size>
void Solve(const std::array<size_t, Size>& startingInstructions, size_t targetOutput)
{
    for (size_t noun = 0; noun < 100; noun++)
    {
        for (size_t verb = 0; verb < 100; verb++)
        {
            typename std::array<size_t, Size> instructions = startingInstructions;
            instructions[1] = noun;
            instructions[2] = verb;
            TrySolve(instructions);

            if (instructions[0] == targetOutput)
            {
                size_t answer = 100 * noun + verb;
                std::wcout << answer << L'\n';
                return;
            }
        }
    }
    std::wcout << L"No answer\n";
    FAIL_FAST();
}

int main()
{
    Solve(real_data, target_output);
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
