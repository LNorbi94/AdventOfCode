#include "TaskSolver.h"
#include "StringManipulation.h"

#include "Graphs/Id.h"
#include "source/PipeMap.h"

#include <iostream>
#include <vector>

class FourthTaskPartOneSolver : public FileParser
{
public:
    FourthTaskPartOneSolver(const std::string_view fileName)
        : FileParser{fileName}
    {
        parseFile();
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

class FourthTaskPartTwoSolver : public FileParser
{
public:
    FourthTaskPartTwoSolver(const std::string_view fileName)
        : FileParser{fileName}
    {
        parseFile();
    }

    void parseLine(std::string_view line) override
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
    solveFirstTask("complete.txt");
    solveSecondTask("sample.txt");
    solveSecondTask("sample2.txt");
    solveSecondTask("sample3.txt");
    solveSecondTask("sample4.txt");
    solveSecondTask("complete.txt");
}
