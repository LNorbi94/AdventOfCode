#include "TileMap.h"

#include <set>
#include <queue>

#include <fstream>

void TileMap::addTiles(std::string_view line)
{
    std::vector< Tile > tiles;
    Id nextId;
    nextId.column = m_tiles.size();
    for (const auto& tile : line) {
        tiles.emplace_back(nextId, tile);
        if (tile == 'S') {
            m_startingTile = nextId;
        }
        ++nextId.row;
    }
    m_tiles.emplace_back(tiles);
}

int TileMap::getNumberOfPlots(int steps)
{
    struct
    {
        bool operator()(const Id& l, const Id& r) const { return r < l; }
    } idComparator;
    std::priority_queue<Id, std::vector<Id>, decltype(idComparator)> queue(idComparator);
    queue.push(m_startingTile);

    while (!queue.empty()) {
        const auto nextNode = queue.top();
        queue.pop();

        const auto& tile = getTile(nextNode);
        for (const auto& neighbour : tile.getNeighbours()) {
            if (!isValidId(neighbour)) {
                continue;
            }

            const auto distance = tile.distance() + 1;
            auto& neighbourTile = getTile(neighbour);
            if (neighbourTile.getType() == TileType::Rock) {
                continue;
            }
            if (distance < neighbourTile.distance()) {
                neighbourTile.setDistance(distance);
                queue.push(neighbour);
            }
        }
    }

    bool isEven = steps % 2 == 0;

    int plots = 0;
    for (const auto& row : m_tiles) {
        for (const auto& tile : row) {
            bool isTileEven = tile.distance() % 2 == 0;
            bool matchesEven = isEven ? isTileEven : !isTileEven;
            if (tile.distance() <= steps && matchesEven) {
                ++plots;
            }
        }
    }

    return plots;
}

bool TileMap::isValidId(const Id& id) const
{
    return id.column >= 0 && id.column < m_tiles.size() && id.row >= 0 && id.row < m_tiles[id.column].size();
}

Tile& TileMap::getTile(const Id& id)
{
    return m_tiles[id.column][id.row];
}
