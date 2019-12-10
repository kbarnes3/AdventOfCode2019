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
        m_memory(intCode),
        m_input(input)
    {
        m_instructionPointer = m_memory.begin();
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

    int GetOperandValue(unsigned int parameterNumber)
    {
        ParameterMode paramMode = GetModeForParameter(*m_instructionPointer, parameterNumber);
        int operand = *(m_instructionPointer + parameterNumber);
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

    bool Add()
    {
        int operand1Value = GetOperandValue(1);
        int operand2Value = GetOperandValue(2);
        int resultLoc = *(m_instructionPointer + 3);

        int result = operand1Value + operand2Value;
        m_memory[resultLoc] = result;

        m_instructionPointer += 4;

        return true;
    }

    bool Multiply()
    {
        int operand1Value = GetOperandValue(1);
        int operand2Value = GetOperandValue(2);
        int resultLoc = *(m_instructionPointer + 3);

        int result = operand1Value * operand2Value;
        m_memory[resultLoc] = result;

        m_instructionPointer += 4;

        return true;
    }

    bool ReadInput()
    {
        int resultLoc = *(m_instructionPointer + 1);

        if (m_inputIter == m_input.cend())
        {
            FAIL_FAST();
        }

        m_memory[resultLoc] = *m_inputIter;
        ++m_inputIter;

        m_instructionPointer += 2;

        return true;
    }

    bool WriteOutput()
    {
        int value = GetOperandValue(1);
        m_output.push_back(value);

        m_instructionPointer += 2;

        return !SingleOutput;
    }

    bool JumpIfTrue()
    {
        int compValue = GetOperandValue(1);

        if (compValue != 0)
        {
            int jumpValue = GetOperandValue(2);
            m_instructionPointer = m_memory.begin();
            m_instructionPointer += jumpValue;
        }
        else
        {
            m_instructionPointer += 3;
        }

        return true;
    }

    bool JumpIfFalse()
    {
        int compValue = GetOperandValue(1);

        if (compValue == 0)
        {
            int jumpValue = GetOperandValue(2);
            m_instructionPointer = m_memory.begin();
            m_instructionPointer += jumpValue;
        }
        else
        {
            m_instructionPointer += 3;
        }

        return true;
    }

    bool LessThan()
    {
        int value1 = GetOperandValue(1);
        int value2 = GetOperandValue(2);
        int resultLoc = *(m_instructionPointer + 3);
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
        m_instructionPointer += 4;

        return true;
    }

    bool Equals()
    {
        int value1 = GetOperandValue(1);
        int value2 = GetOperandValue(2);
        int resultLoc = *(m_instructionPointer + 3);
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
        m_instructionPointer += 4;

        return true;
    }

    bool ProcessOperation()
    {
        switch (*m_instructionPointer % 100)
        {
        case 1:
            return Add();
        case 2:
            return Multiply();
        case 3:
            return ReadInput();
        case 4:
            return WriteOutput();
        case 5:
            return JumpIfTrue();
        case 6:
            return JumpIfFalse();
        case 7:
            return LessThan();
        case 8:
            return Equals();
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

        bool running = true;
        while (running)
        {
            running = ProcessOperation();
        }

        m_processed = true;
    }

    std::array<int, Size> m_memory;
    typename std::array<int,Size>::iterator m_instructionPointer;
    const std::array<int, InputSize> m_input;
    typename std::array<int, InputSize>::const_iterator m_inputIter;
    std::vector<int> m_output;

    bool m_processed = false;
};
