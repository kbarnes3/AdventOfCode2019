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

    void Input(int input);

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

    void InputPaintColor(int input);
    void SetPanelColor(PanelColor color);
    void InputDirection(int input);
    void Rotate(int input);
    void Move();

    InputState m_inputState = InputState::WaitingForPaintColor;
    Direction m_direction = Direction::PositiveY;
    int m_x = 0;
    int m_y = 0;
    std::map<std::pair<int, int>, PanelColor> m_paintedPanels;
};
