#pragma once

#include "Pipe.h"

#include <string_view>
#include <optional>
#include <vector>

class PipeMap
{
public:
    void addPipes(std::string_view line);

    void findLoop();
    int getLongestDistance();
    int getLargestEnclosedArea();

private:
    void calculateDistances();
    int getEnclosedArea(const Pipe& pipe, std::vector<Id>& visitedIdsGlobally);

    bool isValidId(const Id& id) const;
    bool isPartOfLoop(const Id& id) const;
    bool isPipeEnclosedInLoop(const Pipe& pipe) const;
    int getNumberOfEnclosingPipes(const Pipe& pipe) const;
    Pipe& getPipe(const Id& id);
    std::optional< Pipe > getNextPipe(const Pipe& pipe, Direction& direction);

    const std::vector< Id >& getLoop() const;

    std::vector< std::vector< Pipe > > m_pipes;
    Id m_startPipe = { -1, -1 };

    std::vector< std::vector< Id > > m_loops;
};
