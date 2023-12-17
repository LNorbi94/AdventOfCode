#include "CityBlock.h"

CityBlock::CityBlock(Id id, int heatLoss)
    : m_id{ id }
    , m_heatLoss{ heatLoss }
{
}

const Id& CityBlock::getId() const
{
    return m_id;
}

int CityBlock::heatLoss() const
{
    return m_heatLoss;
}

int CityBlock::accumulatedHeatLoss(const Direction direction, int stepsTaken) const
{
    auto accumulatedHeatLoss = m_accumulatedHeatLoss.find(std::make_pair(direction, stepsTaken));
    if (accumulatedHeatLoss != m_accumulatedHeatLoss.cend()) {
        return accumulatedHeatLoss->second;
    }
    return std::numeric_limits<int>::max();
}

void CityBlock::setAccumulatedHeatLoss(const Direction direction, int stepsTaken, const int accumulatedHeatLoss)
{
    m_accumulatedHeatLoss[std::make_pair(direction, stepsTaken)] = accumulatedHeatLoss;
}

std::array<const Id, 4> CityBlock::getNeighbours() const
{
    const std::array< const Id, 4> neighbours{
        Id{ m_id.column, m_id.row - 1 },
        Id{ m_id.column, m_id.row + 1 },
        Id{ m_id.column - 1, m_id.row },
        Id{ m_id.column + 1, m_id.row }
    };
    return neighbours;
}

Id CityBlock::getNeighbour(Direction direction) const
{
    const auto neighbours = getNeighbours();
    return neighbours[static_cast<int>(direction)];
}
