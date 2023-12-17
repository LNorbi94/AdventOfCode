#include "CityMap.h"

#include "CityNode.h"

#include <queue>

void CityMap::addCityBlocks(std::string_view line)
{
    std::vector< CityBlock > cityBlocks;
    Id nextId;
    nextId.column = m_cityBlocks.size();
    for (const auto& cityBlock : line) {
        cityBlocks.emplace_back(CityBlock{ nextId, cityBlock - '0' });
        ++nextId.row;
    }
    m_cityBlocks.emplace_back(cityBlocks);
}

int CityMap::getMinimalHeatLoss()
{
    CityNode startingNode;
    startingNode.id = Id{ 0, 0 };
    Id goalNode{ static_cast<int>(m_cityBlocks.size()) - 1, static_cast<int>(m_cityBlocks[0].size()) - 1 };
    for (const auto& direction : { Direction::Left, Direction::Right, Direction::Top, Direction::Bottom }) {
        getCityBlock(startingNode.id).setAccumulatedHeatLoss(direction, 0, 0);
    }

    struct
    {
        bool operator()(const CityNode& l, const CityNode& r) const { return l.heatLoss > r.heatLoss; }
    } nodeComparator;
    std::priority_queue<CityNode, std::vector<CityNode>, decltype(nodeComparator)> queue(nodeComparator);
    queue.push(startingNode);


    while (!queue.empty()) {
        const auto topNode = queue.top();
        queue.pop();

        if (topNode.id == goalNode) {
            return topNode.heatLoss;
        }

        const auto& node = getCityBlock(topNode.id);
        const auto reversedDirection = reverseDirection(topNode.direction);
        for (const auto& direction : { Direction::Left, Direction::Right, Direction::Top, Direction::Bottom }) {
            const auto neighbourId = node.getNeighbour(direction);
            if ((direction == topNode.direction && topNode.stepsTaken == 3) || direction == reversedDirection || !isValidId(neighbourId)) {
                continue;
            }

            auto stepsTaken = 1;
            if (direction == topNode.direction) {
                stepsTaken = topNode.stepsTaken + 1;
            }

            auto& neighbour = getCityBlock(neighbourId);
            const auto currentHeatLoss = topNode.heatLoss + neighbour.heatLoss();
            if (neighbour.accumulatedHeatLoss(direction, stepsTaken) > currentHeatLoss) {
                neighbour.setAccumulatedHeatLoss(direction, stepsTaken, currentHeatLoss);
                queue.emplace(CityNode{ neighbourId, currentHeatLoss, direction, stepsTaken });
            }
        }
    }

    return -1;
}

int CityMap::getMinimalHeatLossWithUltraCrucible()
{
    CityNode startingNode;
    startingNode.id = Id{ 0, 0 };
    Id goalNode{ static_cast<int>(m_cityBlocks.size()) - 1, static_cast<int>(m_cityBlocks[0].size()) - 1 };
    for (const auto& direction : { Direction::Left, Direction::Right, Direction::Top, Direction::Bottom }) {
        getCityBlock(startingNode.id).setAccumulatedHeatLoss(direction, 0, 0);
    }

    struct
    {
        bool operator()(const CityNode& l, const CityNode& r) const { return l.heatLoss > r.heatLoss; }
    } nodeComparator;
    std::priority_queue<CityNode, std::vector<CityNode>, decltype(nodeComparator)> queue(nodeComparator);
    queue.push(startingNode);


    while (!queue.empty()) {
        const auto topNode = queue.top();
        queue.pop();

        if (topNode.id == goalNode) {
            return topNode.heatLoss;
        }

        const auto& node = getCityBlock(topNode.id);
        const auto reversedDirection = reverseDirection(topNode.direction);
        for (const auto& direction : { Direction::Left, Direction::Right, Direction::Top, Direction::Bottom }) {
            const auto neighbourId = node.getNeighbour(direction);
            if ((topNode.direction != Direction::Unknown && direction != topNode.direction && topNode.stepsTaken < 4) || (direction == topNode.direction && topNode.stepsTaken == 10) || direction == reversedDirection || !isValidId(neighbourId)) {
                continue;
            }

            auto stepsTaken = 1;
            if (direction == topNode.direction) {
                stepsTaken = topNode.stepsTaken + 1;
            }

            auto& neighbour = getCityBlock(neighbourId);
            const auto currentHeatLoss = topNode.heatLoss + neighbour.heatLoss();
            if (neighbour.accumulatedHeatLoss(direction, stepsTaken) > currentHeatLoss) {
                neighbour.setAccumulatedHeatLoss(direction, stepsTaken, currentHeatLoss);
                queue.emplace(CityNode{ neighbourId, currentHeatLoss, direction, stepsTaken });
            }
        }
    }

    return -1;
}

bool CityMap::isValidId(const Id& id) const
{
    if (id.column > m_cityBlocks.size()) {
        return false;
    }
    return id.column >= 0 && id.column < m_cityBlocks.size() && id.row >= 0 && id.row < m_cityBlocks[id.column].size();
}

CityBlock& CityMap::getCityBlock(const Id& id)
{
    return m_cityBlocks[id.column][id.row];
}
