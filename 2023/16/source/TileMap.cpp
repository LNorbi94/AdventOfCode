#include "TileMap.h"

#include <stack>

void TileMap::addTiles(std::string_view line)
{
    std::vector< Tile > tiles;
    Id nextId;
    nextId.column = m_tiles.size();
    for (const auto& pipe : line) {
        tiles.emplace_back(nextId, pipe);
        ++nextId.row;
    }
    m_tiles.emplace_back(tiles);
}

int TileMap::getNumberOfEnergizedFields(const std::pair< Direction, Id >& startingField)
{
    std::stack< std::pair< Direction, Id > > tiles;
    tiles.push(startingField);

    std::vector< std::pair< Direction, Id > > visitedPairs;
    visitedPairs.push_back(startingField);

    while (!tiles.empty()) {
        const auto [currentDirection, currentId] = tiles.top();
        tiles.pop();
        if (!isValidId(currentId)) {
            continue;
        }

        Tile& tile = getTile(currentId);
        tile.setEnergized(true);
        const auto nextDirections = tile.getNextTiles(currentDirection);
        for (const auto& direction : nextDirections) {
            const std::pair< Direction, Id > nextTile = { direction, tile.getNeighbour(direction) };
            auto visitedAlready = std::find(visitedPairs.cbegin(), visitedPairs.cend(), nextTile) != visitedPairs.cend();
            if (!visitedAlready) {
                tiles.push(nextTile);
                visitedPairs.push_back(nextTile);
            }
        }
    }

    auto energizedFields = 0;
    for (auto& row : m_tiles) {
        for (auto& tile : row) {
            if (tile.energized()) {
                ++energizedFields;
            }
            tile.setEnergized(false);
        }
    }
    return energizedFields;
}

int TileMap::getMaximumNumberOfEnergizedFields()
{
    auto maximumEnergizedField = 0;
    for (const auto& rowTiles : m_tiles) {
        for (const auto& tile : rowTiles) {
            const auto [column, row] = tile.getId();
            if (column == 0 && row == 0) {
                auto fromRight = getNumberOfEnergizedFields({ Direction::Right, tile.getId() });
                auto fromBottom = getNumberOfEnergizedFields({ Direction::Bottom, tile.getId() });
                if (fromRight > maximumEnergizedField) {
                    maximumEnergizedField = fromRight;
                }
                if (fromBottom > maximumEnergizedField) {
                    maximumEnergizedField = fromBottom;
                }
            } else if (column == 0 && row == rowTiles.size() - 1) {
                auto fromLeft = getNumberOfEnergizedFields({ Direction::Left, tile.getId() });
                auto fromBottom = getNumberOfEnergizedFields({ Direction::Bottom, tile.getId() });
                if (fromLeft > maximumEnergizedField) {
                    maximumEnergizedField = fromLeft;
                }
                if (fromBottom > maximumEnergizedField) {
                    maximumEnergizedField = fromBottom;
                }
            } else if (column == m_tiles.size() - 1 && row == 0) {
                auto fromRight = getNumberOfEnergizedFields({ Direction::Right, tile.getId() });
                auto fromTop = getNumberOfEnergizedFields({ Direction::Top, tile.getId() });
                if (fromRight > maximumEnergizedField) {
                    maximumEnergizedField = fromRight;
                }
                if (fromTop > maximumEnergizedField) {
                    maximumEnergizedField = fromTop;
                }
            } else if (column == m_tiles.size() - 1 && row == rowTiles.size() - 1) {
                auto fromLeft = getNumberOfEnergizedFields({ Direction::Left, tile.getId() });
                auto fromTop = getNumberOfEnergizedFields({ Direction::Top, tile.getId() });
                if (fromLeft > maximumEnergizedField) {
                    maximumEnergizedField = fromLeft;
                }
                if (fromTop > maximumEnergizedField) {
                    maximumEnergizedField = fromTop;
                }
            } else if (column == 0) {
                auto fromBottom = getNumberOfEnergizedFields({ Direction::Bottom, tile.getId() });
                if (fromBottom > maximumEnergizedField) {
                    maximumEnergizedField = fromBottom;
                }
            } else if (column == m_tiles.size() - 1) {
                auto fromTop = getNumberOfEnergizedFields({ Direction::Top, tile.getId() });
                if (fromTop > maximumEnergizedField) {
                    maximumEnergizedField = fromTop;
                }
            } else if (row == 0) {
                auto fromRight = getNumberOfEnergizedFields({ Direction::Right, tile.getId() });
                if (fromRight > maximumEnergizedField) {
                    maximumEnergizedField = fromRight;
                }
            }else if (row == rowTiles.size() - 1) {
                auto fromLeft = getNumberOfEnergizedFields({ Direction::Left, tile.getId() });
                if (fromLeft > maximumEnergizedField) {
                    maximumEnergizedField = fromLeft;
                }
            }
        }
    }
    return maximumEnergizedField;
}

bool TileMap::isValidId(const Id& id) const
{
    return id.column >= 0 && id.column < m_tiles.size() && id.row >= 0 && id.row < m_tiles[id.column].size();
}

Tile& TileMap::getTile(const Id& id)
{
    return m_tiles[id.column][id.row];
}
