#include "Valley.h"

void Valley::addRow(const std::string_view row)
{
    m_valleyMap.emplace_back(row);
}

int64_t Valley::mirrorScore() const
{
    const auto verticalLine = findVerticalMirrorLine();
    if (verticalLine.has_value()) {
        return verticalLine.value();
    }
    const auto horizontalLine = findHorizontalMirrorLine();
    return horizontalLine.value_or(0) * 100;
}

std::optional<size_t> Valley::findVerticalMirrorLine() const
{
    auto verticalLines = findVerticalMirrorLine(m_valleyMap[0]);
    for (const auto& verticalLine : verticalLines) {
        auto containsNumber = true;
        for (auto i = 1; i < m_valleyMap.size(); ++i) {
            const auto verticalLinesBelow = findVerticalMirrorLine(m_valleyMap[i]);
            containsNumber = containsNumber && std::find(verticalLinesBelow.cbegin(), verticalLinesBelow.cend(), verticalLine) != verticalLinesBelow.cend();
        }
        if (containsNumber) {
            return verticalLine;
        }
    }
    return std::optional<size_t>();
}

std::vector<size_t> Valley::findVerticalMirrorLine(std::string_view line) const
{
    std::vector< size_t > verticalMirrors;
    size_t possibleReflection = 0;
    bool isVerticallyMirrored = true;
    for (auto i = 0; i < line.size() / 2; ++i) {
        auto otherIdx = line.size() - 1 - i;
        if (line[i] != line[otherIdx]) {
            isVerticallyMirrored = false;
        }
    }

    if (isVerticallyMirrored) {
        verticalMirrors.emplace_back(line.size() / 2);
    }

    if (line.size() % 2 != 0) {
        isVerticallyMirrored = true;
        for (auto i = 1; i < line.size() / 2 + 1; ++i) {
            auto otherIdx = line.size() - i;
            if (line[i] != line[otherIdx]) {
                isVerticallyMirrored = false;
            }
        }
        if (isVerticallyMirrored) {
            verticalMirrors.emplace_back(line.size() / 2 + 1);
        }

        isVerticallyMirrored = true;
        for (auto i = 0; i < line.size() / 2; ++i) {
            auto otherIdx = line.size() - 2 - i;
            if (line[i] != line[otherIdx]) {
                isVerticallyMirrored = false;
            }
        }
        if (isVerticallyMirrored) {
            verticalMirrors.emplace_back(line.size() / 2);
        }
    }

    return verticalMirrors;
}

std::optional<size_t> Valley::findHorizontalMirrorLine() const
{
    if (m_valleyMap.size() % 2 == 0) {
        auto isHorizontallyMirrored = true;
        for (auto i = 0; i < m_valleyMap.size() / 2; ++i) {
            auto& line = m_valleyMap[i];
            auto& otherLine = m_valleyMap[m_valleyMap.size() - 1 - i];
            for (auto j = 0; j < line.size(); ++j) {
                if (line[j] != otherLine[j]) {
                    isHorizontallyMirrored = false;
                }
            }
        }

        if (isHorizontallyMirrored) {
            return m_valleyMap.size() / 2;
        }
    } else {
        auto isHorizontallyMirrored = true;
        for (auto i = 1; i < m_valleyMap.size() / 2 + 1; ++i) {
            auto& line = m_valleyMap[i];
            auto& otherLine = m_valleyMap[m_valleyMap.size() - i];
            for (auto j = 0; j < line.size(); ++j) {
                if (line[j] != otherLine[j]) {
                    isHorizontallyMirrored = false;
                }
            }
        }

        if (isHorizontallyMirrored) {
            return m_valleyMap.size() / 2 + 1;
        }

        isHorizontallyMirrored = true;
        for (auto i = 0; i < m_valleyMap.size() / 2; ++i) {
            auto& line = m_valleyMap[i];
            auto& otherLine = m_valleyMap[m_valleyMap.size() - 2 - i];
            for (auto j = 0; j < line.size(); ++j) {
                if (line[j] != otherLine[j]) {
                    isHorizontallyMirrored = false;
                }
            }
        }

        if (isHorizontallyMirrored) {
            return m_valleyMap.size() / 2;
        }
    }

    return 0;
}
