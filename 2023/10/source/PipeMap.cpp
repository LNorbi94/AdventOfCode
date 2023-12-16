#include "PipeMap.h"

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

void PipeMap::addPipes(const std::string_view line)
{
    std::vector< Pipe > pipes;
    Id nextId;
    nextId.column = m_pipes.size();
    for (const auto& pipe : line) {
        pipes.emplace_back(nextId, pipe);

        if (pipe == 'S') {
            m_startPipe = nextId;
        }
        ++nextId.row;
    }
    m_pipes.emplace_back(pipes);
}

void PipeMap::findLoop()
{
    auto& startPipe = getPipe(m_startPipe);
    for (const auto& neighbour : startPipe.getNeighbours()) {
        if (isValidId(neighbour)) {
            std::vector< Id > route;
            std::optional< Pipe > nextPipe = getPipe(neighbour);
            route.push_back(nextPipe->getId());
            auto direction = startPipe.getDirectionToField(neighbour);
            nextPipe = getNextPipe(*nextPipe, direction);
            while (nextPipe.has_value() && nextPipe->getId() != m_startPipe && nextPipe->getId() != neighbour) {
                route.push_back(nextPipe->getId());
                nextPipe = getNextPipe(*nextPipe, direction);
            }
            if (nextPipe.has_value() && nextPipe->getType() == 'S') {
                m_loops.emplace_back(route);
            }
        }
    }
}

int PipeMap::getLongestDistance()
{
    calculateDistances();

    auto longestDistance = 0;
    for (const auto& row : m_pipes) {
        for (const auto& pipe : row) {
            if (pipe.getDistance() > longestDistance) {
                longestDistance = pipe.getDistance();
            }
        }
    }
    return longestDistance;
}

int PipeMap::getLargestEnclosedArea()
{
    auto totalArea = 0;

    std::vector< Id > visitedIds;

    for (const auto& row : m_pipes) {
        for (const auto& pipe : row) {
            auto visitedAlready = std::any_of(visitedIds.cbegin(), visitedIds.cend(), [pipe](const Id& id) {return id == pipe.getId(); });
            if (visitedAlready) {
                continue;
            }
            auto partOfLoop = isPartOfLoop(pipe.getId());
            if (!partOfLoop && isPipeEnclosedInLoop(pipe)) {
                std::cout << pipe.getId().column << ":" << pipe.getId().row << "\n";
                continue;
                const auto enclosedArea = getEnclosedArea(pipe, visitedIds);
                if (enclosedArea != -1) {
                    totalArea += enclosedArea;
                }
            }
        }
    }

    return totalArea;
}

void PipeMap::calculateDistances()
{
    for (const auto& loop : m_loops) {
        for (auto i = 0; i < loop.size(); ++i) {
            auto distance = i + 1;
            auto& pipe = getPipe(loop[i]);
            if (pipe.getDistance() != -1 && pipe.getDistance() > distance) {
                pipe.setDistance(distance);
            }
            else if (pipe.getDistance() == -1) {
                pipe.setDistance(distance);
            }
        }
    }
}

int PipeMap::getEnclosedArea(const Pipe& pipe, std::vector<Id>& visitedIdsGlobally)
{
    auto area = 1;
    if (pipe.getType() == 'S') {
        return -1;
    }

    for (const auto& firstNeighbour : pipe.getNeighbours()) {
        if (isPartOfLoop(firstNeighbour)) {
            continue;
        }

        auto& firstPipe = getPipe(firstNeighbour);

        if (!isPipeEnclosedInLoop(firstPipe)) {
            return -1;
        }
        ++area;

        std::stack< Pipe > enclosedPipes;
        enclosedPipes.push(firstPipe);

        std::vector< Id > visitedIds;
        visitedIds.push_back(pipe.getId());
        visitedIds.push_back(firstPipe.getId());

        Pipe* lastPipe = nullptr;

        while (!enclosedPipes.empty()) {
            auto currentPipe = enclosedPipes.top();
            lastPipe = &currentPipe;
            enclosedPipes.pop();

            for (const auto& neighbour : currentPipe.getNeighbours()) {
                auto visitedAlready = std::any_of(visitedIds.cbegin(), visitedIds.cend(), [neighbour](const Id& id) { return id == neighbour; });
                if (visitedAlready) {
                    continue;
                }

                auto& neighbourPipe = getPipe(neighbour);
                if (!isPartOfLoop(neighbour)) {
                    if (isPipeEnclosedInLoop(neighbourPipe)) {
                        area++;
                        enclosedPipes.push(neighbourPipe);
                        visitedIds.push_back(neighbour);
                    } else {
                        return -1;
                    }
                }
            }
        }

        if (lastPipe != nullptr && getNumberOfEnclosingPipes(*lastPipe) < 3) {
            return -1;
        }
        visitedIdsGlobally.append_range(visitedIds);
    }

    return area;
}

bool PipeMap::isValidId(const Id& id) const
{
    return id.column >= 0 && id.column < m_pipes.size() && id.row >= 0 && id.row < m_pipes[id.column].size();
}

bool PipeMap::isPartOfLoop(const Id& id) const
{
    return std::any_of(getLoop().cbegin(), getLoop().cend(), [id](const Id& loopId) { return loopId == id; });
}

bool PipeMap::isPipeEnclosedInLoop(const Pipe& pipe) const
{
    return getNumberOfEnclosingPipes(pipe) >= 2;
}

int PipeMap::getNumberOfEnclosingPipes(const Pipe& pipe) const
{
    const auto& neighbours = pipe.getNeighbours();
    int neighboursFromLoop = 0;
    for (const auto& neighbour : neighbours) {
        if (isValidId(neighbour)) {
            if (isPartOfLoop(neighbour)) {
                ++neighboursFromLoop;
            }
        } else {
            return -1;
        }
    }
    return neighboursFromLoop;
}

Pipe& PipeMap::getPipe(const Id& id)
{
    return m_pipes[id.column][id.row];
}

std::optional<Pipe> PipeMap::getNextPipe(const Pipe& pipe, Direction& direction)
{
    const auto newDirection = pipe.getNewDirection(direction);
    const auto nextId = pipe.getNextPipe(newDirection);
    if (isValidId(nextId)) {
        const auto& nextPossiblePipe = getPipe(nextId);
        if (pipe.canMoveToPipe(newDirection, nextPossiblePipe.getType())) {
            direction = newDirection;
            return nextPossiblePipe;
        }
    }
    return {};
}

const std::vector<Id>& PipeMap::getLoop() const
{
    auto biggestLoop = 0;
    for (auto i = 1; i < m_loops.size(); ++i) {
        if (m_loops[i].size() > m_loops[biggestLoop].size()) {
            biggestLoop = i;
        }
    }
    return m_loops[biggestLoop];
}
