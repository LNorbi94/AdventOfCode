#include "SeventeenthTask.h"

#include "common/TaskSolver.h"
#include "common/StringManipulation.h"
#include "common/Graphs/Id.h"

#include "CityMap.h"

#include <functional>
#include <iostream>
#include <vector>
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "17.txt";
}

class SeventeenthTaskPartOneSolver : public TaskSolver
{
public:
    SeventeenthTaskPartOneSolver(const std::string_view fileName)
        : TaskSolver{fileName}
    {
        ParseFile(std::bind_front(&SeventeenthTaskPartOneSolver::parseLine, this));
    }

    void parseLine(const std::string_view line)
    {
        m_cityMap.addCityBlocks(line);
    }

    void solveMap()
    {
        std::cout << m_cityMap.getMinimalHeatLoss() << "\n";
    }

private:
    CityMap m_cityMap;
};

class SeventeenthTaskPartTwoSolver : public TaskSolver
{
public:
    SeventeenthTaskPartTwoSolver(const std::string_view fileName)
        : TaskSolver{fileName}
    {
        ParseFile(std::bind_front(&SeventeenthTaskPartTwoSolver::parseLine, this));
    }

    void parseLine(std::string_view line)
    {
        m_cityMap.addCityBlocks(line);
    }

    void solveMap()
    {
        std::cout << m_cityMap.getMinimalHeatLossWithUltraCrucible() << "\n";
    }

private:
    CityMap m_cityMap;
};

void SeventeenthTask::SolveFirstPart()
{
    SeventeenthTaskPartOneSolver f{inputFileName.string()};
    f.solveTask();
    f.solveMap();
}

void SeventeenthTask::SolveSecondPart()
{
    SeventeenthTaskPartTwoSolver f{inputFileName.string()};
    f.solveTask();
    f.solveMap();
}
