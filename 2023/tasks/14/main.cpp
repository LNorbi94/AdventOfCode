
#include "TaskSolver.h"
#include "StringManipulation.h"

#include "source/Platform.h"

#include <regex>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

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
        p.addRow(std::string(line));
    }

    void solve()
    {
        p.MoveRocksTo(Platform::Direction::North);
        std::cerr << p.CalculateMaxLoad() << "\n";
    }

private:
    Platform p;
};

class FourthTaskPartTwoSolver : public FileParser
{
public:
    FourthTaskPartTwoSolver(const std::string_view fileName)
        : FileParser{fileName}
    {
        parseFile();
    }

    void parseLine(const std::string_view line) override
    {
        p.addRow(std::string(line));
    }

    void solve()
    {
        p.SpinCycle(1000000000);
        std::cerr << p.CalculateMaxLoad() << "\n";
    }

private:
    Platform p;
};

void solveFirstTask(const std::string_view file)
{
    FourthTaskPartOneSolver f{file};
    f.solve();
}

void solveSecondTask(const std::string_view file)
{
    FourthTaskPartTwoSolver f{file};
    f.solve();
}

int main()
{
    solveFirstTask("complete.txt");
    solveSecondTask("complete.txt");
}
