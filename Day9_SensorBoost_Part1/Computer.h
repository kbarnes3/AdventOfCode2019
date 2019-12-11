#pragma once
#include <array>
#include <intrin.h>
#include <optional>
#include <queue>
#include <type_traits>
#include <vector>


__declspec(noreturn)
void FAIL_FAST()
{
    __fastfail(1);
}

template<bool SingleOutput>
class Computer
{
public:
    template<class InputIt>
    Computer(InputIt first, InputIt last) :
        m_memory(first, last)
    {
    }

    Computer(const Computer&) = delete;
    Computer& operator=(const Computer&) = delete;

    bool Terminated() const
    {
        return m_state == ProcessState::Terminated;
    }

    void AddInput(int value)
    {
        if (m_state == ProcessState::Running)
        {
            FAIL_FAST();
        }
        m_input.push(value);
    }

    template<bool ProcessSingleOutput = SingleOutput>
    typename std::enable_if<ProcessSingleOutput, std::optional<int>>::type
        Process()
    {
        m_output.clear();
        ProcessLoop();

        if (m_output.size() == 0)
        {
            return {};
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
        Immediate = 1,
        Relative = 2
    };

    enum class ProcessState
    {
        Initialized,
        Running,
        WaitingForInput,
        YieldingOutput,
        Terminated
    };

    void EnsureMemory(int address)
    {
        if (address >= m_memory.size())
        {
            m_memory.resize(address + 1, 0);
        }
    }

    int ReadMemory(int address)
    {
        EnsureMemory(address);
        return m_memory[address];
    }

    void WriteMemory(int address, int value)
    {
        EnsureMemory(address);
        m_memory[address] = value;
    }

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
            case 2:
                return ParameterMode::Relative;
            default:
                FAIL_FAST();
        }
    }

    int GetOperandValue(unsigned int parameterNumber)
    {
        ParameterMode paramMode = GetModeForParameter(ReadMemory(m_instructionPointer), parameterNumber);
        int operand = ReadMemory(m_instructionPointer + parameterNumber);
        int operandValue = 0;

        switch (paramMode)
        {
            case ParameterMode::Position:
                operandValue = ReadMemory(operand);
                break;
            case ParameterMode::Immediate:
                operandValue = operand;
                break;
            case ParameterMode::Relative:
                operandValue = ReadMemory(m_relativeBase + operand);
                break;
            default:
                FAIL_FAST();
        }

        return operandValue;
    }

    ProcessState Add()
    {
        int operand1Value = GetOperandValue(1);
        int operand2Value = GetOperandValue(2);
        int resultLoc = ReadMemory(m_instructionPointer + 3);

        int result = operand1Value + operand2Value;
        WriteMemory(resultLoc, result);

        m_instructionPointer += 4;

        return ProcessState::Running;
    }

    ProcessState Multiply()
    {
        int operand1Value = GetOperandValue(1);
        int operand2Value = GetOperandValue(2);
        int resultLoc = ReadMemory(m_instructionPointer + 3);

        int result = operand1Value * operand2Value;
        WriteMemory(resultLoc, result);

        m_instructionPointer += 4;

        return ProcessState::Running;
    }

    ProcessState ReadInput()
    {
        if (m_input.empty())
        {
            return ProcessState::WaitingForInput;
        }

        int resultLoc = ReadMemory(m_instructionPointer + 1);

        WriteMemory(resultLoc, m_input.front());
        m_input.pop();

        m_instructionPointer += 2;

        return ProcessState::Running;
    }

    ProcessState WriteOutput()
    {
        int value = GetOperandValue(1);
        m_output.push_back(value);

        m_instructionPointer += 2;

        if (SingleOutput)
        {
            return ProcessState::YieldingOutput;
        }
        else
        {
            return ProcessState::Running;
        }
    }

    ProcessState JumpIfTrue()
    {
        int compValue = GetOperandValue(1);

        if (compValue != 0)
        {
            int jumpValue = GetOperandValue(2);
            m_instructionPointer = jumpValue;
        }
        else
        {
            m_instructionPointer += 3;
        }

        return ProcessState::Running;
    }

    ProcessState JumpIfFalse()
    {
        int compValue = GetOperandValue(1);

        if (compValue == 0)
        {
            int jumpValue = GetOperandValue(2);
            m_instructionPointer = jumpValue;
        }
        else
        {
            m_instructionPointer += 3;
        }

        return ProcessState::Running;
    }

    ProcessState LessThan()
    {
        int value1 = GetOperandValue(1);
        int value2 = GetOperandValue(2);
        int resultLoc = ReadMemory(m_instructionPointer + 3);
        int result = 0;

        if (value1 < value2)
        {
            result = 1;
        }
        else
        {
            result = 0;
        }

        WriteMemory(resultLoc, result);
        m_instructionPointer += 4;

        return ProcessState::Running;
    }

    ProcessState Equals()
    {
        int value1 = GetOperandValue(1);
        int value2 = GetOperandValue(2);
        int resultLoc = ReadMemory(m_instructionPointer + 3);
        int result = 0;

        if (value1 == value2)
        {
            result = 1;
        }
        else
        {
            result = 0;
        }

        WriteMemory(resultLoc, result);
        m_instructionPointer += 4;

        return ProcessState::Running;
    }

    ProcessState AdjustRelativeBase()
    {
        int value1 = GetOperandValue(1);

        m_relativeBase += value1;
        m_instructionPointer += 2;

        return ProcessState::Running;
    }

    ProcessState ProcessOperation()
    {
        switch (ReadMemory(m_instructionPointer) % 100)
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
            case 9:
                return AdjustRelativeBase();
            case 99:
                return ProcessState::Terminated;
            default:
                FAIL_FAST();
        }
    }

    void ProcessLoop()
    {
        if (m_state == ProcessState::Running ||
            m_state == ProcessState::Terminated)
        {
            FAIL_FAST();
        }

        m_state = ProcessState::Running;
        while (m_state == ProcessState::Running)
        {
            m_state = ProcessOperation();
        }
    }

    std::vector<int> m_memory;
    int m_instructionPointer = 0;
    int m_relativeBase = 0;
    std::queue<int> m_input;
    std::vector<int> m_output;

    ProcessState m_state = ProcessState::Initialized;
};
