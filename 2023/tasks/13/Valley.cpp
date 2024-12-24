#include "Valley.h"
#include "Valley.h"
#include "Valley.h"

void Valley::addRow(std::string row)
{
    m_valleyMap.addRow(std::move(row));
}

int64_t Valley::mirrorScore(const size_t withDifference) const
{
    const auto verticalLine = findMirrorLine(LineDirection::Vertical, withDifference);
    if (verticalLine.has_value()) {
        return verticalLine.value();
    }
    const auto horizontalLine = findMirrorLine(LineDirection::Horizontal, withDifference);
    return horizontalLine.value_or(0) * 100;
}

std::optional<size_t> Valley::findMirrorLine(LineDirection direction, size_t withDifference) const
{
    for (auto i = 1; i < m_valleyMap.size(direction); ++i) {
        if (differenceOfPerfectMirror(direction, i) == withDifference) {
            return i;
        }
    }
    return std::nullopt;
}

size_t Valley::differenceOfPerfectMirror(LineDirection direction, size_t idx) const
{
    size_t diff = 0;
    for (auto i = 0; i < m_valleyMap.size(direction); ++i) {
        diff += m_valleyMap.differentFields(direction, idx, i);
    }

    return diff;
}
