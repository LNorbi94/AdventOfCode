#pragma once

#include <compare>
#include <string>

struct Id {
    int row = 0;
    int column = 0;

    auto operator<=>(const Id& rhs) const = default;

    operator std::string() const;
};
