// Day7_AmplificationCircuit_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include <algorithm>
#include "Computer.h"
#include <iostream>
#include <limits>

template<size_t Size>
int MaximizePhaseSettings(const std::array<int, Size>& intCode, const std::vector<int>& phaseSettingList, int inputSignal)
{
    if (phaseSettingList.size() == 0)
    {
        return inputSignal;
    }

    int maxThruster = std::numeric_limits<int>::min();

    for (int phaseSetting : phaseSettingList)
    {
        Computer<Size, true> computer(intCode);
        computer.AddInput(phaseSetting);
        computer.AddInput(inputSignal);
        std::optional<int> outputValue = computer.Process();
        if (!outputValue.has_value())
        {
            FAIL_FAST();
        }

        std::vector<int> innerPhaseSettingList = phaseSettingList;
        std::vector<int>::iterator toErase = std::remove(innerPhaseSettingList.begin(), innerPhaseSettingList.end(), phaseSetting);
        innerPhaseSettingList.erase(toErase, innerPhaseSettingList.end());

        int thrusterValue = MaximizePhaseSettings(intCode, innerPhaseSettingList, outputValue.value());
        maxThruster = std::max(maxThruster, thrusterValue);
    }

    return maxThruster;
}

template<size_t Size>
void Solve(const std::array<int, Size>& intCode)
{
    std::vector<int> phaseSettingList = { 0, 1, 2, 3, 4 };
    int maxThruster = MaximizePhaseSettings(intCode, phaseSettingList, 0);
    
    std::wcout << maxThruster << L'\n';
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
