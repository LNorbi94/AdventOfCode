#pragma once

#include <cstdint>
#include <vector>

#include <set>

#include "common/Range.h"

class CafeteriaDatabase
{
public:
    // Add a range of fresh food IDs (inclusive: [from, to]).
    void AddFreshFoodRange(size_t from, size_t to);

    // Check if the given food ID falls into any fresh food range.
    // If not, increments the spoiled food counter.
    void InvestigateFood(size_t id);

    // Returns the number of spoiled foods (foods that were investigated
    // but did not fall into any fresh food range).
    size_t NumberOfFreshFood() const;

    size_t TotalNumberOfFreshFood() const;

private:
    std::vector<std::pair<size_t, size_t>> freshFoodRanges;
    std::vector<Range> freshFoodRanges_;
    size_t freshFoodCount = 0;
};
