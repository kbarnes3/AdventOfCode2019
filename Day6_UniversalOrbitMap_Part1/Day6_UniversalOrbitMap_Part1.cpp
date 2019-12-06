// Day6_UniversalOrbitMap_Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
    std::wstring Name;
    OrbitNode* Parent;
};

std::map<std::wstring, OrbitNode> BuildOrbitMap(std::vector<OrbitEntry>& entries)
{
    std::map<std::wstring, OrbitNode> orbitMap;
    orbitMap.insert(
        { L"COM", 
        { L"COM", nullptr } });

    while (!entries.empty())
    {
        std::vector<OrbitEntry>::iterator iter = entries.begin();
        while (iter != entries.end())
        {
            std::map<std::wstring, OrbitNode>::iterator orbiteeNode =
                orbitMap.find(iter->Orbitee);
            if (orbiteeNode != orbitMap.end())
            {
                // We found the parent node in the map, add an entry pointing to it
                std::pair<std::map<std::wstring, OrbitNode>::iterator, bool> result = orbitMap.insert(
                    { iter->Orbiter,
                    { iter->Orbiter, &(orbiteeNode->second) } });
                if (!result.second)
                {
                    FAIL_FAST();
                }
                
                // Now remove the current entry from the list we need to process still
                iter = entries.erase(iter);
            }
            else
            {
                // The orbitee node hasn't been mapped yet. Just move on and we'll deal
                // with this in another pass.
                ++iter;
            }
        }
    }

    return orbitMap;
}

void Solve(std::vector<OrbitEntry>& entries)
{
    std::map<std::wstring, OrbitNode> orbitMap = BuildOrbitMap(entries);
}

int main()
{
    Solve(test_data);
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
