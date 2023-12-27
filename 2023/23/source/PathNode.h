#pragma once

#include "Id.h"

#include <algorithm>
#include <vector>

struct PathNode
{
    Id id;
    std::vector< Id > route;

    bool operator<(const PathNode& node) const
    {
        return route.size() < node.route.size();
    }

    bool isInRoute(const Id& id) const
    {
        return std::ranges::contains(route, id);
    }
};
