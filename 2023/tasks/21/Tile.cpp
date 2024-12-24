#include "Tile.h"

Tile::Tile(Id id, const char type)
    : m_id{ id }
{
    switch (type) {
        case '.':
            m_type = TileType::Plot;
            break;
        case '#':
            m_type = TileType::Rock;
            break;
        case 'S':
            m_type = TileType::Start;
            break;
    }

    if (m_type == TileType::Start) {
        m_distance = 0;
    }
}

void Tile::setDistance(int distance)
{
    m_distance = distance;
}

int Tile::distance() const
{
    return m_distance;
}

const Id& Tile::getId() const
{
    return m_id;
}

TileType Tile::getType() const
{
    return m_type;
}

std::vector<Direction> Tile::getNextTiles(const Direction direction) const
{
    return {};
}

Direction Tile::getDirectionToTile(const Id& id) const
{
    const auto& neighbours = getNeighbours();

    if (id == neighbours[0]) {
        return Direction::Left;
    } else if (id == neighbours[1]) {
        return Direction::Right;
    } else if (id == neighbours[2]) {
        return Direction::Top;
    } else if (id == neighbours[3]) {
        return Direction::Bottom;
    }

    return Direction::Unknown;
}

std::array<const Id, 4> Tile::getNeighbours() const
{
    const std::array< const Id, 4> neighbours{
        Id{ m_id.column, m_id.row - 1 },
        Id{ m_id.column, m_id.row + 1 },
        Id{ m_id.column - 1, m_id.row },
        Id{ m_id.column + 1, m_id.row }
    };
    return neighbours;
}

const Id& Tile::getNeighbour(Direction direction) const
{
    const auto neighbours = getNeighbours();
    return neighbours[static_cast<int>(direction)];
}
