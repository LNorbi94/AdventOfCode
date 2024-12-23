#pragma once

#include "Tile.h"

#include <string_view>
#include <optional>
#include <vector>

class TileMap
{
public:
    void addTiles(std::string_view line);

    int getNumberOfPlots(int steps);

private:

    bool isValidId(const Id& id) const;
    Tile& getTile(const Id& id);

    std::vector< std::vector< Tile > > m_tiles;
    Id m_startingTile;
};
