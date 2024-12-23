#include "TrenchNode.h"

#include <array>

TrenchNode::TrenchNode(Id id, std::string rgbCode)
    : m_id{ id }
    , m_rgbCode{ rgbCode }
{
}

const Id& TrenchNode::getId() const
{
    return m_id;
}

std::vector<Id> TrenchNode::getNeighbours() const
{
    return m_neighbours;
}

std::vector<Id> TrenchNode::getNonTrenchNeighbours() const
{
    const std::array< const Id, 4> neighbours{
        Id{ m_id.column, m_id.row - 1 },
        Id{ m_id.column, m_id.row + 1 },
        Id{ m_id.column - 1, m_id.row },
        Id{ m_id.column + 1, m_id.row }
    };

    std::vector<Id> nonTrenchNeighbours;
    for (const auto& neighbour : neighbours) {
        if (std::find(m_neighbours.cbegin(), m_neighbours.cend(), neighbour) == m_neighbours.cend()) {
            nonTrenchNeighbours.push_back(neighbour);
        }
    }
    return nonTrenchNeighbours;
}

void TrenchNode::addNeighbour(Id id)
{
    m_neighbours.emplace_back(id);
}

Id TrenchNode::getNeighbour(const Direction direction) const
{
    const std::array< const Id, 4> neighbours{
        Id{ m_id.column, m_id.row - 1 },
        Id{ m_id.column, m_id.row + 1 },
        Id{ m_id.column - 1, m_id.row },
        Id{ m_id.column + 1, m_id.row }
    };
    return neighbours[static_cast<int>(direction)];
}
