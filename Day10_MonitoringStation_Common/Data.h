#pragma once
#include <array>

// Transform with:
// '<,'>s/^/    { / | '<,'>s/\./false, /g | '<,'>s/#/true, /g | '<,'>s/$/},/

const std::array<std::array<bool, 5>, 5> test_data_1 = { {
    { false, true, false, false, true, },
    { false, false, false, false, false, },
    { true, true, true, true, true, },
    { false, false, false, false, true, },
    { false, false, false, true, true, },
} };

const std::array<std::array<bool, 36>, 36> real_data = { {
    { true, false, false, false, false, false, true, false, false, false, true, false, false, false, false, false, false, false, false, false, true, true, true, false, true, false, false, false, false, false, false, false, false, true, false, false, },
    { false, false, false, false, true, false, false, false, false, false, false, true, true, true, false, false, true, false, true, false, true, true, true, false, false, false, false, true, false, false, false, false, false, false, true, true, },
    { false, false, false, false, false, false, true, false, false, true, true, true, false, false, false, false, false, false, false, true, false, true, false, true, false, true, false, false, true, false, false, false, false, false, false, false, },
    { false, false, false, false, false, false, true, false, false, false, false, false, false, true, false, true, false, false, false, false, true, false, true, true, false, false, false, false, true, true, false, true, false, true, false, true, },
    { false, false, false, true, true, true, false, true, false, true, false, false, false, false, false, false, false, true, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, },
    { false, false, false, false, true, true, false, false, false, true, false, false, true, false, false, false, false, true, true, false, false, false, false, true, false, false, false, true, false, true, false, false, false, false, false, false, },
    { false, false, true, true, false, false, false, true, false, true, true, true, false, false, false, false, false, true, true, false, false, false, false, true, false, true, false, false, true, true, false, true, true, false, false, false, },
    { false, false, true, true, false, false, false, false, true, false, true, false, false, false, false, false, false, true, false, true, false, false, false, true, false, true, false, false, false, true, false, true, false, false, false, false, },
    { false, true, false, true, true, false, false, true, true, false, false, false, false, false, false, true, true, false, false, true, false, false, false, true, false, false, false, false, false, true, true, false, false, false, true, true, },
    { false, false, false, false, false, false, false, true, true, false, false, false, false, false, true, false, false, false, false, false, true, true, false, false, true, false, false, true, false, false, true, false, false, false, false, false, },
    { false, false, true, false, false, true, false, false, false, true, false, false, false, false, false, false, true, false, false, true, true, false, false, false, true, false, true, false, false, false, true, false, false, false, true, true, },
    { false, false, false, false, false, false, true, true, false, true, true, false, true, false, true, false, true, true, true, false, false, false, false, true, false, true, false, false, true, false, false, false, false, false, false, true, },
    { true, false, false, true, false, true, false, false, false, true, false, false, false, false, false, true, false, false, false, true, false, false, false, true, true, true, true, false, true, false, false, true, false, false, false, true, },
    { false, false, false, true, true, false, false, false, true, true, false, true, false, false, true, false, false, false, false, false, true, true, true, true, false, true, false, false, false, false, true, true, false, false, false, false, },
    { false, true, false, false, false, false, true, true, true, false, true, false, false, false, true, false, false, false, false, true, false, false, true, false, false, false, false, false, false, true, false, false, false, false, false, false, },
    { false, true, true, false, true, false, true, false, false, false, true, false, false, false, false, true, true, false, false, false, false, false, false, true, false, false, false, false, false, true, true, false, false, false, true, true, },
    { false, false, false, false, false, true, false, false, false, false, true, true, true, false, false, false, true, false, false, false, false, false, true, false, false, false, false, true, false, false, false, false, false, false, false, false, },
    { false, false, false, true, false, false, false, true, false, false, false, false, true, true, false, false, true, false, true, false, false, false, false, false, false, true, false, true, false, true, false, false, false, false, false, false, },
    { false, true, false, false, true, true, true, false, false, false, false, false, false, false, false, false, false, false, false, true, false, true, false, false, true, false, false, false, true, true, true, true, false, true, true, false, },
    { false, true, false, true, true, true, false, false, true, false, false, false, false, false, true, false, false, false, false, false, false, true, false, false, true, true, true, false, false, false, false, true, true, false, false, true, },
    { true, false, false, false, false, false, false, true, false, true, false, true, false, true, false, true, false, true, false, false, false, true, false, true, false, true, false, false, false, false, true, true, false, false, false, false, },
    { false, true, false, false, false, false, false, true, false, false, false, false, false, true, false, false, false, true, true, false, true, false, false, false, false, false, false, true, false, true, false, false, false, true, false, false, },
    { false, false, false, true, true, false, false, true, true, true, false, false, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, },
    { false, false, true, false, true, false, false, true, false, true, false, false, false, true, false, false, false, false, false, true, false, false, false, false, false, true, false, false, false, true, true, true, false, true, false, false, },
    { false, true, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false, true, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, },
    { false, false, false, true, true, false, false, true, false, false, true, false, false, false, true, false, false, true, false, false, false, true, false, false, false, false, false, false, true, true, true, true, false, false, false, false, },
    { false, true, false, false, true, false, false, false, true, true, false, true, true, false, false, true, true, false, false, true, true, true, false, false, false, false, false, false, true, false, false, false, false, false, false, false, },
    { false, true, true, false, false, false, false, false, true, false, false, false, false, false, false, false, true, false, false, true, false, false, false, true, false, false, true, false, false, false, false, false, false, false, true, false, },
    { true, false, true, false, true, false, false, true, false, false, true, true, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, true, true, },
    { false, false, true, false, false, false, false, true, true, false, false, false, false, false, false, true, true, false, false, false, false, false, true, false, false, false, true, false, false, false, true, true, false, false, false, false, },
    { false, true, true, false, false, true, true, false, false, true, false, true, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, true, true, true, },
    { true, true, false, false, false, false, false, false, false, true, false, false, true, false, true, false, false, true, true, false, false, true, false, false, false, true, false, false, false, false, false, false, false, false, false, false, },
    { true, false, false, true, true, false, false, false, true, false, true, true, false, true, false, true, false, false, false, false, false, false, false, false, false, true, false, false, true, false, false, true, false, false, false, false, },
    { false, false, false, false, false, true, false, false, false, true, false, false, false, true, false, true, false, false, false, false, false, false, true, false, false, false, false, true, false, false, false, false, false, false, false, false, },
    { false, false, false, false, true, false, false, false, false, false, false, true, true, true, false, true, false, false, true, false, false, false, false, false, false, true, true, false, false, false, false, false, true, false, false, true, },
    { true, false, false, true, false, false, false, true, true, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, true, true, false, false, false, false, false, true, false, false, false, false, },
} };
