#pragma once

#include <optional>
#include <vector>

class Range
{
public:
    Range() = default;
    Range(size_t start, size_t end);

    std::optional<Range> getIntersection(const Range &other) const;

    std::vector<Range> getDifference(const Range &other);

    // Returns the parts of this range that are not covered by any range in the given vector.
    std::vector<Range> getDifferenceFromRanges(const std::vector<Range> &ranges) const;

    size_t getStart() const;

    void setStart(size_t start);

    size_t getEnd() const;

    void setEnd(size_t end);

    bool containsRange(const Range& other) const;

    bool containsValue(size_t value) const;

private:
    size_t m_start = 0;
    size_t m_end = 0;
};
