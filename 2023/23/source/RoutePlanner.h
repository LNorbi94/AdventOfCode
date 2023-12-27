#pragma once

#include "Path.h"

#include <string_view>
#include <vector>

class RoutePlanner
{
public:
    void addPaths(std::string_view line);

    int getLongestRoute();
    int getLongestDifficultRoute();

private:
    bool isValidId(const Id& id) const;
    Path& getPath(const Id& id);

    Id getNextPath(const Id& id, const std::vector< Id >& route);
    bool isIntersection(const Id& id, const std::vector< Id >& route);

    std::vector< std::vector< Path > > m_trail;
};
