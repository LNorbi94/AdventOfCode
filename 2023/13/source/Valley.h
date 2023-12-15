#pragma once

#include <string>
#include <optional>
#include <vector>

class Valley
{
public:
    Valley() = default;

    void addRow(std::string_view row);

    int64_t mirrorScore() const;

private:
    std::optional< size_t > findVerticalMirrorLine() const;
    std::vector< size_t > findVerticalMirrorLine(std::string_view line) const;
    std::optional< size_t > findHorizontalMirrorLine() const;

    std::vector< std::string > m_valleyMap;
};
