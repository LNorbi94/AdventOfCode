#include "Tile.h"

Tile::Tile(Id id, const char type)
    : m_id{ id }
{
    switch (type) {
        case '.':
            m_type = TileType::EmptySpace;
            break;
        case '/':
            m_type = TileType::Mirror;
            break;
        case '\\':
            m_type = TileType::ReversedMirror;
            break;
        case '|':
            m_type = TileType::VerticalSplitter;
            break;
        case '-':
            m_type = TileType::HorizontalSplitter;
            break;
    }
}

void Tile::setEnergized(bool energized)
{
    m_energized = energized;
}

bool Tile::energized() const
{
    return m_energized;
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
    switch (direction) {
        case Direction::Left:
        {
            switch (m_type) {
                case TileType::EmptySpace:
                case TileType::HorizontalSplitter:
                    return { direction };
                case TileType::Mirror:
                    return { Direction::Bottom };
                case TileType::ReversedMirror:
                    return { (Direction::Top) };
                case TileType::VerticalSplitter:
                    return { (Direction::Top), (Direction::Bottom) };
            }
            break;
        }
        case Direction::Right:
        {
            switch (m_type) {
                case TileType::EmptySpace:
                case TileType::HorizontalSplitter:
                    return { (direction) };
                case TileType::Mirror:
                    return { (Direction::Top) };
                case TileType::ReversedMirror:
                    return { (Direction::Bottom) };
                case TileType::VerticalSplitter:
                    return { (Direction::Top), (Direction::Bottom) };
            }
            break;
        }
        case Direction::Top:
        {
            switch (m_type) {
                case TileType::EmptySpace:
                case TileType::VerticalSplitter:
                    return { (direction) };
                case TileType::Mirror:
                    return { (Direction::Right) };
                case TileType::ReversedMirror:
                    return { (Direction::Left) };
                case TileType::HorizontalSplitter:
                    return { (Direction::Left), (Direction::Right) };
            }
            break;
        }
        case Direction::Bottom:
        {
            switch (m_type) {
                case TileType::EmptySpace:
                case TileType::VerticalSplitter:
                    return { (direction) };
                case TileType::Mirror:
                    return { (Direction::Left) };
                case TileType::ReversedMirror:
                    return { (Direction::Right) };
                case TileType::HorizontalSplitter:
                    return { (Direction::Left), (Direction::Right) };
            }
            break;
        }
    }
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
