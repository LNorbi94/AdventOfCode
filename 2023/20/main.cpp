#include "TaskSolver.h"

//#include "source/WorkflowOrganizer.h"

#include <iostream>
#include <fstream>

class FirstTaskSolver
{
public:
    FirstTaskSolver(const std::string_view fileName)
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

class SecondTaskSolver
{
public:
    SecondTaskSolver(const std::string_view fileName)
    {
    }

};

void solveFirstTask(const std::string_view file)
{
    FirstTaskSolver f{ file };
}

void solveSecondTask(const std::string_view file)
{
    SecondTaskSolver f{ file };
}

int main()
{
    solveFirstTask("sample.txt");
    solveFirstTask("complete.txt");
    solveSecondTask("sample.txt");
    solveSecondTask("complete.txt");
}
