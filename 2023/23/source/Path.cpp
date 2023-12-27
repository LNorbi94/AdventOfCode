#include "Path.h"

Path::Path(Id id, const char type)
    : m_id{ id }
{
    switch (type) {
        case '.':
            m_type = PathType::Normal;
            break;
        case '#':
            m_type = PathType::Forest;
            break;
        case '>':
            m_type = PathType::RightwardSlope;
            break;
        case '<':
            m_type = PathType::LeftwardSlope;
            break;
        case '^':
            m_type = PathType::UpwardSlope;
            break;
        case 'v':
            m_type = PathType::DownwardSlope;
            break;
    }
}

void Path::setDistance(const int distance)
{
    m_distance = distance;
}

int Path::distance() const
{
    return m_distance;
}

const Id& Path::getId() const
{
    return m_id;
}

PathType Path::getType() const
{
    return m_type;
}

std::vector< Id > Path::getNeighbours() const
{
    const std::vector< Id > neighbours{
        Id{ m_id.column, m_id.row - 1 },
        Id{ m_id.column, m_id.row + 1 },
        Id{ m_id.column - 1, m_id.row },
        Id{ m_id.column + 1, m_id.row }
    };

    switch (m_type) {
        case PathType::RightwardSlope:
            return { neighbours[1] };
        case PathType::LeftwardSlope:
            return { neighbours[0] };
        case PathType::UpwardSlope:
            return { neighbours[2] };
        case PathType::DownwardSlope:
            return { neighbours[3] };
        case PathType::Forest:
            return {};
    }

    return neighbours;
}

std::vector<Id> Path::getAlternativeNeighbours() const
{
    const std::vector< Id > neighbours{
        Id{ m_id.column, m_id.row - 1 },
        Id{ m_id.column, m_id.row + 1 },
        Id{ m_id.column - 1, m_id.row },
        Id{ m_id.column + 1, m_id.row }
    };

    switch (m_type) {
        case PathType::Forest:
            return {};
    }

    return neighbours;
}
