#include "TaskSolver.h"

#include <fstream>
#include <iostream>

TaskSolver::TaskSolver( const std::string_view inputFile )
    : FileParser{ inputFile }
{}

void TaskSolver::solveTask() const
{
    std::cout << m_solution << "\n";
}
