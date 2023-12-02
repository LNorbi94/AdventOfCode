#include "TaskSolver.h"

#include <fstream>
#include <iostream>

TaskSolver::TaskSolver( const std::string_view inputFile )
    : m_fileName{ inputFile }
{}

void TaskSolver::solveTask()
{
    std::ifstream stream{ m_fileName };

    std::string line;
    while ( std::getline( stream, line ) ) {
        parseLine( line );
    }

    std::cout << m_solution << "\n";
}
