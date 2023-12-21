#include "TaskSolver.h"
#include "StringManipulation.h"

#include "source/Id.h"
#include "source/TileMap.h"

#include <iostream>
#include <vector>

class FirstTaskSolver : public TaskSolver
{
public:
    FirstTaskSolver(const std::string_view fileName, const int numberOfSteps)
        : TaskSolver{ fileName }
        , m_steps{ numberOfSteps }
    {
    }

    void parseLine(const std::string_view line) override
    {
        m_tileMap.addTiles(line);
    }

    void solveMap()
    {
        std::cout << m_tileMap.getNumberOfPlots( m_steps ) << "\n";
    }

private:
    TileMap m_tileMap;
    int m_steps = 0;
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
        //std::cout << m_tileMap.getMaximumNumberOfEnergizedFields() << "\n";
    }

private:
    TileMap m_tileMap;
};

void solveFirstTask(const std::string_view file, const int numberOfSteps)
{
    FirstTaskSolver f{ file, numberOfSteps };
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
    solveFirstTask("sample.txt", 6);
    solveFirstTask("complete.txt", 64);
    //solveSecondTask("sample.txt");
    //solveSecondTask("complete.txt");
}
