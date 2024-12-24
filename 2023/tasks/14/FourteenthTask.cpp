
#include "common/TaskSolver.h"
#include "common/StringManipulation.h"

#include "Platform.h"

#include <functional>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include "FourteenthTask.h"
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "14.txt";
}

class FourteenthTaskPartOneSolver : public FileParser
{
public:
    FourteenthTaskPartOneSolver(const std::string_view fileName)
        : FileParser{fileName}
    {
        ParseFile(std::bind_front(&FourteenthTaskPartOneSolver::parseLine, this));
    }

    void parseLine(const std::string &line)
    {
        p.addRow(line);
    }

    void solve()
    {
        p.MoveRocksTo(Platform::Direction::North);
        std::cerr << p.CalculateMaxLoad() << "\n";
    }

private:
    Platform p;
};

class FourteenthTaskPartTwoSolver : public FileParser
{
public:
    FourteenthTaskPartTwoSolver(const std::string_view fileName)
        : FileParser{fileName}
    {
        ParseFile(std::bind_front(&FourteenthTaskPartTwoSolver::parseLine, this));
    }

    void parseLine(const std::string &line)
    {
        p.addRow(line);
    }

    void solve()
    {
        p.SpinCycle(1000000000);
        std::cerr << p.CalculateMaxLoad() << "\n";
    }

private:
    Platform p;
};

void FourteenthTask::SolveFirstPart()
{
    FourteenthTaskPartOneSolver f{inputFileName.string()};
    f.solve();
}

void FourteenthTask::SolveSecondPart()
{
    FourteenthTaskPartTwoSolver f{inputFileName.string()};
    f.solve();
}
