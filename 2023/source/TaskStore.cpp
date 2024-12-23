#include "TaskStore.h"

#include <1/FirstTask.h>
#include <2/SecondTask.h>
#include <3/ThirdTask.h>
#include <4/FourthTask.h>
#include <5/FifthTask.h>
#include <6/SixthTask.h>
#include <7/SeventhTask.h>

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
    RegisterTask("3", std::make_unique<ThirdTask>());
    RegisterTask("4", std::make_unique<FourthTask>());
    RegisterTask("5", std::make_unique<FifthTask>());
    RegisterTask("6", std::make_unique<SixthTask>());
    RegisterTask("7", std::make_unique<SeventhTask>());
}

void TaskStore::RegisterTask(const std::string &taskName, std::unique_ptr<ITask> task)
{
    tasks[taskName] = std::move(task);
}
