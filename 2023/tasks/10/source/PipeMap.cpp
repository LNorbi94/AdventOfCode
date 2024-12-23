#include "PipeMap.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#include <fstream>

void PipeMap::addPipes(const std::string_view line)
{
    std::vector< Pipe > pipes;
    Id nextId;
    nextId.row = m_pipes.size();
    for (const auto& pipe : line) {
        pipes.emplace_back(nextId, pipe);

        if (pipe == 'S') {
            m_startPipe = nextId;
        }
        ++nextId.column;

        pipes.emplace_back(nextId, '#');
        ++nextId.column;
    }
    m_pipes.emplace_back(pipes);

    pipes = std::vector< Pipe >{};
    nextId.row += 1;
    nextId.column = 0;
    for (const auto& pipe : line) {
        pipes.emplace_back(nextId, '#');
        ++nextId.column;
        pipes.emplace_back(nextId, '#');
        ++nextId.column;
    }
    m_pipes.emplace_back(pipes);
}

void PipeMap::findLoop()
{
    std::vector< std::vector< Id > > loops;
    const auto& startPipe = getPipe(m_startPipe);
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
                route.push_back(nextPipe->getId());
                loops.emplace_back(route);
            }
        }
    }

    for (auto i = 0; i < loops.size(); ++i) {
        for (auto j = 0; j < loops.size(); ++j) {
            if (i != j && loops[i].size() == loops[j].size()) {
                m_loop = std::move(loops[i]);
            }
        }
    }
}

int PipeMap::getLongestDistance()
{
    return (std::ranges::count_if(m_loop, [this](const Id& id) { return getPipe(id).getType() != '#'; }) + 1) / 2;
}

int PipeMap::getEnclosedArea()
{
    for (const auto& row : m_pipes) {
        for (const auto& pipe : row) {
            if (!std::ranges::contains(m_visitedIds, pipe.getId()) && !isPartOfLoop(pipe.getId()) && isPipeEnclosedInLoop(pipe)) {
                findEnclosedPipes(pipe);
            }
        }
    }

    std::ofstream f("output.txt");
    for (const auto& row : m_pipes) {
        for (const auto& pipe : row) {
            const auto isInsideLoop = std::ranges::contains(m_insideLoop, pipe.getId());
            if (isInsideLoop) {
                f << "I";
            } else if (isPartOfLoop(pipe.getId())) {
                const auto type = pipe.prettyType();
                std::string out{ type.cbegin(), type.cend() };
                f << out;
            } else {
                f << "O";
            }
        }
        f << "\n";
    }

    return std::ranges::count_if(m_insideLoop, [this](const Id& id) { return getPipe(id).getType() != '#'; });
}

void PipeMap::findEnclosedPipes(const Pipe& pipe)
{
    auto area = 0;
    if (pipe.getType() == 'S') {
        return;
    }

    std::queue< Id > enclosedPipes;
    m_visitedIds.push_back(pipe.getId());
    enclosedPipes.push(pipe.getId());

    std::vector<Id> visitedPipes;
    visitedPipes.push_back(pipe.getId());
    while (!enclosedPipes.empty()) {
        const auto nextPipeId = enclosedPipes.front();
        enclosedPipes.pop();
        m_visitedIds.push_back(nextPipeId);

        if (!isValidId(nextPipeId)) {
            return;
        }

        auto& nextPipe = getPipe(nextPipeId);
        for (const auto& neighbour : nextPipe.getNeighbours()) {
            const auto partOfInsideLoop = std::ranges::contains(visitedPipes, neighbour);
            const auto partOfLoop = isPartOfLoop(neighbour);
            if (!partOfInsideLoop && !partOfLoop) {
                visitedPipes.push_back(neighbour);
                enclosedPipes.push(neighbour);
            }
        }
    }

    for (const auto& pipe : visitedPipes) {
        if (!isPartOfLoop(pipe) && !std::ranges::contains(m_insideLoop, pipe)) {
            m_insideLoop.emplace_back(pipe);
        }
    }
}

bool PipeMap::isValidId(const Id& id) const
{
    return id.row >= 0 && id.row < m_pipes.size() && id.column >= 0 && id.column < m_pipes[id.row].size();
}

bool PipeMap::isPartOfLoop(const Id& id) const
{
    return std::ranges::contains(m_loop, id);
}

bool PipeMap::isPipeEnclosedInLoop(const Pipe& pipe) const
{
    return getNumberOfEnclosingPipes(pipe) >= 2;
}

int PipeMap::getNumberOfEnclosingPipes(const Pipe& pipe, const std::vector<Id>& additionalPipes) const
{
    const auto& neighbours = pipe.getNeighbours();
    auto enclosingNeighbours = 0;
    for (const auto& neighbour : neighbours) {
        if (isValidId(neighbour)) {
            if (isPartOfLoop(neighbour) || std::ranges::contains(additionalPipes, neighbour)) {
                ++enclosingNeighbours;
            }
        } else {
            return -1;
        }
    }
    return enclosingNeighbours;
}

const Pipe& PipeMap::getPipe(const Id& id) const
{
    return m_pipes[id.row][id.column];
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
