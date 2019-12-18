// Day02_1202ProgramAlarm_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include <FailFast.h>
#include <iostream>

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
            FAIL_FAST();
    }
}

template<size_t Size>
void Solve(std::array<size_t, Size>& intCode)
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

    std::wcout << intCode[0] << L'\n';
}

int main()
{
    real_data[1] = 12;
    real_data[2] = 2;
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
