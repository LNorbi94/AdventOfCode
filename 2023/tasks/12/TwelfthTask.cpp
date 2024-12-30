#include "common/FileParser.h"
#include "common/StringManipulation.h"

#include "SpringInventory.h"

#include <functional>
#include <iostream>
#include <sstream>

#include <deque>
#include "TwelfthTask.h"
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "12.txt";
}

class TwelfthTaskPartOneSolver : public FileParser
{
public:
    TwelfthTaskPartOneSolver(const std::string_view fileName)
        : FileParser{fileName}
    {
        ParseFile(std::bind_front(&TwelfthTaskPartOneSolver::parseLine, this));
    }

    void parseLine(const std::string_view line)
    {
        const auto input = common::splitString(std::string(line), " ");
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

class TwelfthTaskPartTwoSolver : public FileParser
{
public:
    TwelfthTaskPartTwoSolver(const std::string_view fileName)
        : FileParser{fileName}
    {
        ParseFile(std::bind_front(&TwelfthTaskPartTwoSolver::parseLine, this));
    }

    void parseLine(std::string_view line)
    {
        const auto input = common::splitString(std::string(line), " ");
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

void TwelfthTask::SolveFirstPart()
{
    TwelfthTaskPartOneSolver f{inputFileName.string()};
    f.solve();
}

void TwelfthTask::SolveSecondPart()
{
    TwelfthTaskPartTwoSolver f{inputFileName.string()};
    f.solve();
}
