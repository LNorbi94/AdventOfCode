#include "SixteenthTask.h"

#include "common/TaskSolver.h"
#include "common/StringManipulation.h"

#include "common/Graphs/Id.h"
#include "TileMap.h"

#include <functional>
#include <iostream>
#include <vector>
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "16.txt";
}

class SixteenthTaskPartOneSolver : public TaskSolver
{
public:
    SixteenthTaskPartOneSolver(const std::string_view fileName)
        : TaskSolver{fileName}
    {
        ParseFile(std::bind_front(&SixteenthTaskPartOneSolver::parseLine, this));
    }

    void parseLine(const std::string_view line)
    {
        m_tileMap.addTiles(line);
    }

    void solveMap()
    {
        std::cout << m_tileMap.getNumberOfEnergizedFields({Direction::Right, Id{0, 0}}) << "\n";
    }

private:
    TileMap m_tileMap;
};

class SixteenthTaskPartTwoSolver : public TaskSolver
{
public:
    SixteenthTaskPartTwoSolver(const std::string_view fileName)
        : TaskSolver{fileName}
    {
        ParseFile(std::bind_front(&SixteenthTaskPartTwoSolver::parseLine, this));
    }

    void parseLine(std::string_view line)
    {
        m_tileMap.addTiles(line);
    }

    void solveMap()
    {
        std::cout << m_tileMap.getMaximumNumberOfEnergizedFields() << "\n";
    }

private:
    TileMap m_tileMap;
};

void SixteenthTask::SolveFirstPart()
{
    SixteenthTaskPartOneSolver f{inputFileName.string()};
    f.solveTask();
    f.solveMap();
}

void SixteenthTask::SolveSecondPart()
{
    SixteenthTaskPartTwoSolver f{inputFileName.string()};
    f.solveTask();
    f.solveMap();
}
