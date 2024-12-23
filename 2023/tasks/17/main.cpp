#include "TaskSolver.h"
#include "StringManipulation.h"

#include "source/Id.h"
#include "source/CityMap.h"

#include <iostream>
#include <vector>

class FourthTaskPartOneSolver : public TaskSolver
{
public:
    FourthTaskPartOneSolver(const std::string_view fileName)
        : TaskSolver{fileName}
    {
    }

    void parseLine(const std::string_view line) override
    {
        m_cityMap.addCityBlocks(line);
    }

    void solveMap()
    {
        std::cout << m_cityMap.getMinimalHeatLoss() << "\n";
    }

private:
    CityMap m_cityMap;
};

class FourthTaskPartTwoSolver : public TaskSolver
{
public:
    FourthTaskPartTwoSolver(const std::string_view fileName)
        : TaskSolver{fileName}
    {
    }

    void parseLine(std::string_view line) override
    {
        m_cityMap.addCityBlocks(line);
    }

    void solveMap()
    {
        std::cout << m_cityMap.getMinimalHeatLossWithUltraCrucible() << "\n";
    }

private:
    CityMap m_cityMap;
};

void solveFirstTask(const std::string_view file)
{
    FourthTaskPartOneSolver f{file};
    f.solveTask();
    f.solveMap();
}

void solveSecondTask(const std::string_view file)
{
    FourthTaskPartTwoSolver f{file};
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
