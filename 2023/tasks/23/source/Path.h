#pragma once

#include "Id.h"
#include "PathType.h"

#include <vector>

class Path
{
public:
    Path(Id id, char type);

    void setDistance(int distance);

    int distance() const;
    const Id& getId() const;
    PathType getType() const;

    std::vector< Id > getNeighbours() const;
    std::vector< Id > getAlternativeNeighbours() const;

private:
    Id m_id;
    PathType m_type = PathType::Unknown;
    int m_distance = -1;
};
