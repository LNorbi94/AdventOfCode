#pragma once

#include <string>
#include <map>

#include "common/Range.h"

class PartRatings
{
public:
    enum class RangeType
    {
        Start,
        End
    };

    PartRatings();
    PartRatings(const PartRatings &) = default;
    PartRatings &operator=(const PartRatings &) = default;
    PartRatings(PartRatings &&) = default;
    PartRatings &operator=(PartRatings &&) = default;

    void setRating(char category, int64_t value, RangeType type);

    std::string getRule() const;
    void setRule(const std::string &rule);

    int64_t getNumberOfCombinations() const;

private:
    std::map<char, Range> m_ratings;
    std::string m_currentRule = "in";
};
