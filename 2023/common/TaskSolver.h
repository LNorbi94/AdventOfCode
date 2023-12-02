#pragma once

#include <string>

class TaskSolver
{
public:
    TaskSolver( std::string_view inputFile );

    void solveTask();

protected:
    virtual void parseLine( std::string_view line ) = 0;

    int m_solution = 0;

private:
    std::string m_fileName;
};
