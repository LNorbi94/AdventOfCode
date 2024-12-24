#include "ThirteenthTask.h"

#include "common/StringManipulation.h"

#include "Valley.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "13.txt";
}

class ThirteenthTaskPartOneSolver
{
public:
    ThirteenthTaskPartOneSolver(const std::string_view fileName)
    {
        std::ifstream stream{fileName.data()};

        std::vector<Valley> valleys;
        Valley valley;
        std::string line;
        while (std::getline(stream, line))
        {
            if (line.empty())
            {
                valleys.push_back(valley);
                valley = Valley{};
            }
            else
            {
                valley.addRow(line);
            }
        }
        valleys.push_back(valley);

        auto solution = 0;
        for (const auto &valley : valleys)
        {
            solution += valley.mirrorScore();
        }
        std::cout << solution << "\n";
    }
};

class ThirteenthTaskPartTwoSolver
{
public:
    ThirteenthTaskPartTwoSolver(const std::string_view fileName)
    {
        std::ifstream stream{fileName.data()};

        std::vector<Valley> valleys;
        Valley valley;
        std::string line;
        while (std::getline(stream, line))
        {
            if (line.empty())
            {
                valleys.push_back(valley);
                valley = Valley{};
            }
            else
            {
                valley.addRow(line);
            }
        }
        valleys.push_back(valley);

        auto solution = 0;
        for (const auto &valley : valleys)
        {
            solution += valley.mirrorScore(1);
        }
        std::cout << solution << "\n";
    }
};

void ThirteenthTask::SolveFirstPart()
{
    ThirteenthTaskPartOneSolver f{inputFileName.string()};
}

void ThirteenthTask::SolveSecondPart()
{
    ThirteenthTaskPartTwoSolver f{inputFileName.string()};
}
