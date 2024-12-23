#pragma once

enum class Direction
{
    Left,
    Right,
    Top,
    Bottom,
    Unknown
};

inline
Direction reverseDirection(const Direction direction)
{
    if (direction == Direction::Left) {
        return Direction::Right;
    }
    else if (direction == Direction::Right) {
        return Direction::Left;
    }
    else if (direction == Direction::Top) {
        return Direction::Bottom;
    }
    else if (direction == Direction::Bottom) {
        return Direction::Top;
    }
    return Direction::Unknown;
}
