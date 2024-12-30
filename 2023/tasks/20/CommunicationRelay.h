#pragma once

#include "IModule.h"
#include "ModuleType.h"

#include <deque>
#include <filesystem>
#include <map>
#include <vector>
#include <string>
#include <memory>

class CommunicationRelay
{
public:
    void initRelay(const std::filesystem::path &fileName);

    void pressButton();

    void processQueue();

    int64_t getPulseCountAfterThousandPush();

    int64_t getbuttonPushNeededForMachineToTurnOn();

private:
    void addModule(const std::string &line);

    void addModuleDestinations(const std::string &line);

    ModuleType getModuleType(const std::string &line);

    std::string getModuleName(const std::string &line);

    std::vector<std::string> getModuleDestinations(const std::string &line);

    void queueSignals(std::vector<Signal> &&signals);

    std::map<std::string, std::unique_ptr<IModule>> modules;
    std::map<Pulse, int> pulseCount;
    std::deque<Signal> queue;

    std::string rxSender;
    std::map<std::string, int64_t> lastHighPulseModules;
    int64_t buttonPressed = 0;
};
