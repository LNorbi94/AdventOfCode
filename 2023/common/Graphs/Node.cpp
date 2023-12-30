#include "Node.h"

Node::Node(Id id)
    : m_id{ std::move(id) }
    , m_neighbours{
        Id{ m_id.row, m_id.column - 1 },
        Id{ m_id.row, m_id.column + 1 },
        Id{ m_id.row - 1, m_id.column },
        Id{ m_id.row + 1, m_id.column }
    }
{}

void Node::setDistance(const int64_t distance)
{
    if (distance != m_distance) {
        m_distance = distance;
    }
}

int64_t Node::getDistance() const
{
    return m_distance;
}

const Id& Node::getId() const
{
    return m_id;
}

void Node::setPrevious(const Id& id)
{
    if (id != m_previous) {
        m_previous = id;
    }
}

const Id& Node::previous() const
{
    return m_previous;
}

Direction Node::getDirectionToField(const Id& id) const
{
    for (auto i = 0; i < m_neighbours.size(); ++i) {
        if (m_neighbours[i] == id) {
            return static_cast<Direction>(i);
        }
    }

    return Direction::Unknown;
}

const std::array<Id, 4>& Node::getNeighbours() const
{
    return m_neighbours;
}

const Id& Node::getNeighbour(const Direction direction) const
{
    return m_neighbours[static_cast<int>(direction)];
}
