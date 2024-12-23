#include "common/TaskSolver.h"
#include "common/StringManipulation.h"

#include <functional>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include "NinthTask.h"
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "9.txt";
}

class OasisHistory
{
public:
    OasisHistory(std::vector<int64_t> history)
    {
        m_history.push_back(history);

        bool sequenceReachedZero = false;
        auto i = 0;
        while (!sequenceReachedZero)
        {
            std::vector<int64_t> nextSequence;
            for (auto j = 0; j < m_history[i].size() - 1; ++j)
            {
                auto difference = m_history[i][j + 1] - m_history[i][j];
                nextSequence.emplace_back(difference);
            }
            sequenceReachedZero = std::all_of(nextSequence.cbegin(), nextSequence.cend(), [](const int64_t val)
                                              { return val == 0; });
            m_history.push_back(nextSequence);
            ++i;
        }
    }

    int64_t predictNextValue() const
    {
        int64_t nextPrediction = 0;
        for (int j = m_history.size() - 2; j >= 0; --j)
        {
            const auto currentLine = m_history[j];
            const auto lastValue = currentLine[currentLine.size() - 1];
            nextPrediction = lastValue + nextPrediction;
        }
        return nextPrediction;
    }

    int64_t predictPreviousValue() const
    {
        int64_t prediction = 0;
        for (int j = m_history.size() - 2; j >= 0; --j)
        {
            const auto currentLine = m_history[j];
            const auto lastValue = currentLine[0];
            prediction = lastValue - prediction;
        }
        return prediction;
    }

private:
    std::vector<std::vector<int64_t>> m_history;
};

class NinthTaskPartOneSolver : public TaskSolver
{
public:
    NinthTaskPartOneSolver(const std::string_view fileName)
        : TaskSolver{fileName}
    {
        ParseFile(std::bind_front(&NinthTaskPartOneSolver::parseLine, this));
    }

    void parseLine(std::string_view line)
    {
        auto numbers = common::extractNumbers<int64_t>(line.data());
        auto history = OasisHistory{numbers};
        m_solution += history.predictNextValue();
    }
};

class NinthTaskPartTwoSolver : public TaskSolver
{
public:
    NinthTaskPartTwoSolver(const std::string_view fileName)
        : TaskSolver{fileName}
    {
        ParseFile(std::bind_front(&NinthTaskPartTwoSolver::parseLine, this));
    }

    void parseLine(std::string_view line)
    {
        auto numbers = common::extractNumbers<int64_t>(line.data());
        auto history = OasisHistory{numbers};
        m_solution += history.predictPreviousValue();
    }
};

void NinthTask::SolveFirstPart()
{
    NinthTaskPartOneSolver f{inputFileName.string()};
    f.solveTask();
}

void NinthTask::SolveSecondPart()
{
    NinthTaskPartTwoSolver f{inputFileName.string()};
    f.solveTask();
}
