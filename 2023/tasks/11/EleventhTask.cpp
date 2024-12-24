#include "FileParser.h"

#include "Graphs/Id.h"
#include "source/GalaxyMap.h"

#include <iostream>

class FourthTaskPartOneSolver : public FileParser
{
public:
    FourthTaskPartOneSolver(const std::string_view fileName)
        : FileParser{fileName}
    {
        parseFile();
        m_map.correctLengthForExpansion();
    }

    void parseLine(const std::string_view line) override
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

class FourthTaskPartTwoSolver : public FileParser
{
public:
    FourthTaskPartTwoSolver(const std::string_view fileName)
        : FileParser{fileName}
    {
        parseFile();
        m_map.correctLengthForExpansion();
    }

    void parseLine(std::string_view line) override
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

void solveFirstTask(const std::string_view file)
{
    FourthTaskPartOneSolver f{file};
    f.solveMap();
}

void solveSecondTask(const std::string_view file)
{
    FourthTaskPartTwoSolver f{file};
    f.solveMap();
}

int main()
{
    solveFirstTask("sample.txt");
    // solveFirstTask("complete.txt");
    solveSecondTask("sample.txt");
    solveSecondTask("complete.txt");
}
