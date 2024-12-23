#include <gtest/gtest.h>

#include "2/GameController.h"

namespace
{
    const std::string sampleInput = R"(Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green)";
}

class GameControllerTests : public testing::Test
{
};

TEST_F(GameControllerTests, SampleTestPartOne)
{
    GameController controller;
    controller.AddGames(sampleInput);

    EXPECT_EQ(controller.GetSumOfPossibleGames(GameController::CountBy::Id), 8);
}

TEST_F(GameControllerTests, SampleTestPartTwo)
{
    GameController controller;
    controller.AddGames(sampleInput);

    EXPECT_EQ(controller.GetSumOfPossibleGames(GameController::CountBy::Power), 2286);
}
