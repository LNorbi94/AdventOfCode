#include "FlipFlopModule.h"

#include <algorithm>

void FlipFlopModule::addDestinations(const std::vector<std::string> &destinations_)
{
    destinations = destinations_;
}

std::vector<Signal> FlipFlopModule::receivePulse(const std::string &, Pulse pulse)
{
    if (pulse == Pulse::HighPulse)
    {
        return {};
    }

    std::vector<Signal> signals;
    const auto pulseToSend = isOn ? Pulse::LowPulse : Pulse::HighPulse;
    std::ranges::for_each(destinations, [&](const auto &destination)
                          { signals.push_back({moduleName, destination, pulseToSend}); });

    isOn = !isOn;
    return signals;
}
