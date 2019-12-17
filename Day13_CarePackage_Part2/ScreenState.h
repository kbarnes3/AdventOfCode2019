#pragma once
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
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
    size_t CountMatchingTiles(ScreenTile tile) const;
    std::pair<long long, long long> GetFirstTile(ScreenTile tile) const;
    std::pair<long long, long long> GetConsoleSize() const;

private:
    enum class InputState
    {
        ExpectingX,
        ExpectingY,
        ExpectingTileOrScore
    };

    void InputX(long long input);
    void InputY(long long input);
    void InputScore(long long input);
    void InputTile(long long input);
    void WriteTileToScreen(ScreenTile tile);

    HANDLE m_hConsoleOut = INVALID_HANDLE_VALUE;
    InputState m_state = InputState::ExpectingX;
    long long m_x = 0;
    long long m_y = 0;
    std::map<std::pair<long long, long long>, ScreenTile> m_screen;
};
