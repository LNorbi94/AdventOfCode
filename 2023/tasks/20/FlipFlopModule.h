#pragma once

#include "IModule.h"

class FlipFlopModule : public IModule
{
public:
    void addDestinations(const std::vector<std::string> &destinations_) override;

    std::vector<Signal> receivePulse(const std::string &sender, Pulse pulse) override;

private:
    bool isOn = false;
    std::vector<std::string> destinations;
};
