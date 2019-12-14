// Day12_TheNBodyProblem_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Data.h>
#include <iostream>
#include <numeric>

struct Velocity
{
    int x;
    int y;
    int z;
};

struct Moon
{
    Position position;
    Velocity velocity;
};

template<size_t Size>
void ApplyGravity(std::array<Moon, Size>& moons)
{
    typename std::array<Moon, Size>::iterator moon = moons.begin();
    while (moon != moons.end())
    {
        typename std::array<Moon, Size>::const_iterator otherMoon = moons.cbegin();
        while (otherMoon != moons.cend())
        {
            if (moon->position.x < otherMoon->position.x)
            {
                moon->velocity.x++;
            }
            else if (moon->position.x > otherMoon->position.x)
            {
                moon->velocity.x--;
            }

            if (moon->position.y < otherMoon->position.y)
            {
                moon->velocity.y++;
            }

            else if (moon->position.y > otherMoon->position.y)
            {
                moon->velocity.y--;
            }

            if (moon->position.z < otherMoon->position.z)
            {
                moon->velocity.z++;
            }
            else if (moon->position.z > otherMoon->position.z)
            {
                moon->velocity.z--;
            }

            ++otherMoon;
        }

        moon++;
    }
}

template<size_t Size>
void ApplyVelocity(std::array<Moon, Size>& moons)
{
    typename std::array<Moon, Size>::iterator moon = moons.begin();
    while (moon != moons.end())
    {
        moon->position.x += moon->velocity.x;
        moon->position.y += moon->velocity.y;
        moon->position.z += moon->velocity.z;
        ++moon;
    }
}

template<size_t Size>
void PrintMoons(const std::array<Moon, Size>& moons)
{
    for (const Moon& moon : moons)
    {
        std::wcout << L"pos=<x=" << moon.position.x << L", y=" << moon.position.y;
        std::wcout << L", z=" << moon.position.z << L">, vel=<x=" << moon.velocity.x;
        std::wcout << L", y=" << moon.velocity.y << L", z=" << moon.velocity.z;
        std::wcout << L">\n";
    }
}

template<size_t Size>
int ComputeEnergy(const std::array<Moon, Size>& moons)
{
    return std::accumulate(
        moons.cbegin(),
        moons.cend(),
        0,
        [](int a, const Moon& b) -> int
    {
        int value = a;
        int potentialEnergy = abs(b.position.x) +
            abs(b.position.y) +
            abs(b.position.z);
        int kineticEnergy = abs(b.velocity.x) +
            abs(b.velocity.y) +
            abs(b.velocity.z);

        value += potentialEnergy * kineticEnergy;
        return value;
    });
}

template<size_t Size>
void Solve(const std::array<Position, Size>& data, unsigned int timeSteps)
{
    std::array<Moon, Size> moons;

    for (size_t i = 0; i < Size; i++)
    {
        moons[i] = { { data[i].x, data[i].y, data[i].z }, { 0, 0, 0 } };
    }

    for (unsigned int t = 0; t < timeSteps; t++)
    {
        ApplyGravity(moons);
        ApplyVelocity(moons);
    }

    int totalEnergy = ComputeEnergy(moons);
    std::wcout << totalEnergy << L'\n';
}


int main()
{
    Solve(real_data, 1000);
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
