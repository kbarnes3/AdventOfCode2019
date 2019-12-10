// Day7_AmplificationCircuit_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include <algorithm>
#include "Computer.h"
#include <iostream>
#include <limits>
#include <numeric>

template<size_t Size, bool SingleOutput>
bool AllTerminated(const std::vector<Computer<Size, SingleOutput>>& computers)
{
    return std::accumulate(computers.cbegin(), computers.cend(), true, 
        [] (bool a, const Computer<Size, SingleOutput>& b) -> bool
        {
            return a && b.Terminated();
        });
}

template<size_t Size>
int TryPhaseSettings(const std::array<int, Size>& intCode, const std::vector<int>& phaseSettingList)
{
    constexpr size_t numComputers = 5;
    if (phaseSettingList.size() != numComputers)
    {
        FAIL_FAST();
    }

    int lastOutput = 0;
    std::vector<Computer<Size, true>> computers;
    for (size_t i = 0; i < numComputers; i++)
    {
        computers.push_back(Computer<Size, true>(intCode));
        computers[i].AddInput(phaseSettingList[i]);
    }

    computers[0].AddInput(0);

    while (!AllTerminated(computers))
    {
        for (size_t i = 0; i < numComputers; i++)
        {
            size_t nextComputer = i + 1;
            if (nextComputer >= numComputers)
            {
                nextComputer = 0;
            }

            if (computers[i].Terminated())
            {
                continue;
            }

            std::optional<int> output = computers[i].Process();
            if (output.has_value())
            {
                if (i == 4)
                {
                    lastOutput = output.value();
                }

                computers[nextComputer].AddInput(output.value());
            }
        }
    }

    return lastOutput;
}

template<size_t Size>
int PermutePhaseSettings(const std::array<int, Size>& intCode,
    const std::vector<int>& currentPhaseOrder,
    const std::vector<int>& remainingPhases)
{
    if (remainingPhases.empty())
    {
        if (currentPhaseOrder.size() != 5)
        {
            FAIL_FAST();
        }
        return TryPhaseSettings(intCode, currentPhaseOrder);
    }

    int maxThruster = std::numeric_limits<int>::min();
    for (int phase : remainingPhases)
    {
        std::vector<int> proposedPhaseOrder = currentPhaseOrder;
        proposedPhaseOrder.push_back(phase);

        std::vector<int> proposedRemaining = remainingPhases;
        std::vector<int>::iterator toErase = std::remove(proposedRemaining.begin(), proposedRemaining.end(), phase);
        proposedRemaining.erase(toErase, proposedRemaining.end());

        int thruster = PermutePhaseSettings(intCode, proposedPhaseOrder, proposedRemaining);
        maxThruster = std::max(maxThruster, thruster);
    }

    return maxThruster;
}

template<size_t Size>
int MaximizePhaseSettings(const std::array<int, Size>& intCode, const std::vector<int>& phaseSettingList)
{
    std::vector<int> empty;
    int maxThruster = PermutePhaseSettings(intCode, empty, phaseSettingList);

    return maxThruster;
}

template<size_t Size>
void Solve(const std::array<int, Size>& intCode)
{
    std::vector<int> phaseSettingList = { 5, 6, 7, 8, 9 };
    int maxThruster = MaximizePhaseSettings(intCode, phaseSettingList);

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
