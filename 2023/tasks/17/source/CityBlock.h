#pragma once

#include "Direction.h"
#include "Id.h"

#include <array>
#include <map>
#include <limits>

class CityBlock
{
public:
    CityBlock(Id id, int heatLoss);

    const Id& getId() const;

    int heatLoss() const;
    int accumulatedHeatLoss(Direction direction, int stepsTaken) const;
    void setAccumulatedHeatLoss(const Direction direction, int stepsTaken, int accumulatedHeatLoss);

    std::array< const Id, 4 > getNeighbours() const;
    Id getNeighbour(Direction direction) const;

private:
    Id m_id;
    int m_heatLoss = 0;
    std::map< std::pair< Direction, int >, int > m_accumulatedHeatLoss;
};
