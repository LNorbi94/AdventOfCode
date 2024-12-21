#pragma once

#include <string>

class ITask
{
public:
    virtual ~ITask() = default;

    virtual void SolveFirstTask(const std::string &inputFileName) = 0;
    virtual void SolveSecondTask(const std::string &inputFileName) = 0;
};
