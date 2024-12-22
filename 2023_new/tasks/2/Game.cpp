#include "Game.h"

namespace
{
    constexpr auto MaxRedCubes = 12;
    constexpr auto MaxGreenCubes = 13;
    constexpr auto MaxBlueCubes = 14;
}

Game::Game(const size_t id) : m_id{id}
{
}

void Game::AddRound(const int red, const int green, const int blue)
{
    if (red > m_minimumRedCubes)
    {
        m_minimumRedCubes = red;
    }

    if (green > m_minimumGreenCubes)
    {
        m_minimumGreenCubes = green;
    }

    if (blue > m_minimumBlueCubes)
    {
        m_minimumBlueCubes = blue;
    }
}

bool Game::IsGamePossible() const
{
    return m_minimumRedCubes <= MaxRedCubes && m_minimumGreenCubes <= MaxGreenCubes && m_minimumBlueCubes <= MaxBlueCubes;
}

size_t Game::GetId() const
{
    return m_id;
}

int Game::GetPower() const
{
    return m_minimumRedCubes * m_minimumBlueCubes * m_minimumGreenCubes;
}
