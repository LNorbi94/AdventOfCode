#pragma once

#include "Pulse.h"

#include <string>
#include <vector>

class Signal
{
    std::vector< std::string > destination;
    Pulse pulse;
};

class Module
{
public:
    virtual Signal receivePulse(Pulse pulse) = 0;

private:
    std::vector< std::string > m_destinationModules;
};
