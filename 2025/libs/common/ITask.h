#pragma once

#include <string>

class ITask
{
public:
    virtual ~ITask() = default;

    virtual void SolveFirstPart() = 0;
    virtual void SolveSecondPart() = 0;
};
