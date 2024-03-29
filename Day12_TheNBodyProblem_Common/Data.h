#pragma once
#include <array>

struct Position
{
    int x;
    int y;
    int z;
};

// Transform with:
// '<,'>s/</    { /g | '<,'>s/\w=//g | '<,'>s/>/ },/g
const std::array<Position, 4> test_data = { {
    { -1, 0, 2 },
    { 2, -10, -7 },
    { 4, -8, 8 },
    { 3, 5, -1 },
} };

const std::array<Position, 4> real_data = { {
    { -17, 9, -5 },
    { -1, 7, 13 },
    { -19, 12, 5 },
    { -6, -6, -4 },
} };
