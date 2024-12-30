#include "CommunicationRelay.h"

#include <common/FileParser.h>
#include <common/StringManipulation.h>

#include "BroadcastModule.h"
#include "ConjunctionModule.h"
#include "FlipFlopModule.h"
#include "ModuleType.h"

#include <algorithm>
#include <iterator>
#include <ranges>
#include <iostream>
#include <numeric>

void CommunicationRelay::initRelay(const std::filesystem::path &fileName)
{
    {
        FileParser fileParser{fileName.string()};
        fileParser.ParseFile(std::bind_front(&CommunicationRelay::addModule, this));
    }
    {
        FileParser fileParser{fileName.string()};
        fileParser.ParseFile(std::bind_front(&CommunicationRelay::addModuleDestinations, this));
        for (const auto &input : modules.at(rxSender)->getInputs())
        {
            lastHighPulseModules[input] = 0;
        }
    }
}

void CommunicationRelay::pressButton()
{
    buttonPressed++;
    pulseCount[Pulse::LowPulse]++;
    queueSignals(modules.at("broadcaster")->receivePulse("button", Pulse::LowPulse));
    processQueue();
}

void CommunicationRelay::processQueue()
{
    while (!queue.empty())
    {
        auto signal = queue.front();
        queue.pop_front();
        if (modules.contains(signal.destination))
        {
            queueSignals(modules.at(signal.destination)->receivePulse(signal.sender, signal.pulse));
        }
        else
        {

            // std::cout << "Firing signal: " << signal.sender << " -> " << signal.destination << " " << (signal.pulse == Pulse::HighPulse ? "high" : "low") << '\n';
        }

        if (lastHighPulseModules.contains(signal.sender) && signal.destination == rxSender && signal.pulse == Pulse::HighPulse)
        {
            lastHighPulseModules[signal.sender] = buttonPressed;
            // std::cout << signal.sender << " sent high pulse, after " << buttonPressed << " presses.\n";
        }
        pulseCount[signal.pulse]++;
    }
}

int64_t CommunicationRelay::getPulseCountAfterThousandPush()
{
    for (int i = 0; i < 1000; ++i)
    {
        pressButton();
    }

    return pulseCount[Pulse::HighPulse] * pulseCount[Pulse::LowPulse];
}

int64_t CommunicationRelay::getbuttonPushNeededForMachineToTurnOn()
{
    while (std::ranges::any_of(lastHighPulseModules | std::ranges::views::values, [](int64_t lastButtonPress)
                               { return lastButtonPress == 0; }))
    {
        pressButton();
    }

    int64_t requiredButtonPresses = 1;
    for (const auto &lastButtonPress : lastHighPulseModules | std::ranges::views::values)
    {
        requiredButtonPresses = std::lcm(requiredButtonPresses, lastButtonPress);
    }

    return requiredButtonPresses;
}

void CommunicationRelay::addModule(const std::string &line)
{
    const auto moduleType = getModuleType(line);
    const auto [name, outputs] = common::splitString(line, " -> ");
    const auto moduleName = getModuleName(name);
    switch (moduleType)
    {
    case ModuleType::FlipFlop:
        modules[moduleName] = std::make_unique<FlipFlopModule>();
        break;
    case ModuleType::Conjunction:
        modules[moduleName] = std::make_unique<ConjunctionModule>();
        break;
    case ModuleType::Broadcast:
        modules[moduleName] = std::make_unique<BroadcastModule>();
        break;
    }
    modules[moduleName]->setModuleName(moduleName);
}

void CommunicationRelay::addModuleDestinations(const std::string &line)
{
    const auto moduleType = getModuleType(line);
    const auto [name, outputs] = common::splitString(line, " -> ");
    const auto moduleName = getModuleName(name);
    const auto moduleDestinations = getModuleDestinations(outputs);
    modules.at(moduleName)->addDestinations(moduleDestinations);
    for (const auto &destination : moduleDestinations)
    {
        if (modules.contains(destination))
        {
            modules.at(destination)->addInput(moduleName);
        }
        if (destination == "rx")
        {
            rxSender = moduleName;
        }
    }
}

ModuleType CommunicationRelay::getModuleType(const std::string &line)
{
    auto moduleType = ModuleType::Broadcast;
    if (line.front() == '%')
    {
        moduleType = ModuleType::FlipFlop;
    }
    else if (line.front() == '&')
    {
        moduleType = ModuleType::Conjunction;
    }
    return moduleType;
}

std::string CommunicationRelay::getModuleName(const std::string &line)
{
    std::string moduleName = "broadcaster";
    if (line.front() == '%' || line.front() == '&')
    {
        moduleName = line.substr(1);
    }
    return moduleName;
}

std::vector<std::string> CommunicationRelay::getModuleDestinations(const std::string &line)
{
    auto destinations = common::splitToMultipleString(line, ',');
    for (auto &destination : destinations)
    {
        std::erase(destination, ' ');
    }
    return destinations;
}

void CommunicationRelay::queueSignals(std::vector<Signal> &&signals)
{
    std::ranges::copy(signals, std::back_inserter(queue));
}
