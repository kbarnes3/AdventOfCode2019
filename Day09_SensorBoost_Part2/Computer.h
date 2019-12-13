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

template<typename T, bool SingleOutput>
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

    void AddInput(T value)
    {
        if (m_state == ProcessState::Running)
        {
            FAIL_FAST();
        }
        m_input.push(value);
    }

    template<bool ProcessSingleOutput = SingleOutput>
    typename std::enable_if<ProcessSingleOutput, std::optional<T>>::type
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
    typename std::enable_if<!ProcessSingleOutput, std::vector<T>>::type
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

    void EnsureMemory(T address)
    {
        if (address >= static_cast<T>(m_memory.size()))
        {
            m_memory.resize(address + 1, 0);
        }
    }

    T ReadMemory(size_t address)
    {
        EnsureMemory(address);
        return m_memory[address];
    }

    void WriteMemory(size_t address, T value)
    {
        EnsureMemory(address);
        m_memory[address] = value;
    }

    ParameterMode GetModeForParameter(T opCode, unsigned int parameterNumber)
    {
        T divisor = 1;
        switch (parameterNumber)
        {
        case 1:
            divisor = 100;
            break;
        case 2:
            divisor = 1000;
            break;
        case 3:
            divisor = 10000;
            break;
        default:
            FAIL_FAST();
        }

        T parameterMode = opCode / divisor;
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

    T GetOperandValue(unsigned int parameterNumber)
    {
        ParameterMode paramMode = GetModeForParameter(ReadMemory(m_instructionPointer), parameterNumber);
        T operand = ReadMemory(m_instructionPointer + parameterNumber);
        T operandValue = 0;

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

    size_t GetOperandAddress(unsigned int parameterNumber)
    {
        ParameterMode paramMode = GetModeForParameter(ReadMemory(m_instructionPointer), parameterNumber);
        T operand = ReadMemory(m_instructionPointer + parameterNumber);

        switch (paramMode)
        {
        case ParameterMode::Position:
            return operand;
        case ParameterMode::Relative:
            return m_relativeBase + operand;
        default:
            FAIL_FAST();
        }
    }

    ProcessState Add()
    {
        T operand1Value = GetOperandValue(1);
        T operand2Value = GetOperandValue(2);
        T resultLoc = GetOperandAddress(3);

        T result = operand1Value + operand2Value;
        WriteMemory(resultLoc, result);

        m_instructionPointer += 4;

        return ProcessState::Running;
    }

    ProcessState Multiply()
    {
        T operand1Value = GetOperandValue(1);
        T operand2Value = GetOperandValue(2);
        T resultLoc = GetOperandAddress(3);

        T result = operand1Value * operand2Value;
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

        T resultLoc = GetOperandAddress(1);

        WriteMemory(resultLoc, m_input.front());
        m_input.pop();

        m_instructionPointer += 2;

        return ProcessState::Running;
    }

    ProcessState WriteOutput()
    {
        T value = GetOperandValue(1);
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
        T compValue = GetOperandValue(1);

        if (compValue != 0)
        {
            T jumpValue = GetOperandValue(2);
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
        T compValue = GetOperandValue(1);

        if (compValue == 0)
        {
            T jumpValue = GetOperandValue(2);
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
        T value1 = GetOperandValue(1);
        T value2 = GetOperandValue(2);
        T resultLoc = GetOperandAddress(3);
        T result = 0;

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
        T value1 = GetOperandValue(1);
        T value2 = GetOperandValue(2);
        T resultLoc = GetOperandAddress(3);
        T result = 0;

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
        T value = GetOperandValue(1);

        m_relativeBase += value;
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

    std::vector<T> m_memory;
    T m_instructionPointer = 0;
    size_t m_relativeBase = 0;
    std::queue<T> m_input;
    std::vector<T> m_output;

    ProcessState m_state = ProcessState::Initialized;
};
