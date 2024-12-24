#include "Pipe.h"

Pipe::Pipe(Id id, const char type)
    : m_id{ id }
    , m_type{ type }
{}

void Pipe::setDistance(const int distance)
{
    m_distance = distance;
}

int Pipe::getDistance() const
{
    return m_distance;
}

Id Pipe::getId() const
{
    return m_id;
}

char Pipe::getType() const
{
    return m_type;
}

std::u8string_view Pipe::prettyType() const
{
    switch (m_type) {
    case '|':
        return u8"│";
    case '-':
        return u8"━";
    case '7':
        return u8"┑";
    case 'F':
        return u8"┍";
    case 'L':
        return u8"┕";
    case 'J':
        return u8"┙";
    }
    return u8"";
}

Id Pipe::getNextPipe(const Direction direction) const
{
    auto [row, column] = m_id;
    if (direction == Direction::Bottom) {
        return { row + 1, column };
    }
    else if (direction == Direction::Top) {
        return { row - 1, column };
    }
    else if (direction == Direction::Left) {
        return { row, column - 1 };
    }
    else if (direction == Direction::Right) {

        return { row, column + 1 };
    }
    return { -1, -1 };
}

bool Pipe::canMoveToPipe(const Direction direction, const char pipeTwo) const
{
    if (pipeTwo == 'S' || pipeTwo == '#' || m_type == '#') {
        return true;
    }
    if (m_type == '.') {
        return false;
    }
    if (direction == Direction::Bottom) {
        return pipeTwo == '|' || pipeTwo == 'L' || pipeTwo == 'J';
    }
    else if (direction == Direction::Top) {
        return pipeTwo == '|' || pipeTwo == '7' || pipeTwo == 'F';
    }
    else if (direction == Direction::Left) {
        return pipeTwo == '-' || pipeTwo == 'F' || pipeTwo == 'L';
    }
    else if (direction == Direction::Right) {
        return pipeTwo == '-' || pipeTwo == '7' || pipeTwo == 'J';
    }
    return false;
}

Direction Pipe::getDirectionToField(const Id& id) const
{
    const std::array< const Id, 4> neighbours = getNeighbours();

    if (id == neighbours[0]) {
        return Direction::Top;
    }
    else if (id == neighbours[1]) {
        return Direction::Bottom;
    }
    else if (id == neighbours[2]) {
        return Direction::Left;
    }
    else if (id == neighbours[3]) {
        return Direction::Right;
    }
    return Direction::Unknown;
}

Direction Pipe::getNewDirection(const Direction direction) const
{
    switch (m_type) {
        case '#':
        case '|':
        case '-':
            return direction;
        case '7':
            return direction == Direction::Top ? Direction::Left : Direction::Bottom;
        case 'F':
            return direction == Direction::Top ? Direction::Right : Direction::Bottom;
        case 'L':
            return direction == Direction::Bottom ? Direction::Right : Direction::Top;
        case 'J':
            return direction == Direction::Bottom ? Direction::Left : Direction::Top;
    }
    return Direction::Unknown;
}

std::array<const Id, 4> Pipe::getNeighbours() const
{
    const std::array< const Id, 4> neighbours{
        Id{ m_id.row - 1, m_id.column },
        Id{ m_id.row + 1, m_id.column },
        Id{ m_id.row, m_id.column - 1 },
        Id{ m_id.row, m_id.column + 1 }
    };
    return neighbours;
}

Id Pipe::getNeighbour(Direction direction) const
{
    const std::array< const Id, 4> neighbours{
        Id{ m_id.row, m_id.column - 1 },
        Id{ m_id.row, m_id.column + 1 },
        Id{ m_id.row - 1, m_id.column },
        Id{ m_id.row + 1, m_id.column }
    };

    return neighbours[static_cast<int>(direction)];
}
