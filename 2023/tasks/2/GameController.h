#pragma once

#include <string>
#include <vector>
#include <optional>
#include <filesystem>

#include "Game.h"

class GameController
{
public:
    enum class CountBy
    {
        Id,
        Power
    };

    void AddGames(const std::filesystem::path &path);

    void AddGames(const std::string &inputString);

    size_t GetSumOfPossibleGames(CountBy countBy) const;

private:
    void ParseGame(const std::string &game);
    int ExtractColor(const std::string &round, const std::string_view color) const;

    std::vector<Game> m_games;
};
