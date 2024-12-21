#pragma once

#include "common/ITask.h"

class FirstTask : public ITask
{
public:
    void SolveFirstTask(const std::string &inputFileName) override;
    void SolveSecondTask(const std::string &inputFileName) override;
};
