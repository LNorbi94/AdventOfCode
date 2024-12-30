#pragma once

#include "Pulse.h"
#include "Signal.h"

#include <vector>

class IModule
{
public:
    ~IModule() = default;

    virtual void setModuleName(const std::string &name);

    virtual void addDestinations(const std::vector<std::string> &destinations) = 0;

    virtual void addInput(const std::string &input);

    virtual std::vector<std::string> getInputs() const;

    virtual std::vector<Signal> receivePulse(const std::string &sender, Pulse pulse) = 0;

protected:
    std::string moduleName;
};
