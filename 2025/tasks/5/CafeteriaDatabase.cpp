#include "CafeteriaDatabase.h"

#include <iostream>

void CafeteriaDatabase::AddFreshFoodRange(size_t from, size_t to)
{
    freshFoodRanges.emplace_back(from, to);

    Range freshFoodRange(from, to);
    freshFoodRanges_.append_range(freshFoodRange.getDifferenceFromRanges(freshFoodRanges_));
}

void CafeteriaDatabase::InvestigateFood(const size_t id)
{
    bool isInRange = false;

    for (const auto &range : freshFoodRanges_)
    {
        if (range.containsValue(id))
        {
            isInRange = true;
            break;
        }
    }

    if (isInRange)
    {
        ++freshFoodCount;
    }
}

size_t CafeteriaDatabase::NumberOfFreshFood() const
{
    return freshFoodCount;
}

size_t CafeteriaDatabase::TotalNumberOfFreshFood() const
{
    size_t freshFoodCount_ = 0;
    for (const auto &range : freshFoodRanges_)
    {
        //std::cout << "Added " << (range.getEnd() - range.getStart() + 1) << " number of fresh foods" << std::endl;
        freshFoodCount_ += (range.getEnd() - range.getStart() + 1);
    }
    return freshFoodCount_;
}
