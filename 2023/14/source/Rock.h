#pragma once

class Rock
{
public:
    enum class Type
    {
        Rounded,
        CubeShaped,
        Empty
    };

    enum class Direction
    {
        North,
    };

    Rock() = default;
    Rock(char input);

    bool CanBeMoved() const;

    bool CanPlaceRockHere() const;

    char ToChar() const;

    Type GetType() const;

    void ChangeType(Type type_);

private:
    Type type = Type::Empty;
};
