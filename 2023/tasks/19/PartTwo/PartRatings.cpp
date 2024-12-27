#include "PartRatings.h"

#include <ranges>
#include <numeric>

PartRatings::PartRatings()
{
    m_ratings['x'] = Range{1, 4000};
    m_ratings['m'] = Range{1, 4000};
    m_ratings['a'] = Range{1, 4000};
    m_ratings['s'] = Range{1, 4000};
}

void PartRatings::setRating(const char category, const int64_t value, const RangeType type)
{
    switch (type)
    {
    case RangeType::Start:
        m_ratings.at(category).setStart(value);
        break;
    case RangeType::End:
        m_ratings.at(category).setEnd(value);
        break;
    }
}

std::string PartRatings::getRule() const
{
    return m_currentRule;
}

void PartRatings::setRule(const std::string &rule)
{
    m_currentRule = rule;
}

int64_t PartRatings::getNumberOfCombinations() const
{
    int64_t combinations = 1;
    for (const auto &range : m_ratings | std::views::values)
    {
        combinations *= range.getEnd() - range.getStart() + 1;
    }
    return combinations;
}
