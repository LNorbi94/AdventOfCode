#pragma once

#include <string>

enum class Direction
{
    Left,
    Right,
    Top,
    Bottom,
    Unknown
};

inline Direction stringToDirection(const std::string_view input)
{
    if (input == "R")
    {
        return Direction::Right;
    }
    else if (input == "L")
    {
        return Direction::Left;
    }
    else if (input == "D")
    {
        return Direction::Bottom;
    }
    else if (input == "U")
    {
        return Direction::Top;
    }
    return Direction::Unknown;
}

inline Direction reverseDirection(const Direction direction)
{
    switch (direction)
    {
    case Direction::Left:
        return Direction::Right;
    case Direction::Right:
        return Direction::Left;
    case Direction::Top:
        return Direction::Bottom;
    case Direction::Bottom:
        return Direction::Top;
    }
    return Direction::Unknown;
}
