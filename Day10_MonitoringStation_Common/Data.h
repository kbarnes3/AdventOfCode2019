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

