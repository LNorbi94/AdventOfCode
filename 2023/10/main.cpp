#include "TaskSolver.h"
#include "StringManipulation.h"

#include "source/Id.h"
#include "source/PipeMap.h"

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

class SecondTaskSolver : public TaskSolver
{
public:
    SecondTaskSolver(const std::string_view fileName)
        : TaskSolver{ fileName }
    {
    }

    void parseLine(std::string_view line) override
    {
        m_pipeMap.addPipes(line);
    }

    void solveMap()
    {
        m_pipeMap.findLoop();
        std::cout << m_pipeMap.getLargestEnclosedArea() << "\n";
    }

private:
    PipeMap m_pipeMap;
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
