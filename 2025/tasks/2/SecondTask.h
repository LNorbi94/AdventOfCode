#pragma once

#include "common/ITask.h"

class SecondTask : public ITask
{
public:
    void SolveFirstPart() override;
    void SolveSecondPart() override;
};
