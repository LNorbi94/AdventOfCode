#include "TaskSolver.h"
#include "StringManipulation.h"

#include "source/Id.h"
#include "source/Trench.h"

#include <iostream>
#include <vector>

class FirstTaskSolver : public TaskSolver
{
public:
    FirstTaskSolver(const std::string_view fileName)
        : TaskSolver{ fileName }
    {
        parseFile();
    }

    void parseLine(const std::string_view line) override
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

class SecondTaskSolver : public TaskSolver
{
public:
    SecondTaskSolver(const std::string_view fileName)
        : TaskSolver{ fileName }
    {
        parseFile();
    }

    void parseLine(std::string_view line) override
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
