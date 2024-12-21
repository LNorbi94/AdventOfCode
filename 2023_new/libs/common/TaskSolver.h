#pragma once

#include "FileParser.h"

#include <string>

class TaskSolver : public FileParser
{
public:
    TaskSolver( std::string_view inputFile );

    void solveTask() const;

protected:
    int m_solution = 0;
};
