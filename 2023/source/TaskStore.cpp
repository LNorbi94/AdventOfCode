#include "TaskStore.h"

#include <1/FirstTask.h>
#include <2/SecondTask.h>
#include <3/ThirdTask.h>
#include <4/FourthTask.h>
#include <5/FifthTask.h>
#include <6/SixthTask.h>
#include <7/SeventhTask.h>
#include <8/EighthTask.h>
#include <9/NinthTask.h>
#include <10/TenthTask.h>
#include <11/EleventhTask.h>
#include <12/TwelfthTask.h>
#include <13/ThirteenthTask.h>
#include <14/FourteenthTask.h>
#include <15/FifteenthTask.h>
#include <16/SixteenthTask.h>
#include <17/SeventeenthTask.h>
#include <18/EighteenthTask.h>
#include <19/NineteenthTask.h>
#include <20/TwentiethTask.h>
#include <21/TwentyFirstTask.h>
#include <22/TwentySecondTask.h>
#include <23/TwentyThirdTask.h>
#include <24/TwentyFourthTask.h>
#include <25/TwentyFifthTask.h>

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
    RegisterTask("8", std::make_unique<EighthTask>());
    RegisterTask("9", std::make_unique<NinthTask>());
    RegisterTask("10", std::make_unique<TenthTask>());
    RegisterTask("11", std::make_unique<EleventhTask>());
    RegisterTask("12", std::make_unique<TwelfthTask>());
    RegisterTask("13", std::make_unique<ThirteenthTask>());
    RegisterTask("14", std::make_unique<FourteenthTask>());
    RegisterTask("15", std::make_unique<FifteenthTask>());
    RegisterTask("16", std::make_unique<SixteenthTask>());
    RegisterTask("17", std::make_unique<SeventeenthTask>());
    RegisterTask("18", std::make_unique<EighteenthTask>());
    RegisterTask("19", std::make_unique<NineteenthTask>());
    RegisterTask("20", std::make_unique<TwentiethTask>());
    // RegisterTask("21", std::make_unique<TwentyFirstTask>());
    // RegisterTask("22", std::make_unique<TwentySecondTask>());
    // RegisterTask("23", std::make_unique<TwentyThirdTask>());
    // RegisterTask("24", std::make_unique<TwentyFourthTask>());
    // RegisterTask("25", std::make_unique<TwentyFifthTask>());
}

void TaskStore::RegisterTask(const std::string &taskName, std::unique_ptr<ITask> task)
{
    tasks[taskName] = std::move(task);
}
