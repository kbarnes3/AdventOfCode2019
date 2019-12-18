#pragma once
#include <map>
#include <string>
#include <vector>

const std::wstring Ore = L"ORE";

struct ReactionComponent
{
    int Quantity;
    std::wstring Name;
};

struct Reaction
{
    std::vector<ReactionComponent> Inputs;
    ReactionComponent Output;
};

// Transform with:
// '<,'>s/\(.*\) \(\w\+\)$/    { L"\2", { { \1 \2 } },/ | '<,'>s/\(\d\+\) \(\w\+\)/{ \1, L"\2" }/g | '<,'>s/ =>/ },
const std::map<std::wstring, Reaction> test_data_1 = { {
    { L"A", { { { 10, L"ORE" } }, { 10, L"A" } } },
    { L"B", { { { 1, L"ORE" } }, { 1, L"B" } } },
    { L"C", { { { 7, L"A" }, { 1, L"B" } }, { 1, L"C" } } },
    { L"D", { { { 7, L"A" }, { 1, L"C" } }, { 1, L"D" } } },
    { L"E", { { { 7, L"A" }, { 1, L"D" } }, { 1, L"E" } } },
    { L"FUEL", { { { 7, L"A" }, { 1, L"E" } }, { 1, L"FUEL" } } },
} };
