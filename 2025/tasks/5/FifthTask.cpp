#include "FifthTask.h"

#include <filesystem>
#include <iostream>

#include "CafeteriaDatabase.h"
#include <common/FileParser.h>
#include <common/StringManipulation.h>

#include <fstream>

namespace
{
    const std::filesystem::path inputFileName = "5.txt";
}

void FifthTask::SolveFirstPart()
{
    CafeteriaDatabase database;
    std::ifstream stream{inputFileName.string()};

    std::string line;
    while (std::getline(stream, line))
    {
        if (line.empty())
        {
            break;
        }

        auto parts = common::splitString(line, "-");
        database.AddFreshFoodRange(std::stoull(parts[0]), std::stoull(parts[1]));
    }

    while (std::getline(stream, line))
    {
        database.InvestigateFood(std::stoull(line));
    }

    std::cout << database.NumberOfFreshFood() << "\n";
}

void FifthTask::SolveSecondPart()
{
    CafeteriaDatabase database;
    std::ifstream stream{ inputFileName.string() };

    std::string line;
    while (std::getline(stream, line))
    {
        if (line.empty())
        {
            break;
        }

        auto parts = common::splitString(line, "-");
        database.AddFreshFoodRange(std::stoull(parts[0]), std::stoull(parts[1]));
    }

    std::cout << database.TotalNumberOfFreshFood() << "\n";
}
