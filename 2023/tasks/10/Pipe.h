#pragma once

#include "common/Direction.h"
#include "common/Graphs/Id.h"

#include <array>

class Pipe
{
public:
    Pipe(Id id, const char type);

    void setDistance(const int distance);
    int getDistance() const;

    Id getId() const;

    char getType() const;
    std::u8string_view prettyType() const;

    Id getNextPipe(const Direction direction) const;
    bool canMoveToPipe(const Direction direction, const char pipeTwo) const;

    Direction getDirectionToField(const Id &id) const;
    Direction getNewDirection(const Direction direction) const;

    std::array<const Id, 4> getNeighbours() const;
    Id getNeighbour(Direction direction) const;

private:
    Id m_id;
    int m_distance = -1;
    char m_type = '.';
};