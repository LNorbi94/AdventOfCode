#pragma once

#include <optional>
#include <vector>

class Range
{
public:
    Range() = default;
    Range(int64_t start, int64_t end);

    std::optional<Range> getIntersection(const Range &other);

    std::vector<Range> getDifference(const Range &other);

    int64_t getStart() const;

    void setStart(int64_t start);

    int64_t getEnd() const;

    void setEnd(int64_t end);

    bool containsRange(const Range &other) const;

private:
    int64_t m_start = 0;
    int64_t m_end = 0;
};
