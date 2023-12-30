#pragma once

#include "GalaxyMapNode.h"

#include <string_view>
#include <vector>

class GalaxyMap
{
public:
    void addData(std::string_view line);
    void correctLengthForExpansion();

    uint64_t getSumOfShortestPaths(int expansion = 2);

private:
    bool isValidId(const Id& id) const;
    GalaxyMapNode& getNode(const Id& id);

    uint64_t findShortestPath(const Id& first, const Id& second, int expansion = 2);

    std::vector< std::vector< GalaxyMapNode > > m_nodes;
};
