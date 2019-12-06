#pragma once

#include <string>
#include <vector>

struct OrbitEntry
{
    const std::wstring Orbitee;
    const std::wstring Orbiter;
};

// Transform with
// '<,'>s/\(\w*\))\(\w*\)/    { L"\1", L"\2" },

const std::vector<OrbitEntry> test_data = { {
    { L"COM", L"B" },
    { L"B", L"C" },
    { L"C", L"D" },
    { L"D", L"E" },
    { L"E", L"F" },
    { L"B", L"G" },
    { L"G", L"H" },
    { L"D", L"I" },
    { L"E", L"J" },
    { L"J", L"K" },
    { L"K", L"L" },
} };

