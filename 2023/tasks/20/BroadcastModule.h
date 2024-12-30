#pragma once

#include "IModule.h"

class BroadcastModule : public IModule
{
public:
    void addDestinations(const std::vector<std::string> &destinations_) override;

    std::vector<Signal> receivePulse(const std::string &sender, Pulse pulse) override;

private:
    std::vector<std::string> destinations;
};
