#include "EleventhTask.h"

#include "common/Graphs/Id.h"
#include "common/FileParser.h"
#include "GalaxyMap.h"

#include <functional>
#include <iostream>
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "11.txt";
}

class EleventhTaskPartOneSolver : public FileParser
{
public:
    EleventhTaskPartOneSolver(const std::string_view fileName)
        : FileParser{fileName}
    {
        ParseFile(std::bind_front(&EleventhTaskPartOneSolver::parseLine, this));
        m_map.correctLengthForExpansion();
    }

    void parseLine(const std::string_view line)
    {
        m_map.addData(line);
    }

    void solveMap()
    {
        std::cout << m_map.getSumOfShortestPaths() << "\n";
    }

private:
    GalaxyMap m_map;
};

class EleventhTaskPartTwoSolver : public FileParser
{
public:
    EleventhTaskPartTwoSolver(const std::string_view fileName)
        : FileParser{fileName}
    {
        ParseFile(std::bind_front(&EleventhTaskPartTwoSolver::parseLine, this));
        m_map.correctLengthForExpansion();
    }

    void parseLine(std::string_view line)
    {
        m_map.addData(line);
    }

    void solveMap()
    {
        std::cout << m_map.getSumOfShortestPaths(1000000) << "\n";
    }

private:
    GalaxyMap m_map;
};

void EleventhTask::SolveFirstPart()
{
    EleventhTaskPartOneSolver f{inputFileName.string()};
    f.solveMap();
}

void EleventhTask::SolveSecondPart()
{
    EleventhTaskPartTwoSolver f{inputFileName.string()};
    f.solveMap();
}
