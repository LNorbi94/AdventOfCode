#pragma once

#include <TaskSolver.h>

#include <string>
#include <optional>
#include <map>

class SecondTask : public TaskSolver
{
public:
    SecondTask( std::string_view inputFile );

protected:
    void parseLine( std::string_view line ) override;

private:
    std::optional< std::string > getNumberWord( std::string_view line, int i );

    std::map< std::string, char > m_numbers;
};
