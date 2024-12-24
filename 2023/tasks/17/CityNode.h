#pragma once

#include "common/Graphs/Id.h"
#include "common/Direction.h"

struct CityNode
{
    Id id;
    int heatLoss = 0;
    Direction direction = Direction::Unknown;
    int stepsTaken = 0;
};
