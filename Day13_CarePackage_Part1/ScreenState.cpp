#include "ScreenState.h"
#include "FailFast.h"
#include <numeric>

ScreenState::ScreenState()
{
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
        m_state = InputState::ExpectingTile;
        break;
    case InputState::ExpectingTile:
        InputTile(input);
        m_state = InputState::ExpectingX;
        break;
    default:
        FAIL_FAST();
    }
}

size_t ScreenState::CountMatchingTiles(ScreenTile tile)
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

void ScreenState::InputX(long long input)
{
    m_x = input;
}

void ScreenState::InputY(long long input)
{
    m_y = input;
}

void ScreenState::InputTile(long long input)
{
    if (input < static_cast<long long>(ScreenTile::Empty) || input > static_cast<long long>(ScreenTile::Ball))
    {
        FAIL_FAST();
    }

    ScreenTile tile = static_cast<ScreenTile>(input);
    m_screen.insert_or_assign(std::make_pair(m_x, m_y), tile);
}
