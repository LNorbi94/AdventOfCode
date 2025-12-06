#include "Range.h"

Range::Range(const size_t start, const size_t end)
    : m_start{start}, m_end{end}
{
}

std::optional<Range> Range::getIntersection(const Range &other) const
{
    if (containsRange(other))
    {
        return other;
    }

    Range possibleIntersection{std::max(m_start, other.getStart()), std::min(m_end, other.getEnd())};
    // Check if the possible intersection is valid (start <= end) and if this range contains it
    if (possibleIntersection.getStart() <= possibleIntersection.getEnd() && containsRange(possibleIntersection))
    {
        return possibleIntersection;
    }
    return {};
}

std::vector<Range> Range::getDifference(const Range &other)
{
    auto intersection = getIntersection(other);
    if (!intersection.has_value())
    {
        return {other};
    }

    std::vector<Range> ranges;
    Range lowerDiff{other.getStart(), intersection->getStart() - 1};
    if (other.containsRange(lowerDiff))
    {
        ranges.push_back(lowerDiff);
    }
    Range upperDiff{intersection->getEnd() + 1, other.getEnd()};
    if (other.containsRange(upperDiff))
    {
        ranges.push_back(upperDiff);
    }

    return ranges;
}

std::vector<Range> Range::getDifferenceFromRanges(const std::vector<Range> &ranges) const
{
    std::vector<Range> remaining = {*this};

    for (const auto &range : ranges)
    {
        std::vector<Range> newRemaining;
        for (const auto &currentRange : remaining)
        {
            // Compute intersection to find what needs to be removed
            auto intersection = currentRange.getIntersection(range);
            if (!intersection.has_value())
            {
                // No overlap, keep the entire current range
                newRemaining.push_back(currentRange);
            }
            else
            {
                // Add parts before and after the intersection
                // Only add "before" part if there's actually something before the intersection
                if (currentRange.getStart() < intersection->getStart())
                {
                    // Safe: we know intersection->getStart() > currentRange.getStart(), so >= 1
                    newRemaining.emplace_back(currentRange.getStart(), intersection->getStart() - 1);
                }
                // Only add "after" part if there's actually something after the intersection
                if (intersection->getEnd() < currentRange.getEnd())
                {
                    newRemaining.emplace_back(intersection->getEnd() + 1, currentRange.getEnd());
                }
            }
        }
        remaining = std::move(newRemaining);
    }

    return remaining;
}

size_t Range::getStart() const
{
    return m_start;
}

void Range::setStart(size_t start)
{
    m_start = start;
}

size_t Range::getEnd() const
{
    return m_end;
}

void Range::setEnd(size_t end)
{
    m_end = end;
}

bool Range::containsRange(const Range &other) const
{
    return m_start <= other.getStart() && m_end >= other.getEnd() && other.getStart() <= other.getEnd();
}

bool Range::containsValue(const size_t value) const
{
    return m_start <= value && value <= m_end;
}
