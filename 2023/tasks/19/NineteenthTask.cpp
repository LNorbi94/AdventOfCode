#include "NineteenthTask.h"

#include "common/TaskSolver.h"

#include "PartOne/WorkflowOrganizer.h"
#include "PartTwo/GenericWorkflowOrganizer.h"

#include <iostream>
#include <fstream>
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "19.txt";
}

class NineteenthTaskPartOneSolver
{
public:
    NineteenthTaskPartOneSolver(const std::string_view fileName)
    {
        std::ifstream stream{fileName.data()};

        std::string line;
        while (std::getline(stream, line))
        {
            if (line.empty())
            {
                break;
            }
            m_workflowOrganizer.addWorkflow(line);
        }
        while (std::getline(stream, line))
        {
            m_workflowOrganizer.addPart(line);
        }

        std::cout << m_workflowOrganizer.getTotalPartsRanking() << "\n";
    }

private:
    WorkflowOrganizer m_workflowOrganizer;
};

class NineteenthTaskPartTwoSolver
{
public:
    NineteenthTaskPartTwoSolver(const std::string_view fileName)
    {
        std::ifstream stream{fileName.data()};

        std::string line;
        while (std::getline(stream, line))
        {
            if (line.empty())
            {
                break;
            }
            m_workflowOrganizer.addWorkflow(line);
        }

        m_workflowOrganizer.determineAcceptedPartRatings();
        std::cout << m_workflowOrganizer.getNumberOfCombinations() << "\n";
    }

private:
    GenericWorkflowOrganizer m_workflowOrganizer;
};

void NineteenthTask::SolveFirstPart()
{
    NineteenthTaskPartOneSolver f{inputFileName.string()};
}

void NineteenthTask::SolveSecondPart()
{
    NineteenthTaskPartTwoSolver f{inputFileName.string()};
}
