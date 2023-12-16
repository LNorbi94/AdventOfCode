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

    void setEnergized(bool energized);
    bool energized() const;

    const Id& getId() const;

    TileType getType() const;

    std::vector< Direction > getNextTiles(const Direction direction) const;
    //bool canMoveToPipe(const Direction direction, const char pipeTwo) const;

    Direction getDirectionToTile(const Id& id) const;
    //Direction getNewDirection(const Direction direction) const;

    std::array< const Id, 4 > getNeighbours() const;
    const Id& getNeighbour(Direction direction) const;

private:
    Id m_id;
    TileType m_type = TileType::Unknown;
    bool m_energized = false;
};