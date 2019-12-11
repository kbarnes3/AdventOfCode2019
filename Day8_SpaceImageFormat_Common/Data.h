#pragma once
#include <array>

// Transform the input with the following regex
// '<,'>s/\(\d\)/    \1,\r/g
const std::array<int, 12> test_data = {
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    0,
    1,
    2,
};

const unsigned int test_data_width = 3;
const unsigned int test_data_height = 2;
