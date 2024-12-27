#include "Range.h"

Range::Range(const int64_t start, const int64_t end)
    : m_start{start}, m_end{end}
{
}

std::optional<Range> Range::getIntersection(const Range &other)
{
    if (containsRange(other))
    {
        return other;
    }

    Range possibleIntersection{std::max(m_start, other.getStart()), std::min(m_end, other.getEnd())};
    if (containsRange(possibleIntersection))
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

int64_t Range::getStart() const
{
    return m_start;
}

void Range::setStart(int64_t start)
{
    m_start = start;
}

int64_t Range::getEnd() const
{
    return m_end;
}

void Range::setEnd(int64_t end)
{
    m_end = end;
}

bool Range::containsRange(const Range &other) const
{
    return m_start <= other.getStart() && m_end >= other.getEnd() && other.getStart() < other.getEnd();
}
