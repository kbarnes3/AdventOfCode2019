// Day14_SpaceStoichiometry_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <Data.h>
#include <FailFast.h>
#include <iostream>

long long GetOreNeeded(const std::map<std::wstring, Reaction>& reactions, long long fuelToMake)
{
    std::map<std::wstring, long long> chemicals = { { { Fuel, -1 * fuelToMake } } };
    bool done = false;
    do
    {
        done = true;
        for (const std::pair<std::wstring, long long>& chemical : chemicals)
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
            std::map<std::wstring, Reaction>::const_iterator reactionIter = reactions.find(chemical.first);
            if (reactionIter == reactions.cend())
            {
                FAIL_FAST();
            }
            const Reaction& reaction = reactionIter->second;

            if (reaction.Output.Name != chemical.first)
            {
                FAIL_FAST();
            }

            long long reactionsToDo = -1 * chemical.second / reaction.Output.Quantity;
            reactionsToDo = std::max(1ll, reactionsToDo);

            // Add the output to our stockpiles, subtract the inputs from out stockpiles
            chemicals[chemical.first] += reaction.Output.Quantity * reactionsToDo;
            for (const ReactionComponent& component : reaction.Inputs)
            {
                chemicals[component.Name] -= component.Quantity * reactionsToDo;
            }
        }
    } while (!done);

    long long oreNeeded = chemicals[Ore];
    oreNeeded *= -1;

    return oreNeeded;
}

void Solve(const std::map<std::wstring, Reaction>& reactions)
{
    constexpr long long targetOre = 1000000000000;
    long long lowerFuel = 1;
    long long oreNeeded = GetOreNeeded(reactions, lowerFuel);
    if (oreNeeded > targetOre)
    {
        FAIL_FAST();
    }

    // Find an upper bound
    long long upperFuel = 1;
    while (oreNeeded < targetOre)
    {
        upperFuel = upperFuel << 1;
        oreNeeded = GetOreNeeded(reactions, upperFuel);
    }

    // Now binary search until we find the most we can make
    while (upperFuel - lowerFuel > 1)
    {
        long long middle = (upperFuel + lowerFuel) / 2;
        if (middle == upperFuel || middle == lowerFuel)
        {
            FAIL_FAST();
        }

        oreNeeded = GetOreNeeded(reactions, middle);
        if (oreNeeded > targetOre)
        {
            upperFuel = middle;
        }
        else
        {
            lowerFuel = middle;
        }
        

    }

    std::wcout << lowerFuel << L'\n';
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
