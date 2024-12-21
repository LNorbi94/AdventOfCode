#pragma once

#include "Direction.h"
#include "Id.h"

#include <array>

class Node
{
public:
    Node(Id id);

    void setDistance(const int64_t distance);
    int64_t getDistance() const;

    const Id& getId() const;

    void setPrevious(const Id& id);
    const Id& previous() const;


    Direction getDirectionToField(const Id& id) const;

    const std::array<Id, 4>& getNeighbours() const;
    const Id& getNeighbour(Direction direction) const;

private:
    Id m_id;
    Id m_previous;
    int64_t m_distance = -1;

    const std::array<Id, 4> m_neighbours;
};