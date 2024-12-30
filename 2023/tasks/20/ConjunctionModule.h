#pragma once

#include "IModule.h"

#include <map>

class ConjunctionModule : public IModule
{
public:
    void addDestinations(const std::vector<std::string> &destinations_) override;

    void addInput(const std::string &input) override;

    std::vector<std::string> getInputs() const override;

    std::vector<Signal> receivePulse(const std::string &sender, Pulse pulse) override;

private:
    std::vector<std::string> destinations;
    std::map<std::string, Pulse> lastPulse;
};
