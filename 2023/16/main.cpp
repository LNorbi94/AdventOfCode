#include "TaskSolver.h"
#include "StringManipulation.h"

#include "source/Id.h"
#include "source/TileMap.h"

#include <iostream>
#include <vector>

class FirstTaskSolver : public TaskSolver
{
public:
    FirstTaskSolver(const std::string_view fileName)
        : TaskSolver{ fileName }
    {
    }

    void parseLine(const std::string_view line) override
    {
        m_tileMap.addTiles(line);
    }

    void solveMap()
    {
        std::cout << m_tileMap.getNumberOfEnergizedFields( { Direction::Right, Id{ 0, 0 } } ) << "\n";
    }

private:
    TileMap m_tileMap;
};

class SecondTaskSolver : public TaskSolver
{
public:
    SecondTaskSolver(const std::string_view fileName)
        : TaskSolver{ fileName }
    {
    }

    void parseLine(std::string_view line) override
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

void solveFirstTask(const std::string_view file)
{
    FirstTaskSolver f{ file };
    f.solveTask();
    f.solveMap();
}

void solveSecondTask(const std::string_view file)
{
    SecondTaskSolver f{ file };
    f.solveTask();
    f.solveMap();
}

int main()
{
    solveFirstTask("sample.txt");
    solveFirstTask("complete.txt");
    solveSecondTask("sample.txt");
    solveSecondTask("complete.txt");
}
