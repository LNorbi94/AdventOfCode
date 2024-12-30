#include "TwentiethTask.h"

#include "CommunicationRelay.h"

#include <iostream>
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "20.txt";
}

void TwentiethTask::SolveFirstPart()
{
    CommunicationRelay relay{};
    relay.initRelay(inputFileName);
    std::cout << relay.getPulseCountAfterThousandPush() << "\n";
}

void TwentiethTask::SolveSecondPart()
{
    CommunicationRelay relay{};
    relay.initRelay(inputFileName);
    std::cout << relay.getbuttonPushNeededForMachineToTurnOn() << "\n";
}
