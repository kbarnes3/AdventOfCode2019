// Day15_OxygenSystem_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Computer.h>
#include <Data.h>
#include <deque>
#include <iostream>

enum class Direction : int
{
    None = 0,
    North = 1,
    South = 2,
    West = 3,
    East = 4
};

Direction GetOppositeDirection(Direction direction)
{
    switch (direction)
    {
    case Direction::North:
        return Direction::South;
    case Direction::South:
        return Direction::North;
    case Direction::West:
        return Direction::East;
    case Direction::East:
        return Direction::West;
    default:
        FAIL_FAST();
    }
}

bool AreOppositeDirections(Direction a, Direction b)
{
    Direction oppositeA = GetOppositeDirection(a);
    return oppositeA == b;
}

Direction GetDirectionToAttempt(Direction lastAttemptedInSpace, Direction lastSuccessfulStep)
{
    // We've tried every new direction, just go back
    if (lastAttemptedInSpace == Direction::East)
    {
        return GetOppositeDirection(lastSuccessfulStep);
    }
    else
    {
        Direction newDirection = static_cast<Direction>(static_cast<int>(lastAttemptedInSpace) + 1);
        if (AreOppositeDirections(newDirection, lastSuccessfulStep))
        {
            return GetDirectionToAttempt(newDirection, lastSuccessfulStep);
        }
        else
        {
            return newDirection;
        }
    }
}

template<size_t Size>
void Solve(const std::array<long long, Size>& intCode)
{
    Computer<long long, true> computer(intCode.cbegin(), intCode.cend());
    bool systemFound = false;
    std::deque<Direction> steps;
    Direction lastDirectionAttempted = Direction::None;

    while (!systemFound)
    {
        Direction lastSuccessfulStep = Direction::None;
        if (!steps.empty())
        {
            lastSuccessfulStep = steps.front();
        }
        Direction directionToAttempt = GetDirectionToAttempt(lastDirectionAttempted, lastSuccessfulStep);

        computer.AddInput(static_cast<int>(directionToAttempt));
        std::optional<long long> robotAction = computer.Process();
        if (!robotAction.has_value())
        {
            FAIL_FAST();
        }

        switch (robotAction.value())
        {
        case 0:
            // The robot hit a wall. Its position has not changed.
            lastDirectionAttempted = directionToAttempt;
            break;
        case 2:
            // The robot moved one step and found the system
            systemFound = true;
            [[fallthrough]];
        case 1:
            // The robot moved one step
            if (AreOppositeDirections(directionToAttempt, lastSuccessfulStep))
            {
                steps.pop_front();
                lastDirectionAttempted = lastSuccessfulStep;
            }
            else
            {
                steps.push_front(directionToAttempt);
                lastDirectionAttempted = Direction::None;
            }
            break;
        default:
            FAIL_FAST();
        }
    }

    std::wcout << steps.size() << L'\n';
}

int main()
{
    Solve(real_data);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
