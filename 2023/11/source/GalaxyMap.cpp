#include "GalaxyMap.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#include <fstream>

void GalaxyMap::addData(const std::string_view line)
{
    std::vector< GalaxyMapNode > nodes;
    Id nextId;
    nextId.row = m_nodes.size();
    bool isEmptyRow = true;
    for (const auto& node : line) {
        nodes.emplace_back(nextId, node);
        ++nextId.column;
        isEmptyRow = isEmptyRow && node == '.';
    }
    if (isEmptyRow) {
        for (auto& node : nodes) {
            node.setLength(node.length() * 2);
        }
    }
    m_nodes.emplace_back(nodes);
}

void GalaxyMap::correctLengthForExpansion()
{
    if (m_nodes.empty()) {
        return;
    }
    std::vector<bool> areColumnsEmpty( m_nodes[0].size(), true );
    for (auto i = 0; i < m_nodes.size(); ++i) {
        for (auto j = 0; j < m_nodes[i].size(); ++j) {
            areColumnsEmpty[j] = areColumnsEmpty[j] && m_nodes[i][j].getType() == NodeType::EmptySpace;
        }
    }

    for (auto j = 0; j < areColumnsEmpty.size(); ++j) {
        for (auto i = 0; i < m_nodes.size(); ++i) {
            if (areColumnsEmpty[j]) {
                m_nodes[i][j].setLength(m_nodes[i][j].length() * 2);
            }
        }
    }
}

uint64_t GalaxyMap::getSumOfShortestPaths(const int expansion)
{
    std::vector<Id> galaxies;
    for (const auto& row : m_nodes) {
        for (const auto& node : row) {
            if (node.getType() == NodeType::Galaxy) {
                galaxies.push_back(node.getId());
            }
        }
    }

    uint64_t sumOfShortestPaths = 0;
    for (auto i = 0; i < galaxies.size(); ++i) {
        for (auto j = i + 1; j < galaxies.size(); ++j) {
            sumOfShortestPaths += findShortestPath(galaxies[i], galaxies[j], expansion);
        }
    }

    return sumOfShortestPaths;
}

bool GalaxyMap::isValidId(const Id& id) const
{
    return id.row >= 0 && id.row < m_nodes.size() && id.column >= 0 && id.column < m_nodes[id.row].size();
}

GalaxyMapNode& GalaxyMap::getNode(const Id& id)
{
    return m_nodes[id.row][id.column];
}

uint64_t GalaxyMap::findShortestPath(const Id& first, const Id& second, const int expansion)
{
    struct MinimalNode
    {
        Id id;
        int distance;
    };

    struct
    {
        bool operator() (const MinimalNode& l, const MinimalNode& r) const { return l.distance > r.distance; }
    } nodeComparator;

    std::priority_queue<MinimalNode, std::vector<MinimalNode>, decltype(nodeComparator)> queue(nodeComparator);
    queue.emplace(first, 0);

    for (auto& row : m_nodes) {
        for (auto& node : row) {
            node.setDistance(std::numeric_limits<int>::max());
        }
    }

    while (!queue.empty()) {
        const auto node = queue.top();
        queue.pop();

        if (node.id == second) {
            break;
        }

        const auto& galaxyNode = getNode(node.id);
        for (const auto& neighbour : galaxyNode.getNeighbours()) {
            if (isValidId(neighbour)) {
                auto& neighbourNode = getNode(neighbour);
                auto distance = node.distance + neighbourNode.length();
                if (distance < neighbourNode.getDistance()) {
                    neighbourNode.setDistance(distance);
                    neighbourNode.setPrevious(node.id);
                    queue.emplace(neighbour, distance);
                }
            }
        }
    }

    const auto& endNode = getNode(second);
    uint64_t pathLength = 0;
    if (endNode.getDistance() < std::numeric_limits<int>::max()) {
        std::queue<Id> path;
        path.push(second);

        while (!path.empty()) {
            const auto id = path.front();
            path.pop();

            if (id == first) {
                break;
            }

            if (isValidId(id)) {
                const auto& node = getNode(id);
                uint64_t length = node.length() == 1 ? 1 : (node.length() * expansion / 2);
                pathLength += length;
                path.push(node.previous());
            }
        }
    }

    return pathLength;
}
