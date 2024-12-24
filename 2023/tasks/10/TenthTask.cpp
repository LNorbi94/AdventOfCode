#include "common/TaskSolver.h"
#include "common/StringManipulation.h"

#include "common/Graphs/Id.h"
#include "PipeMap.h"
#include <functional>
#include <iostream>
#include <vector>
#include "TenthTask.h"
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "10.txt";
}

class TenthTaskPartOneSolver : public FileParser
{
public:
    TenthTaskPartOneSolver(const std::string_view fileName)
        : FileParser{fileName}
    {
        ParseFile(std::bind_front(&TenthTaskPartOneSolver::parseLine, this));
    }

    void parseLine(const std::string_view line)
    {
        m_pipeMap.addPipes(line);
    }

    void solveMap()
    {
        m_pipeMap.findLoop();
        std::cout << m_pipeMap.getLongestDistance() << "\n";
    }

private:
    PipeMap m_pipeMap;
};

class TenthTaskPartTwoSolver : public FileParser
{
public:
    TenthTaskPartTwoSolver(const std::string_view fileName)
        : FileParser{fileName}
    {
        ParseFile(std::bind_front(&TenthTaskPartTwoSolver::parseLine, this));
    }

    void parseLine(std::string_view line)
    {
        m_pipeMap.addPipes(line);
    }

    void solveMap()
    {
        m_pipeMap.findLoop();
        std::cout << m_pipeMap.getEnclosedArea() << "\n";
    }

private:
    PipeMap m_pipeMap;
};

void TenthTask::SolveFirstPart()
{
    TenthTaskPartOneSolver f{inputFileName.string()};
    f.solveMap();
}

void TenthTask::SolveSecondPart()
{
    TenthTaskPartTwoSolver f{inputFileName.string()};
    f.solveMap();
}
