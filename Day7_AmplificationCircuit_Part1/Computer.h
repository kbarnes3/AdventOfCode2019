#pragma once
#include <array>
#include <intrin.h>
#include <type_traits>
#include <vector>

__declspec(noreturn)
void FAIL_FAST()
{
    __fastfail(1);
}

template<size_t Size, size_t InputSize, bool SingleOutput>
class Computer
{
public:
    Computer(const std::array<int, Size>& intCode, const std::array<int, InputSize>& input) :
        m_input(input)
    {
        m_memory = intCode;
        m_inputIter = m_input.cbegin();
    }

    template<bool ProcessSingleOutput = SingleOutput>
    typename std::enable_if<ProcessSingleOutput, int>::type
    Process()
    {
        ProcessLoop();

        if (m_output.size() == 0)
        {
            FAIL_FAST();
        }

        return m_output[0];
    }

    template<bool ProcessSingleOutput = SingleOutput>
    typename std::enable_if<!ProcessSingleOutput, std::vector<int>>::type
    Process()
    {
        ProcessLoop();

        return m_output;
    }

private:
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

    int GetOperandValue(typename std::array<int, Size>::iterator instructionIter, unsigned int parameterNumber)
    {
        ParameterMode paramMode = GetModeForParameter(*instructionIter, parameterNumber);
        int operand = *(instructionIter + parameterNumber);
        int operandValue = 0;
        if (paramMode == ParameterMode::Position)
        {
            operandValue = m_memory[operand];
        }
        else
        {
            operandValue = operand;
        }

        return operandValue;
    }

    bool Add(typename std::array<int, Size>::iterator& instructionIter)
    {
        int operand1Value = GetOperandValue(instructionIter, 1);
        int operand2Value = GetOperandValue(instructionIter, 2);
        int resultLoc = *(instructionIter + 3);

        int result = operand1Value + operand2Value;
        m_memory[resultLoc] = result;

        instructionIter += 4;

        return true;
    }

    bool Multiply(typename std::array<int, Size>::iterator& instructionIter)
    {
        int operand1Value = GetOperandValue(instructionIter, 1);
        int operand2Value = GetOperandValue(instructionIter, 2);
        int resultLoc = *(instructionIter + 3);

        int result = operand1Value * operand2Value;
        m_memory[resultLoc] = result;

        instructionIter += 4;

        return true;
    }

    bool ReadInput(typename std::array<int, Size>::iterator& instructionIter)
    {
        int resultLoc = *(instructionIter + 1);

        if (m_inputIter == m_input.cend())
        {
            FAIL_FAST();
        }

        m_memory[resultLoc] = *m_inputIter;
        ++m_inputIter;

        instructionIter += 2;

        return true;
    }

    bool WriteOutput(typename std::array<int, Size>::iterator& instructionIter)
    {
        int value = GetOperandValue(instructionIter, 1);
        m_output.push_back(value);

        instructionIter += 2;

        return !SingleOutput;
    }

    bool JumpIfTrue(typename std::array<int, Size>::iterator& instructionIter)
    {
        int compValue = GetOperandValue(instructionIter, 1);

        if (compValue != 0)
        {
            int jumpValue = GetOperandValue(instructionIter, 2);
            instructionIter = m_memory.begin();
            instructionIter += jumpValue;
        }
        else
        {
            instructionIter += 3;
        }

        return true;
    }

    bool JumpIfFalse(typename std::array<int, Size>::iterator& instructionIter)
    {
        int compValue = GetOperandValue(instructionIter, 1);

        if (compValue == 0)
        {
            int jumpValue = GetOperandValue(instructionIter, 2);
            instructionIter = m_memory.begin();
            instructionIter += jumpValue;
        }
        else
        {
            instructionIter += 3;
        }

        return true;
    }

    bool LessThan(typename std::array<int, Size>::iterator& instructionIter)
    {
        int value1 = GetOperandValue(instructionIter, 1);
        int value2 = GetOperandValue(instructionIter, 2);
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

        m_memory[resultLoc] = result;
        instructionIter += 4;

        return true;
    }

    bool Equals(typename std::array<int, Size>::iterator& instructionIter)
    {
        int value1 = GetOperandValue(instructionIter, 1);
        int value2 = GetOperandValue(instructionIter, 2);
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

        m_memory[resultLoc] = result;
        instructionIter += 4;

        return true;
    }

    bool ProcessOperation(typename std::array<int, Size>::iterator& instructionIter)
    {
        switch (*instructionIter % 100)
        {
        case 1:
            return Add(instructionIter);
        case 2:
            return Multiply(instructionIter);
        case 3:
            return ReadInput(instructionIter);
        case 4:
            return WriteOutput(instructionIter);
        case 5:
            return JumpIfTrue(instructionIter);
        case 6:
            return JumpIfFalse(instructionIter);
        case 7:
            return LessThan(instructionIter);
        case 8:
            return Equals(instructionIter);
        case 99:
            return false;
        default:
            FAIL_FAST();
        }
    }

    void ProcessLoop()
    {
        if (m_processed)
        {
            FAIL_FAST();
        }

        typename std::array<int, Size>::iterator instructionPointer = m_memory.begin();
        bool running = true;
        while (running)
        {
            running = ProcessOperation(instructionPointer);
        }

        m_processed = true;
    }

    std::array<int, Size> m_memory;
    const std::array<int, InputSize> m_input;
    typename std::array<int, InputSize>::const_iterator m_inputIter;
    std::vector<int> m_output;

    bool m_processed = false;
};
