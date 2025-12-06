#pragma once

#include <compare>
#include <string>

struct Id
{
    int row = 0;
    int column = 0;

    [[nodiscard]] constexpr auto operator<=>(const Id &rhs) const = default;

    operator std::string() const;
};
