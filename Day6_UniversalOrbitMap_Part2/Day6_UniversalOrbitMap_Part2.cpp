// Day6_UniversalOrbitMap_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include <iostream>
#include <map>
#include <intrin.h>

__declspec(noreturn)
void FAIL_FAST()
{
    __fastfail(1);
}

struct OrbitNode
{
    const std::wstring Name;
    const OrbitNode* Parent;
};

std::map<std::wstring, OrbitNode> BuildOrbitMap(const std::vector<OrbitEntry>& entries)
{
    std::map<std::wstring, OrbitNode> orbitMap;
    orbitMap.insert(
        { L"COM",
        { L"COM", nullptr } });

    const OrbitNode unknownNode = { L"Unknown", nullptr };

    for (const OrbitEntry& entry : entries)
    {
        // See if we've already created the node for the orbitee
        std::map<std::wstring, OrbitNode>::iterator orbiteeNode =
            orbitMap.find(entry.Orbitee);
        if (orbiteeNode == orbitMap.end())
        {
            // If not, create a placeholder pointing to the unknownNode
            std::pair<std::map<std::wstring, OrbitNode>::iterator, bool> result = orbitMap.insert(
                { entry.Orbitee,
                { entry.Orbitee, &unknownNode } });
            orbiteeNode = result.first;
        }

        // See if we've already referenced this orbiter before
        std::map<std::wstring, OrbitNode>::iterator orbiterNode =
            orbitMap.find(entry.Orbiter);
        if (orbiterNode != orbitMap.end())
        {
            // If we've already got an entry for this orbiter, it
            // should be a placeholder, meaning its parent node should
            // be the unknownNode
            if (orbiterNode->second.Parent != &unknownNode)
            {
                FAIL_FAST();
            }
            orbiterNode->second.Parent = &(orbiteeNode->second);
        }
        else
        {
            // If we don't have an entry for this orbiter, create one
            orbitMap.insert(
                { entry.Orbiter,
                { entry.Orbiter, &(orbiteeNode->second) } });
        }
    }

    // As a sanity check, make sure we don't have any parents set to unknownNode
    // before returning
    for (const std::pair<std::wstring, OrbitNode>& entry : orbitMap)
    {
        if (entry.second.Parent == &unknownNode)
        {
            FAIL_FAST();
        }
    }

    return orbitMap;
}

unsigned int CountOrbits(const std::map<std::wstring, OrbitNode>& orbitMap)
{
    unsigned int numOrbits = 0;
    for (const std::pair<std::wstring, OrbitNode>& entry : orbitMap)
    {
        const OrbitNode* orbiter = entry.second.Parent;
        while (orbiter != nullptr)
        {
            numOrbits++;
            orbiter = orbiter->Parent;
        }
    }

    return numOrbits;
}

void Solve(const std::vector<OrbitEntry>& entries)
{
    std::map<std::wstring, OrbitNode> orbitMap = BuildOrbitMap(entries);
    unsigned int numOrbits = CountOrbits(orbitMap);

    std::wcout << numOrbits << L'\n';
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
