#include "TaskSolver.h"
#include "StringManipulation.h"

#include "source/Hash.h"
#include "source/HashMap.h"

class FirstTaskSolver : public TaskSolver
{
public:
    FirstTaskSolver(const std::string_view fileName)
        : TaskSolver{ fileName }
    {
    }

    void parseLine(std::string_view line) override
    {
        const auto initializationSequence = common::splitToMultipleString(line, ',');
        for (const auto& step : initializationSequence) {
            Hash h{ step };
            m_solution += h.value();
        }
    }
};

class SecondTaskSolver : public TaskSolver
{
public:
    SecondTaskSolver(const std::string_view fileName)
        : TaskSolver{ fileName }
    {
    }

    void parseLine(std::string_view line) override
    {
        const auto initializationSequence = common::splitToMultipleString(line, ',');
        HashMap map;
        for (const auto& step : initializationSequence) {
            bool removeLens = step.contains('-');
            if (removeLens) {
                map.removeValue(common::splitString(step, '-')[0]);
            } else {
                const auto splitStep = common::splitString(step, '=');
                const auto label = splitStep[0];
                const auto focalLength = std::stoll(splitStep[1]);
                map.addValue(label, focalLength);
            }
        }
        m_solution += map.calculateFocusingPower();
    }
};

void solveFirstTask(const std::string_view file)
{
    FirstTaskSolver f{ file };
    f.solveTask();
}

void solveSecondTask(const std::string_view file)
{
    SecondTaskSolver f{ file };
    f.solveTask();
}

int main()
{
    solveFirstTask("sample.txt");
    solveFirstTask("complete.txt");
    solveSecondTask("sample.txt");
    solveSecondTask("complete.txt");
}
