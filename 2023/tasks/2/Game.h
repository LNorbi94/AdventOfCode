#pragma once

class Game
{
public:
    explicit Game(size_t id);

    void AddRound(int red, int green, int blue);

    bool IsGamePossible() const;

    size_t GetId() const;

    int GetPower() const;

private:
    size_t m_id = 0;

    int m_minimumRedCubes = 0;
    int m_minimumGreenCubes = 0;
    int m_minimumBlueCubes = 0;
};
