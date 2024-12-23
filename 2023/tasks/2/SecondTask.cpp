#include "SecondTask.h"

#include "GameController.h"

#include <iostream>

namespace
{
    const std::filesystem::path inputFileName = "2.txt";
}

void SecondTask::SolveFirstPart()
{
    GameController gameController;
    gameController.AddGames(inputFileName);
    std::cout << gameController.GetSumOfPossibleGames(GameController::CountBy::Id) << "\n";
}

void SecondTask::SolveSecondPart()
{
    GameController gameController;
    gameController.AddGames(inputFileName);
    std::cout << gameController.GetSumOfPossibleGames(GameController::CountBy::Power) << "\n";
}
