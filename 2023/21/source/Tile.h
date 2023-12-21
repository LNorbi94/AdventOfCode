#pragma once

#include "Direction.h"
#include "Id.h"
#include "TileType.h"

#include <array>
#include <vector>

class Tile
{
public:
    Tile(Id id, const char type);

    void setDistance(int distance);
    int distance() const;

    const Id& getId() const;

    TileType getType() const;

    std::vector< Direction > getNextTiles(const Direction direction) const;

    Direction getDirectionToTile(const Id& id) const;

    std::array< const Id, 4 > getNeighbours() const;
    const Id& getNeighbour(Direction direction) const;

private:
    Id m_id;
    TileType m_type = TileType::Unknown;
    int m_distance = std::numeric_limits<int>::max();
};