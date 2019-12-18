// Day10_MonitoringStation_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include <cmath>
#include <FailFast.h>
#include <iostream>
#include <map>
#include <numeric>
#include <optional>
#include <utility>

constexpr double pi = 3.1415926535897;

enum class State
{
    Empty,
    Asteroid,
    Occluded
};

template<size_t Width, size_t Height>
void ConvertArray(
    const std::array<std::array<bool, Width>, Height>& source,
    std::array<std::array<State, Width>, Height>& dest
)
{
    for (size_t y = 0; y < Height; y++)
    {
        for (size_t x = 0; x < Width; x++)
        {
            if (source[y][x])
            {
                dest[y][x] = State::Asteroid;
            }
            else
            {
                dest[y][x] = State::Empty;
            }
        }
    }
}

template<size_t Width, size_t Height>
bool IsAsteroidVisible(
    const std::array<std::array<bool, Width>, Height>& data,
    size_t x1,
    size_t y1,
    size_t x2,
    size_t y2)
{
    ptrdiff_t xDiff = x2 - x1;
    ptrdiff_t yDiff = y2 - y1;

    // The two asteroids are visible if nothing is in between them
    ptrdiff_t gcd = std::gcd(xDiff, yDiff);

    ptrdiff_t xStep = xDiff / gcd;
    ptrdiff_t yStep = yDiff / gcd;

    size_t x = x1 + xStep;
    size_t y = y1 + yStep;

    while (x != x2 || y != y2)
    {
        if (data[y][x])
        {
            return false;
        }

        x += xStep;
        y += yStep;
    }

    return true;
}

template<size_t Width, size_t Height>
unsigned int CountVisibleAsteroids(
    const std::array<std::array<bool, Width>, Height>& data,
    size_t targetX,
    size_t targetY)
{
    unsigned int visible = 0;

    for (size_t y = 0; y < Height; y++)
    {
        for (size_t x = 0; x < Width; x++)
        {
            if (data[y][x] &&
                !(x == targetX && y == targetY))
            {
                if (IsAsteroidVisible(data, targetX, targetY, x, y))
                {
                    visible++;
                }
            }
        }
    }

    return visible;
}

template<size_t Width, size_t Height>
std::pair<size_t, size_t> GetStation(const std::array<std::array<bool, Width>, Height>& data)
{
    unsigned int maxVisible = 0;
    size_t stationX = 0;
    size_t stationY = 0;

    for (size_t y = 0; y < Height; y++)
    {
        for (size_t x = 0; x < Width; x++)
        {
            if (data[y][x])
            {
                unsigned int visible = CountVisibleAsteroids(data, x, y);
                if (visible > maxVisible)
                {
                    maxVisible = visible;
                    stationX = x;
                    stationY = y;
                }
            }
        }
    }

    return { stationX, stationY };
}

template<size_t Width, size_t Height>
void BuildAngleMap(
    std::array<std::array<State, Width>, Height>& states,
    std::map<double, std::pair<size_t, size_t>>& angles,
    size_t stationX,
    size_t stationY)
{
    for (size_t y = 0; y < Height; y++)
    {
        for (size_t x = 0; x < Width; x++)
        {
            if (states[y][x] != State::Empty)
            {
                states[y][x] = State::Asteroid;
                ptrdiff_t deltaX = x - stationX;
                ptrdiff_t deltaY = stationY - y; // Swap this because position deltaY should be "up"

                double angle = atan2(deltaX, deltaY);
                if (angle < 0)
                {
                    angle += 2 * pi;
                }
                angles.insert_or_assign(angle, std::make_pair(x, y));
            }
        }
    }
}

bool NextStepInBounds(size_t x, size_t y, ptrdiff_t xStep, ptrdiff_t yStep, size_t width, size_t height)
{
    if (xStep < 0)
    {
        if (static_cast<ptrdiff_t>(x) < abs(xStep))
        {
            return false;
        }
    }
    else if (x + xStep >= width)
    {
        return false;
    }

    if (yStep < 0)
    {
        if (static_cast<ptrdiff_t>(y) < abs(yStep))
        {
            return false;
        }
    }
    else if (y + yStep >= height)
    {
        return false;
    }

    return true;
}

template<size_t Width, size_t Height>
std::optional<std::pair<size_t, size_t>> DestroyAsteroidInLine(
    std::array<std::array<State, Width>, Height>& states,
    size_t stationX,
    size_t stationY,
    size_t lineX,
    size_t lineY
)
{
    ptrdiff_t xDiff = lineX - stationX;
    ptrdiff_t yDiff = lineY - stationY;

    // Destroy the closest asteroid in this line, mark
    // all the others as obscured
    ptrdiff_t gcd = std::gcd(xDiff, yDiff);

    ptrdiff_t xStep = xDiff / gcd;
    ptrdiff_t yStep = yDiff / gcd;

    size_t x = stationX;
    size_t y = stationY;

    std::optional<std::pair<size_t, size_t>> destroyed = {};

    do
    {
        x += xStep;
        y += yStep;

        if (states[y][x] != State::Empty)
        {
            if (!destroyed.has_value() && states[y][x] == State::Occluded)
            {
                // The closest asteroid is occluded
                // This probably means we had two entires in our angle map
                // That were slightly different floats representing the same angle
                // Just return now
                return {};
            }

            if (!destroyed)
            {
                states[y][x] = State::Empty;
                destroyed = std::make_pair(x, y);
            }
            else
            {
                states[y][x] = State::Occluded;
            }
            
        }
    }
    while (NextStepInBounds(x, y, xStep, yStep, Width, Height));

    if (!destroyed.has_value())
    {
        // We shouldn't get here without finding one thing in this line to destroy
        FAIL_FAST();
    }
    return destroyed;
}

template<size_t Width, size_t Height>
std::pair<size_t, size_t> DestroyAsteroids(
    std::array<std::array<State, Width>, Height>& states,
    size_t stationX,
    size_t stationY,
    size_t targetCount)
{
    // Make sure we remove the station from the array of asteroids to destroy
    states[stationY][stationX] = State::Empty;
    size_t destroyedCount = 0;

    while (destroyedCount < targetCount)
    {
        std::map<double, std::pair<size_t, size_t>> angles;
        BuildAngleMap(states, angles, stationX, stationY);

        if (angles.empty())
        {
            return std::make_pair(0, 0);
        }

        for (const std::pair<double, std::pair<size_t, size_t>>& value : angles)
        {
            std::optional<std::pair<size_t, size_t>> destroyed = DestroyAsteroidInLine(
                states,
                stationX, 
                stationY,
                value.second.first,
                value.second.second);
            
            if (destroyed.has_value())
            {
                destroyedCount++;
            }

            if (destroyedCount == targetCount)
            {
                return destroyed.value();
            }
        }
    }

    return std::make_pair(0, 0);
}

template<size_t Width, size_t Height>
void Solve(const std::array<std::array<bool, Width>, Height>& data, size_t targetCount)
{
    std::pair<size_t, size_t> station = GetStation(data);
    std::array<std::array<State, Width>, Height> states;
    ConvertArray(data, states);

    std::pair<size_t, size_t> destroyed = DestroyAsteroids(states, station.first, station.second, targetCount);

    size_t value = 100 * destroyed.first + destroyed.second;
    std::wcout << value << L'\n';
}

int main()
{
    Solve(real_data, 200);
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
