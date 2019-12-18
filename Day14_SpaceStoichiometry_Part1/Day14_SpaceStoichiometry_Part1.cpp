// Day14_SpaceStoichiometry_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include <FailFast.h>
#include <iostream>

void Solve(const std::map<std::wstring, Reaction>& data)
{
    std::map<std::wstring, int> chemicals = { { { L"FUEL", -1 } } };
    bool done = false;
    do
    {
        done = true;
        for (const std::pair<std::wstring, int>& chemical : chemicals)
        {
            // Skip ore procesing
            if (chemical.first == Ore)
            {
                continue;
            }
            // Don't worry about chemicals where we have all we need currently
            if (chemical.second >= 0)
            {
                continue;
            }

            // We found something we need a reaction to make
            // Consider us not done for this loop
            done = false;
            std::map<std::wstring, Reaction>::const_iterator reactionIter = data.find(chemical.first);
            if (reactionIter == data.cend())
            {
                FAIL_FAST();
            }
            const Reaction& reaction = reactionIter->second;

            if (reaction.Output.Name != chemical.first)
            {
                FAIL_FAST();
            }

            // Add the output to our stockpiles, subtract the inputs from out stockpiles
            chemicals[chemical.first] += reaction.Output.Quantity;
            for (const ReactionComponent& component : reaction.Inputs)
            {
                chemicals[component.Name] -= component.Quantity;
            }
        }
    }
    while (!done);

    int oreNeeded = chemicals[Ore];
    oreNeeded *= -1;

    std::wcout << oreNeeded << L'\n';
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
