#pragma once

#include "TrenchNode.h"

#include <set>
#include <string_view>
#include <optional>
#include <memory>
#include <vector>

#include "Geometry/Point.hpp"

class Trench
{
public:
    Trench();

    void dig(std::string_view line);
    void alternativeDig(std::string_view line);

    int64_t getPossibleLavaVolume();

private:

    std::set<std::shared_ptr<TrenchNode>> m_trench;
    std::set<std::shared_ptr<TrenchNode>> m_insideTrench;
    std::shared_ptr<TrenchNode> m_start;
    std::vector<Point> m_points;

    size_t pathLength = 0;
};
