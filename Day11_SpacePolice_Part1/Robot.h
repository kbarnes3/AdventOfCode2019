#pragma once
#include <map>
#include <utility>

enum class PanelColor
{
    Black = 0,
    White = 1,
};

class Robot
{
public:
    Robot();
    Robot(const Robot&) = delete;
    Robot& operator=(const Robot&) = delete;

    void Input(long long input);

    PanelColor GetPanelColor();

    size_t PaintedPanelsCount();

private:
    enum class InputState
    {
        WaitingForPaintColor,
        WaitingForDirection
    };

    enum class Direction
    {
        PositiveY,
        PositiveX,
        NegativeY,
        NegativeX
    };

    void InputPaintColor(long long input);
    void SetPanelColor(PanelColor color);
    void InputDirection(long long input);
    void Rotate(long long input);
    void Move();

    InputState m_inputState = InputState::WaitingForPaintColor;
    Direction m_direction = Direction::PositiveY;
    long long m_x = 0;
    long long m_y = 0;
    std::map<std::pair<long long, long long>, PanelColor> m_paintedPanels;
};
