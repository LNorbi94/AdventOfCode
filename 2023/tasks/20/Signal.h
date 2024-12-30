#pragma once

#include "Pulse.h"

#include <string>

struct Signal
{
    std::string sender;
    std::string destination;
    Pulse pulse;
};
