#include "TaskStore.h"

#include <1/FirstTask.h>
#include <2/SecondTask.h>

TaskStore::TaskStore()
{
    RegisterTasks();
}

ITask *TaskStore::GetTask(const std::string &taskName)
{
    return tasks.at(taskName).get();
}

void TaskStore::RegisterTasks()
{
    RegisterTask("1", std::make_unique<FirstTask>());
    RegisterTask("2", std::make_unique<SecondTask>());
}

void TaskStore::RegisterTask(const std::string &taskName, std::unique_ptr<ITask> task)
{
    tasks[taskName] = std::move(task);
}
