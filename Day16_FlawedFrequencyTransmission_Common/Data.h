#pragma once
#include <array>

const std::array<int, 4> base_pattern = { 0, 1, 0, -1 };

// Transform with:
// '<,'>s/\(\d\)/    \1,\r/g
const std::array<int, 8> test_data = {
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
};
