#include "EighteenthTask.h"

#include "common/TaskSolver.h"
#include "common/StringManipulation.h"
#include "common/Graphs/Id.h"

#include "Trench.h"

#include <functional>
#include <iostream>
#include <vector>
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "18.txt";
}

class EighteenthTaskPartOneSolver : public TaskSolver
{
public:
    EighteenthTaskPartOneSolver(const std::string_view fileName)
        : TaskSolver{fileName}
    {
        ParseFile(std::bind_front(&EighteenthTaskPartOneSolver::parseLine, this));
    }

    void parseLine(const std::string_view line)
    {
        m_trench.dig(line);
    }

    void solveMap()
    {
        std::cout << m_trench.getPossibleLavaVolume() << "\n";
    }

private:
    Trench m_trench;
};

class EighteenthTaskPartTwoSolver : public TaskSolver
{
public:
    EighteenthTaskPartTwoSolver(const std::string_view fileName)
        : TaskSolver{fileName}
    {
        ParseFile(std::bind_front(&EighteenthTaskPartTwoSolver::parseLine, this));
    }

    void parseLine(std::string_view line)
    {
        m_trench.alternativeDig(line);
    }

    void solveMap()
    {
        std::cout << m_trench.getPossibleLavaVolume() << "\n";
    }

private:
    Trench m_trench;
};

void EighteenthTask::SolveFirstPart()
{
    EighteenthTaskPartOneSolver f{inputFileName.string()};
    f.solveMap();
}

void EighteenthTask::SolveSecondPart()
{
    EighteenthTaskPartTwoSolver f{inputFileName.string()};
    f.solveMap();
}
