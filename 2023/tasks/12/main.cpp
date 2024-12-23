#include "FileParser.h"
#include "StringManipulation.h"

#include "source/SpringInventory.h"

#include <iostream>
#include <sstream>

#include <deque>

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
        const auto input = common::splitString(line, ' ');
        m_springInventories.emplace_back(input[0]);
        const auto damagedSprings = common::splitToMultipleString(input[1], ',');
        std::deque<size_t> springs;
        for (const auto &damagedSpring : damagedSprings)
        {
            springs.emplace_back(std::stoull(damagedSpring));
        }
        m_solution += m_springInventories.back().findAllVariants(input[0], springs);
    }

    void solve()
    {
        std::cout << m_solution << "\n";
    }

private:
    std::vector<SpringInventory> m_springInventories;
    int m_solution = 0;
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
        const auto input = common::splitString(line, ' ');
        std::stringstream ss;
        for (auto i = 0; i < 5; ++i)
        {
            ss << input[0];
            if (i != 4)
            {
                ss << "?";
            }
        }
        m_springInventories.emplace_back(ss.str());
        const auto damagedSprings = common::splitToMultipleString(input[1], ',');
        std::deque<size_t> springs;
        for (auto i = 0; i < 5; ++i)
        {
            for (const auto &damagedSpring : damagedSprings)
            {
                springs.emplace_back(std::stoull(damagedSpring));
            }
        }
        m_solution += m_springInventories.back().findAllVariants(ss.str(), springs);
    }

    void solve()
    {
        std::cout << m_solution << "\n";
    }

private:
    std::vector<SpringInventory> m_springInventories;
    int64_t m_solution = 0;
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
    // solveFirstTask("sample.txt");
    // solveFirstTask("complete.txt");
    solveSecondTask("sample.txt");
    solveSecondTask("complete.txt");
}
