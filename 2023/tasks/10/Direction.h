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
    switch (direction) {
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
