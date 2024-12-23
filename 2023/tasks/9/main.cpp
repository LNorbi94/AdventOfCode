#include "TaskSolver.h"
#include "StringManipulation.h"

#include <regex>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

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

class FourthTaskPartOneSolver : public TaskSolver
{
public:
    FourthTaskPartOneSolver(const std::string_view fileName)
        : TaskSolver{fileName}
    {
    }

    void parseLine(std::string_view line) override
    {
        auto numbers = common::extractNumbers<int64_t>(line.data());
        auto history = OasisHistory{numbers};
        m_solution += history.predictNextValue();
    }
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
        auto numbers = common::extractNumbers<int64_t>(line.data());
        auto history = OasisHistory{numbers};
        m_solution += history.predictPreviousValue();
    }
};

void solveFirstTask(const std::string_view file)
{
    FourthTaskPartOneSolver f{file};
    f.solveTask();
}

void solveSecondTask(const std::string_view file)
{
    FourthTaskPartTwoSolver f{file};
    f.solveTask();
}

int main()
{
    solveFirstTask("sample.txt");
    solveFirstTask("complete.txt");
    solveSecondTask("sample.txt");
    solveSecondTask("complete.txt");
}
