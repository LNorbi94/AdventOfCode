#include "GameController.h"

#include <functional>
#include <regex>
#include <sstream>

#include "common/FileParser.h"
#include "common/StringManipulation.h"

void GameController::AddGames(const std::filesystem::path &path)
{
    FileParser fileParser{path.string()};
    fileParser.ParseFile(std::bind_front(&GameController::ParseGame, this));
}

void GameController::AddGames(const std::string &inputString)
{
    const auto lines = common::splitToMultipleString(inputString, '\n');
    std::ranges::for_each(lines, std::bind_front(&GameController::ParseGame, this));
}

size_t GameController::GetSumOfPossibleGames(const CountBy countBy) const
{
    size_t sumOfPossibleGames = 0;

    for (const auto &game : m_games)
    {
        if (countBy == CountBy::Id && game.IsGamePossible())
        {
            sumOfPossibleGames += game.GetId();
        }
        else if (countBy == CountBy::Power)
        {
            sumOfPossibleGames += game.GetPower();
        }
    }

    return sumOfPossibleGames;
}

void GameController::ParseGame(const std::string &game)
{
    Game g{m_games.size() + 1};

    const auto rounds = common::splitToMultipleString(game, ';');
    for (const auto &round : rounds)
    {
        auto blue = ExtractColor(round, "blue");
        auto red = ExtractColor(round, "red");
        auto green = ExtractColor(round, "green");

        g.AddRound(red, green, blue);
    }

    m_games.push_back(g);
}

int GameController::ExtractColor(const std::string &round, const std::string_view color) const
{
    std::stringstream ss;
    ss << "\\d*\\s" << color;
    std::regex r{ss.str()};

    auto begin = std::sregex_iterator(round.begin(), round.end(), r);
    auto end = std::sregex_iterator();

    if (begin != end)
    {
        auto match = begin->str();
        ss.str("");
        for (const auto &ch : match)
        {
            if (ch != ' ')
            {
                ss << ch;
            }
            else
            {
                break;
            }
        }
        return std::stoi(ss.str());
    }
    return 0;
}
