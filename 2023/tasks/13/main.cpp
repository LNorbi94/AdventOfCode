
#include "TaskSolver.h"
#include "StringManipulation.h"

#include "source/Valley.h"

#include <regex>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

class FourthTaskPartOneSolver
{
public:
    FourthTaskPartOneSolver(const std::string_view fileName)
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

class FourthTaskPartTwoSolver
{
public:
    FourthTaskPartTwoSolver(const std::string_view fileName)
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

void solveFirstTask(const std::string_view file)
{
    FourthTaskPartOneSolver f{file};
}

void solveSecondTask(const std::string_view file)
{
    FourthTaskPartTwoSolver f{file};
}

int main()
{
    solveFirstTask("sample.txt");
    solveFirstTask("complete.txt");
    solveSecondTask("sample.txt");
    solveSecondTask("complete.txt");
}
