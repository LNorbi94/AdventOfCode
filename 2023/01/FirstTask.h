#pragma once

#include <TaskSolver.h>

#include <string>

class FirstTask : public TaskSolver
{
public:
    FirstTask( std::string_view inputFile );

protected:
    void parseLine( std::string_view line ) override;
};
