#include "common/TaskSolver.h"
#include "common/StringManipulation.h"

#include <functional>
#include "Hash.h"
#include "HashMap.h"
#include "FifteenthTask.h"
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "15.txt";
}

class FifteenthTaskPartOneSolver : public TaskSolver
{
public:
    FifteenthTaskPartOneSolver(const std::string_view fileName)
        : TaskSolver{fileName}
    {
        ParseFile(std::bind_front(&FifteenthTaskPartOneSolver::parseLine, this));
    }

    void parseLine(std::string_view line)
    {
        const auto initializationSequence = common::splitToMultipleString(line, ',');
        for (const auto &step : initializationSequence)
        {
            Hash h{step};
            m_solution += h.value();
        }
    }
};

class FifteenthTaskPartTwoSolver : public TaskSolver
{
public:
    FifteenthTaskPartTwoSolver(const std::string_view fileName)
        : TaskSolver{fileName}
    {
        ParseFile(std::bind_front(&FifteenthTaskPartTwoSolver::parseLine, this));
    }

    void parseLine(std::string_view line)
    {
        const auto initializationSequence = common::splitToMultipleString(line, ',');
        HashMap map;
        for (const auto &step : initializationSequence)
        {
            bool removeLens = step.contains('-');
            if (removeLens)
            {
                map.removeValue(common::splitString(step, "-")[0]);
            }
            else
            {
                const auto splitStep = common::splitString(step, "=");
                const auto label = splitStep[0];
                const auto focalLength = std::stoll(splitStep[1]);
                map.addValue(label, focalLength);
            }
        }
        m_solution += map.calculateFocusingPower();
    }
};

void FifteenthTask::SolveFirstPart()
{
    FifteenthTaskPartOneSolver f{inputFileName.string()};
    f.solveTask();
}

void FifteenthTask::SolveSecondPart()
{
    FifteenthTaskPartTwoSolver f{inputFileName.string()};
    f.solveTask();
}
