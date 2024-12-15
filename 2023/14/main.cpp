
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

class FirstTaskSolver : public FileParser
{
public:
    FirstTaskSolver(const std::string_view fileName)
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
    FirstTaskSolver f{file};
    f.solve();
}

void solveSecondTask(const std::string_view file)
{
    SecondTaskSolver f{file};
    f.solve();
}

int main()
{
    solveFirstTask("complete.txt");
    solveSecondTask("complete.txt");
}
