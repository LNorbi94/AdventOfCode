#include "ConjunctionModule.h"

#include <algorithm>
#include <ranges>

void ConjunctionModule::addDestinations(const std::vector<std::string> &destinations_)
{
    destinations = destinations_;
}

void ConjunctionModule::addInput(const std::string &input)
{
    lastPulse[input] = Pulse::LowPulse;
}

std::vector<std::string> ConjunctionModule::getInputs() const
{
    std::vector<std::string> inputs;
    for (const auto &input : lastPulse | std::ranges::views::keys)
    {
        inputs.push_back(input);
    }
    return inputs;
}

std::vector<Signal> ConjunctionModule::receivePulse(const std::string &sender, Pulse pulse)
{
    lastPulse.at(sender) = pulse;
    const auto allHigh = std::ranges::all_of(lastPulse, [](const auto &pair)
                                             { return pair.second == Pulse::HighPulse; });
    const auto pulseToSend = allHigh ? Pulse::LowPulse : Pulse::HighPulse;
    std::vector<Signal> signals;
    std::ranges::for_each(destinations, [&](const auto &destination)
                          { signals.push_back({moduleName, destination, pulseToSend}); });
    return signals;
}
