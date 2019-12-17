#pragma once
#include <map>
#include <utility>

enum class ScreenTile : long long
{
    Empty = 0,
    Wall = 1,
    Block = 2,
    Paddle = 3,
    Ball = 4
};

class ScreenState
{
public:
    ScreenState();

    ScreenState(const ScreenState&) = delete;
    ScreenState& operator=(const ScreenState&) = delete;

    void Input(long long input);
    size_t CountMatchingTiles(ScreenTile tile);

private:
    enum class InputState
    {
        ExpectingX,
        ExpectingY,
        ExpectingTile
    };

    void InputX(long long input);
    void InputY(long long input);
    void InputTile(long long input);

    InputState m_state = InputState::ExpectingX;
    long long m_x = 0;
    long long m_y = 0;
    std::map<std::pair<long long, long long>, ScreenTile> m_screen;
};
