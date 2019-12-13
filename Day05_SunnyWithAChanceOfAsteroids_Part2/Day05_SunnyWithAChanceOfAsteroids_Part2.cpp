// Day05_SunnyWithAChanceOfAsteroids_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include <intrin.h>
#include <iostream>

__declspec(noreturn)
void FAIL_FAST()
{
    __fastfail(1);
}

enum class ParameterMode
{
    Position = 0,
    Immediate = 1
};

ParameterMode GetModeForParameter(int opCode, unsigned int parameterNumber)
{
    int divisor = 1;
    switch (parameterNumber)
    {
    case 1:
        divisor = 100;
        break;
    case 2:
        divisor = 1000;
        break;
    default:
        FAIL_FAST();
    }

    int parameterMode = opCode / divisor;
    parameterMode = parameterMode % 10;

    switch (parameterMode)
    {
    case 0:
        return ParameterMode::Position;
    case 1:
        return ParameterMode::Immediate;
    default:
        FAIL_FAST();
    }
}

template<size_t Size>
int GetOperandValue(std::array<int, Size>& intCode, typename std::array<int, Size>::iterator instructionIter, unsigned int parameterNumber)
{
    ParameterMode paramMode = GetModeForParameter(*instructionIter, parameterNumber);
    int operand = *(instructionIter + parameterNumber);
    int operandValue = 0;
    if (paramMode == ParameterMode::Position)
    {
        operandValue = intCode[operand];
    }
    else
    {
        operandValue = operand;
    }

    return operandValue;
}

template<size_t Size>
bool Add(std::array<int, Size>& intCode, typename std::array<int, Size>::iterator& instructionIter)
{
    int operand1Value = GetOperandValue(intCode, instructionIter, 1);
    int operand2Value = GetOperandValue(intCode, instructionIter, 2);
    int resultLoc = *(instructionIter + 3);

    int result = operand1Value + operand2Value;
    intCode[resultLoc] = result;

    instructionIter += 4;

    return true;
}

template<size_t Size>
bool Multiply(std::array<int, Size>& intCode, typename std::array<int, Size>::iterator& instructionIter)
{
    int operand1Value = GetOperandValue(intCode, instructionIter, 1);
    int operand2Value = GetOperandValue(intCode, instructionIter, 2);
    int resultLoc = *(instructionIter + 3);

    int result = operand1Value * operand2Value;
    intCode[resultLoc] = result;

    instructionIter += 4;

    return true;
}

template<size_t Size>
bool ReadInput(std::array<int, Size>& intCode, typename std::array<int, Size>::iterator& instructionIter)
{
    int resultLoc = *(instructionIter + 1);
    intCode[resultLoc] = 5;

    instructionIter += 2;

    return true;
}

template<size_t Size>
bool WriteOutput(std::array<int, Size>& intCode, typename std::array<int, Size>::iterator& instructionIter)
{
    int value = GetOperandValue(intCode, instructionIter, 1);
    std::wcout << value << L'\n';

    instructionIter += 2;

    return true;
}

template<size_t Size>
bool JumpIfTrue(std::array<int, Size>& intCode, typename std::array<int, Size>::iterator& instructionIter)
{
    int compValue = GetOperandValue(intCode, instructionIter, 1);

    if (compValue != 0)
    {
        int jumpValue = GetOperandValue(intCode, instructionIter, 2);
        instructionIter = intCode.begin();
        instructionIter += jumpValue;
    }
    else
    {
        instructionIter += 3;
    }

    return true;
}

template<size_t Size>
bool JumpIfFalse(std::array<int, Size>& intCode, typename std::array<int, Size>::iterator& instructionIter)
{
    int compValue = GetOperandValue(intCode, instructionIter, 1);

    if (compValue == 0)
    {
        int jumpValue = GetOperandValue(intCode, instructionIter, 2);
        instructionIter = intCode.begin();
        instructionIter += jumpValue;
    }
    else
    {
        instructionIter += 3;
    }

    return true;
}

template<size_t Size>
bool LessThan(std::array<int, Size>& intCode, typename std::array<int, Size>::iterator& instructionIter)
{
    int value1 = GetOperandValue(intCode, instructionIter, 1);
    int value2 = GetOperandValue(intCode, instructionIter, 2);
    int resultLoc = *(instructionIter + 3);
    int result = 0;

    if (value1 < value2)
    {
        result = 1;
    }
    else
    {
        result = 0;
    }

    intCode[resultLoc] = result;
    instructionIter += 4;

    return true;
}

template<size_t Size>
bool Equals(std::array<int, Size>& intCode, typename std::array<int, Size>::iterator& instructionIter)
{
    int value1 = GetOperandValue(intCode, instructionIter, 1);
    int value2 = GetOperandValue(intCode, instructionIter, 2);
    int resultLoc = *(instructionIter + 3);
    int result = 0;

    if (value1 == value2)
    {
        result = 1;
    }
    else
    {
        result = 0;
    }

    intCode[resultLoc] = result;
    instructionIter += 4;

    return true;
}

template<size_t Size>
bool ProcessOperation(std::array<int, Size>& intCode, typename std::array<int, Size>::iterator& instructionIter)
{
    switch (*instructionIter % 100)
    {
    case 1:
        return Add(intCode, instructionIter);
    case 2:
        return Multiply(intCode, instructionIter);
    case 3:
        return ReadInput(intCode, instructionIter);
    case 4:
        return WriteOutput(intCode, instructionIter);
    case 5:
        return JumpIfTrue(intCode, instructionIter);
    case 6:
        return JumpIfFalse(intCode, instructionIter);
    case 7:
        return LessThan(intCode, instructionIter);
    case 8:
        return Equals(intCode, instructionIter);
    case 99:
        return false;
    default:
        FAIL_FAST();
    }
}

template<size_t Size>
void Solve(std::array<int, Size>& intCode)
{
    typename std::array<int, Size>::iterator opcode = intCode.begin();
    bool running = true;
    while (running)
    {
        running = ProcessOperation(intCode, opcode);
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
