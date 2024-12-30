#include "BroadcastModule.h"

#include <algorithm>

void BroadcastModule::addDestinations(const std::vector<std::string> &destinations_)
{
    destinations = destinations_;
}

std::vector<Signal> BroadcastModule::receivePulse(const std::string &, const Pulse pulse)
{
    std::vector<Signal> signals;
    std::ranges::for_each(destinations, [&](const auto &destination)
                          { signals.push_back({moduleName, destination, pulse}); });
    return signals;
}
