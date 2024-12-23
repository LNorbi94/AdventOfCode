#include "Rock.h"

Rock::Rock(char input)
{
    if (input == 'O')
    {
        type = Type::Rounded;
    }
    else if (input == '#')
    {
        type = Type::CubeShaped;
    }
}

bool Rock::CanBeMoved() const
{
    return type == Type::Rounded;
}

bool Rock::CanPlaceRockHere() const
{
    return type == Type::Empty;
}

char Rock::ToChar() const
{
    switch (type)
    {
    case Type::Rounded:
        return 'O';
    case Type::CubeShaped:
        return '#';
    case Type::Empty:
        return '.';
    }
    return 'X';
}

enum Rock::Type Rock::GetType() const
{
    return type;
}

void Rock::ChangeType(const Type type_)
{
    type = type_;
}
