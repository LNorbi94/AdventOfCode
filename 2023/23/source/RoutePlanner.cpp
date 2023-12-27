#include "RoutePlanner.h"
#include "PathNode.h"

#include <fstream>
#include <queue>

void RoutePlanner::addPaths(const std::string_view line)
{
    std::vector< Path > paths;
    Id nextId;
    nextId.column = m_trail.size();
    for (const auto& path : line) {
        paths.emplace_back(nextId, path);
        ++nextId.row;
    }
    m_trail.emplace_back(paths);
}

int RoutePlanner::getLongestRoute()
{
    Id startNode;
    for (auto& path : m_trail[0]) {
        if (path.getType() == PathType::Normal) {
            startNode = path.getId();
            path.setDistance(0);
        }
    }

    Id endNode;
    for (const auto& path : m_trail[m_trail.size() - 1]) {
        if (path.getType() == PathType::Normal) {
            endNode = path.getId();
        }
    }

    std::priority_queue< PathNode > queue;
    queue.push(PathNode{ startNode, { startNode } });

    while (!queue.empty()) {
        auto node = queue.top();
        queue.pop();

        auto& path = getPath(node.id);
        for (const auto& neighbour : path.getNeighbours()) {
            if (!isValidId(neighbour) || node.isInRoute(neighbour)) {
                continue;
            }

            int possibleDistance = node.route.size() + 1;
            auto& neighbourNode = getPath(neighbour);
            if (possibleDistance > neighbourNode.distance()) {
                neighbourNode.setDistance(possibleDistance);
                auto newNode = node;
                newNode.id = neighbour;
                newNode.route.push_back(neighbour);
                queue.emplace(newNode);
            }
        }
    }

    return getPath(endNode).distance() - 1;
}

int RoutePlanner::getLongestDifficultRoute()
{
    Id startNode;
    for (auto& path : m_trail[0]) {
        if (path.getType() == PathType::Normal) {
            startNode = path.getId();
            path.setDistance(0);
        }
    }

    Id endNode;
    for (const auto& path : m_trail[m_trail.size() - 1]) {
        if (path.getType() == PathType::Normal) {
            endNode = path.getId();
        }
    }

    std::queue< PathNode > queue;
    queue.push(PathNode{ startNode, { startNode } });

    auto bestDistance = 0;
    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();

        if (node.id == endNode) {
            auto currentDistance = node.route.size() - 1;
            if (bestDistance < currentDistance) {
                bestDistance = currentDistance;
            }
        }

        auto& path = getPath(node.id);
        for (const auto& neighbour : path.getAlternativeNeighbours()) {
            if (!isValidId(neighbour) || node.isInRoute(neighbour)) {
                continue;
            }
            auto& neighbourNode = getPath(neighbour);
            if (neighbourNode.getType() == PathType::Forest) {
                continue;
            }

            auto nextIntersection = neighbour;
            auto newRoute = node.route;
            newRoute.push_back(nextIntersection);
            while (!isIntersection(nextIntersection, newRoute)) {
                auto& nextPath = getPath(nextIntersection);
                nextIntersection = getNextPath(nextIntersection, newRoute);
                newRoute.push_back(nextIntersection);
            }

            queue.emplace(nextIntersection, newRoute);
        }
    }

    return bestDistance;
}

bool RoutePlanner::isValidId(const Id& id) const
{
    return id.column >= 0 && id.column < m_trail.size() && id.row >= 0 && id.row < m_trail[id.column].size();
}

Path& RoutePlanner::getPath(const Id& id)
{
    return m_trail[id.column][id.row];
}

Id RoutePlanner::getNextPath(const Id& id, const std::vector<Id>& route)
{
    auto& path = getPath(id);
    auto neighbours = 0;
    for (const auto& neighbour : path.getAlternativeNeighbours()) {
        if (!isValidId(neighbour) || std::ranges::contains(route, neighbour)) {
            continue;
        }
        auto& neighbourNode = getPath(neighbour);
        if (neighbourNode.getType() == PathType::Forest) {
            continue;
        }
        return neighbour;
    }
    return {};
}

bool RoutePlanner::isIntersection(const Id& id, const std::vector< Id >& route)
{
    auto& path = getPath(id);
    auto neighbours = 0;
    for (const auto& neighbour : path.getAlternativeNeighbours()) {
        if (!isValidId(neighbour) || std::ranges::contains(route, neighbour)) {
            continue;
        }
        auto& neighbourNode = getPath(neighbour);
        if (neighbourNode.getType() == PathType::Forest) {
            continue;
        }
        ++neighbours;
    }
    return neighbours != 1;
}
