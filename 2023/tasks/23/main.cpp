#include "FileParser.h"
#include "StringManipulation.h"

#include "source/Id.h"
#include "source/RoutePlanner.h"

#include <iostream>
#include <vector>

class FirstTaskSolver : public FileParser
{
public:
    FirstTaskSolver(const std::string_view fileName)
        : FileParser{ fileName }
    {
        parseFile();
    }

    void parseLine(const std::string_view line) override
    {
        m_planner.addPaths(line);
    }

    void solveMap()
    {
        std::cout << m_planner.getLongestRoute() << "\n";
    }

private:
    RoutePlanner m_planner;
};

class SecondTaskSolver : public FileParser
{
public:
    SecondTaskSolver(const std::string_view fileName)
        : FileParser{ fileName }
    {
        parseFile();
    }

    void parseLine(const std::string_view line) override
    {
        m_planner.addPaths(line);
    }

    void solveMap()
    {
        std::cout << m_planner.getLongestDifficultRoute() << "\n";
    }

private:
    RoutePlanner m_planner;
};

void solveFirstTask(const std::string_view file)
{
    FirstTaskSolver f{ file };
    f.solveMap();
}

void solveSecondTask(const std::string_view file)
{
    SecondTaskSolver f{ file };
    f.solveMap();
}

int main()
{
    solveFirstTask("sample.txt");
    solveFirstTask("complete.txt");
    solveSecondTask("sample.txt");
    solveSecondTask("complete.txt");
}
