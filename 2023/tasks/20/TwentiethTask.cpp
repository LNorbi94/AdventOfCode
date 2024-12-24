#include "common/TaskSolver.h"

// #include "source/WorkflowOrganizer.h"

#include <iostream>
#include <fstream>
#include "TwentiethTask.h"
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "20.txt";
}

class TwentiethTaskPartOneSolver
{
public:
    TwentiethTaskPartOneSolver(const std::string_view fileName)
    {
        /*std::ifstream stream{ fileName.data() };

        std::string line;
        while (std::getline(stream, line)) {
            if (line.empty()) {
                break;
            }
            m_workflowOrganizer.addWorkflow(line);
        }
        while (std::getline(stream, line)) {
            m_workflowOrganizer.addPart(line);
        }

        std::cout << m_workflowOrganizer.getTotalPartsRanking() << "\n";*/
    }

private:
};

class TwentiethTaskPartTwoSolver
{
public:
    TwentiethTaskPartTwoSolver(const std::string_view fileName)
    {
    }
};

void TwentiethTask::SolveFirstPart()
{
    TwentiethTaskPartOneSolver f{inputFileName.string()};
}

void TwentiethTask::SolveSecondPart()
{
    TwentiethTaskPartTwoSolver f{inputFileName.string()};
}
