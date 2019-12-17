#include "ScreenState.h"
#include <algorithm>
#include "FailFast.h"
#include <iostream>
#include <numeric>

ScreenState::ScreenState()
{
    m_hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 21 };
    SetConsoleCursorPosition(m_hConsoleOut, coord);
}

void ScreenState::Input(long long input)
{
    switch (m_state)
    {
    case InputState::ExpectingX:
        InputX(input);
        m_state = InputState::ExpectingY;
        break;
    case InputState::ExpectingY:
        InputY(input);
        m_state = InputState::ExpectingTileOrScore;
        break;
    case InputState::ExpectingTileOrScore:
        if (m_x == -1)
        {
            InputScore(input);
        }
        else
        {
            InputTile(input);
        }
        m_state = InputState::ExpectingX;
        break;
    default:
        FAIL_FAST();
    }
}

size_t ScreenState::CountMatchingTiles(ScreenTile tile) const
{
    size_t count = 0;

    count = std::accumulate(m_screen.cbegin(), m_screen.cend(), count,
        [tile](size_t a, const std::pair<std::pair<long long, long long>, ScreenTile>& b) -> size_t
        {
            if (b.second == tile)
            {
                return a + 1;
            }
            else
            {
                return a;
            }
        });

    return count;
}

std::pair<long long, long long> ScreenState::GetFirstTile(ScreenTile tile) const
{
    for (const std::pair<std::pair<long long, long long>, ScreenTile>& entry : m_screen)
    {
        if (entry.second == tile)
        {
            return entry.first;
        }
    }
    return std::make_pair(-1, -1);
}

std::pair<long long, long long> ScreenState::GetConsoleSize() const
{
    long long x = 0;
    long long y = 0;

    for (const std::pair<std::pair<long long, long long>, ScreenTile>& entry : m_screen)
    {
        x = std::max(x, entry.first.first);
        y = std::max(y, entry.first.second);
    }

    return std::make_pair(x, y);
}

void ScreenState::InputX(long long input)
{
    m_x = input;
}

void ScreenState::InputY(long long input)
{
    m_y = input;
}

void ScreenState::InputScore(long long input)
{
    COORD coord = { 0, 20 };
    CONSOLE_SCREEN_BUFFER_INFO currentInfo = {};
    GetConsoleScreenBufferInfo(m_hConsoleOut, &currentInfo);
    SetConsoleCursorPosition(m_hConsoleOut, coord);
    std::wcout << L"                              ";
    SetConsoleCursorPosition(m_hConsoleOut, coord);
    std::wcout << input;
    SetConsoleCursorPosition(m_hConsoleOut, currentInfo.dwCursorPosition);
}

void ScreenState::InputTile(long long input)
{
    if (m_x == -1)
    {
        return;
    }
    if (input < static_cast<long long>(ScreenTile::Empty) || input > static_cast<long long>(ScreenTile::Ball))
    {
        FAIL_FAST();
    }

    ScreenTile tile = static_cast<ScreenTile>(input);
    m_screen.insert_or_assign(std::make_pair(m_x, m_y), tile);

    WriteTileToScreen(tile);
}

void ScreenState::WriteTileToScreen(ScreenTile tile)
{
    wchar_t tileChar = L' ';
    switch (tile)
    {
    case ScreenTile::Empty:
        tileChar = L' ';
        break;
    case ScreenTile::Wall:
        tileChar = L'|';
        break;
    case ScreenTile::Block:
        tileChar = L'X';
        break;
    case ScreenTile::Paddle:
        tileChar = L'-';
        break;
    case ScreenTile::Ball:
        tileChar = L'o';
        break;
    default:
        FAIL_FAST();
    }
    COORD coord = { static_cast<short>(m_x), static_cast<short>(m_y) };
    DWORD charsWritten = 0;
    CONSOLE_SCREEN_BUFFER_INFO currentInfo = {};
    GetConsoleScreenBufferInfo(m_hConsoleOut, &currentInfo);
    SetConsoleCursorPosition(m_hConsoleOut, coord);
    WriteConsoleW(m_hConsoleOut, &tileChar, 1, &charsWritten, nullptr);
    SetConsoleCursorPosition(m_hConsoleOut, currentInfo.dwCursorPosition);
}
