#pragma once
#include <array>

enum class Direction
{
    Up,
    Down,
    Left,
    Right,
};

struct Movement
{
    Direction direction;
    int distance;
};

// Transform with:
// '<,'>s/D/    { Direction::Down, /g | '<,'>s/R/    { Direction::Right, /g | '<,'>s/U/    { Direction::Up, /g | '<,'>s/L/    { Direction::Left, /g | '<,'>s/\(\d\),/\1 },\r/g

// R8,U5,L5,D3
std::array<Movement, 4> test_path_1 = { {
    { Direction::Right, 8 },
    { Direction::Up, 5 },
    { Direction::Left, 5 },
    { Direction::Down, 3 },
} };

// U7,R6,D4,L4
std::array<Movement, 4> test_path_2 = { {
    { Direction::Up, 7 },
    { Direction::Right, 6 },
    { Direction::Down, 4 },
    { Direction::Left, 4 },
} };
