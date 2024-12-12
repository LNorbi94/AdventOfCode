#pragma once

#include <string>
#include <optional>
#include <vector>

#include "ValleyMap.h"
#include "LineDirection.h"

class Valley
{
public:
    Valley() = default;

    void addRow(std::string row);

    int64_t mirrorScore(size_t withDifference = 0) const;

private:
    std::optional< size_t > findMirrorLine(LineDirection direction, size_t withDifference) const;

    size_t differenceOfPerfectMirror(LineDirection direction, size_t idx) const;

    ValleyMap m_valleyMap;
};
