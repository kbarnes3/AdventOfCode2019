#include "Robot.h"
#include "FailFast.h"

Robot::Robot()
{
}

void Robot::Input(long long input)
{
    switch (m_inputState)
    {
    case InputState::WaitingForPaintColor:
        InputPaintColor(input);
        m_inputState = InputState::WaitingForDirection;
        break;
    case InputState::WaitingForDirection:
        InputDirection(input);
        m_inputState = InputState::WaitingForPaintColor;
        break;
    default:
        FAIL_FAST();
    }
}

PanelColor Robot::GetPanelColor()
{
    std::map<std::pair<long long, long long>, PanelColor>::const_iterator iter =
        m_paintedPanels.find(std::make_pair(m_x, m_y));

    if (iter != m_paintedPanels.cend())
    {
        return iter->second;
    }
    else
    {
        return PanelColor::Black;
    }
}

size_t Robot::PaintedPanelsCount()
{
    return m_paintedPanels.size();
}

void Robot::InputPaintColor(long long input)
{
    switch (input)
    {
    case 0:
        SetPanelColor(PanelColor::Black);
        break;
    case 1:
        SetPanelColor(PanelColor::White);
        break;
    default:
        FAIL_FAST();
    }
}

void Robot::SetPanelColor(PanelColor color)
{
    m_paintedPanels.insert_or_assign(std::make_pair(m_x, m_y), color);
}

void Robot::InputDirection(long long input)
{
    Rotate(input);
    Move();
}

void Robot::Rotate(long long input)
{
    switch (input)
    {
    case 0:
        switch (m_direction)
        {
        case Direction::PositiveY:
            m_direction = Direction::PositiveX;
            break;
        case Direction::PositiveX:
            m_direction = Direction::NegativeY;
            break;
        case Direction::NegativeY:
            m_direction = Direction::NegativeX;
            break;
        case Direction::NegativeX:
            m_direction = Direction::PositiveY;
            break;
        }
        break;
    case 1:
        switch (m_direction)
        {
        case Direction::PositiveY:
            m_direction = Direction::NegativeX;
            break;
        case Direction::PositiveX:
            m_direction = Direction::PositiveY;
            break;
        case Direction::NegativeY:
            m_direction = Direction::PositiveX;
            break;
        case Direction::NegativeX:
            m_direction = Direction::NegativeY;
            break;
        }
        break;
    default:
        FAIL_FAST();
    }
}

void Robot::Move()
{
    switch (m_direction)
    {
        case Direction::PositiveY:
            m_y++;
            break;
        case Direction::PositiveX:
            m_x++;
            break;
        case Direction::NegativeY:
            m_y--;
            break;
        case Direction::NegativeX:
            m_x--;
            break;
    }
}
