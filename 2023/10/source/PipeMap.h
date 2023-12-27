#pragma once

#include "Pipe.h"

#include <optional>
#include <set>
#include <string_view>
#include <vector>
#include <variant>

class PipeMap
{
public:
    void addPipes(std::string_view line);

    void findLoop();
    int getLongestDistance();
    int getEnclosedArea();

private:
    void findEnclosedPipes(const Pipe& pipe);

    bool isValidId(const Id& id) const;
    bool isPartOfLoop(const Id& id) const;
    bool isPipeEnclosedInLoop(const Pipe& pipe) const;
    int getNumberOfEnclosingPipes(const Pipe& pipe, const std::vector< Id >& additionalPipes = {}) const;
    const Pipe& getPipe(const Id& id) const;
    std::optional< Pipe > getNextPipe(const Pipe& pipe, Direction& direction);

    std::vector< std::vector< Pipe > > m_pipes;
    Id m_startPipe = { -1, -1 };

    std::vector< Id > m_loop;
    std::vector< Id > m_insideLoop;
    std::vector< Id > m_visitedIds;
};
