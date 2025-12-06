#pragma once

#include <map>
#include <memory>
#include <string>

#include "common/ITask.h"

class TaskStore
{
public:
    TaskStore();

    ITask *GetTask(const std::string &taskName);

private:
    void RegisterTasks();
    void RegisterTask(const std::string &taskName, std::unique_ptr<ITask> task);

    std::map<std::string, std::unique_ptr<ITask>> tasks;
};
