#pragma once

#include <string>
#include <vector>
#include <optional>

#include "Rock.h"

class Platform
{
public:
    enum class Direction
    {
        North,
        West,
        South,
        East
    };

    using RockIdx = std::pair<int64_t, int64_t>;

    void addRow(const std::string &line);

    void MoveRocksTo(Direction direction);

    void SpinCycle(size_t times);

    void SlowSpinCycle(size_t times);

    uint64_t CalculateMaxLoad();

private:
    bool IsValidIndex(RockIdx rockIdx) const;
    std::optional<RockIdx> GetNextRock(Direction direction, RockIdx rockIdx) const;
    void MoveRockToTheEnd(Direction direction, RockIdx rockIdx);

    std::vector<std::vector<Rock>> rocks;
};
