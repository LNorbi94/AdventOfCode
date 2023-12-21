#pragma once

#include "Direction.h"
#include "Id.h"

#include <string>
#include <vector>

class TrenchNode
{
public:
    TrenchNode(Id id, std::string rgbCode);

    const Id& getId() const;

    std::vector< Id > getNeighbours() const;
    std::vector< Id > getNonTrenchNeighbours() const;
    void addNeighbour(Id id);
    Id getNeighbour(Direction direction) const;

private:
    Id m_id;
    std::string m_rgbCode;
    std::vector< Id > m_neighbours;
};
