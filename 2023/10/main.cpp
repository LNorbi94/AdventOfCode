#include "TaskSolver.h"
#include "StringManipulation.h"

#include <regex>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

struct Id {
    int column = 0;
    int row = 0;

    bool operator!=(const Id& otherId) const
    {
        return column != otherId.column || row != otherId.row;
    }

    bool operator==(const Id& otherId) const
    {
        return column == otherId.column && row == otherId.row;
    }
};

enum Direction
{
    Left,
    Right,
    Top,
    Bottom,
    Unknown
};

class Pipe
{
public:

    Pipe(Id id, const char type)
        : m_id{ id }
        , m_type{ type }
    {}

    void setDistance(const int distance)
    {
        m_distance = distance;
    }

    int getDistance() const
    {
        return m_distance;
    }

    Id getId() const
    {
        return m_id;
    }

    char getType() const
    {
        return m_type;
    }

    Id getNextPipe(const Direction direction) const
    {
        auto [column, row] = m_id;
        if (direction == Direction::Bottom) {
            return { column + 1, row };
        } else if (direction == Direction::Top) {
            return { column - 1, row };
        } else if (direction == Direction::Left) {
            return { column, row - 1 };
        } else if (direction == Direction::Right) {

            return { column, row + 1 };
        }
        return { -1, -1 };
    }

    Direction getDirectionToField(const Id& id) const
    {
        const std::array< const Id, 4> neighbours{
            Id{ m_id.column - 1, m_id.row },
            Id{ m_id.column + 1, m_id.row },
            Id{ m_id.column, m_id.row - 1 },
            Id{ m_id.column, m_id.row + 1 }
        };
        if (id == neighbours[0]) {
            return Direction::Top;
        } else if (id == neighbours[1]) {
            return Direction::Bottom;
        } else if (id == neighbours[2]) {
            return Direction::Left;
        } else if (id == neighbours[3]) {
            return Direction::Right;
        }
        return Direction::Unknown;
    }

    bool canMoveToPipe(const Direction direction, const char pipeTwo) const
    {
        if (pipeTwo == 'S') {
            return true;
        }
        if (direction == Direction::Bottom) {
            return pipeTwo == '|' || pipeTwo == 'L' || pipeTwo == 'J';
        } else if (direction == Direction::Top) {
            return pipeTwo == '|' || pipeTwo == '7' || pipeTwo == 'F';
        }else if (direction == Direction::Left) {
            return pipeTwo == '-' || pipeTwo == 'F' || pipeTwo == 'L';
        } else if (direction == Direction::Right) {
            return pipeTwo == '-' || pipeTwo == '7' || pipeTwo == 'J';
        }
        return false;
    }

    Direction getNewDirection(const Direction direction) const
    {
        switch (m_type) {
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

    std::array< const Id, 4 > getNeighbours() const
    {
        const std::array< const Id, 4> neighbours{
            Id{ m_id.column - 1, m_id.row },
            Id{ m_id.column + 1, m_id.row },
            Id{ m_id.column, m_id.row - 1 },
            Id{ m_id.column, m_id.row + 1 }
        };
        return neighbours;
    }

private:
    Id m_id;
    int m_distance = -1;
    char m_type = '.';
};

class FirstTaskSolver : public TaskSolver
{
public:
    FirstTaskSolver(const std::string_view fileName)
        : TaskSolver{ fileName }
    {
    }

    void parseLine(std::string_view line) override
    {
        std::vector< Pipe > pipes;
        Id nextId;
        nextId.column = m_pipes.size();
        for (const auto& pipe : line) {
            pipes.emplace_back(nextId, pipe);

            if (pipe == 'S') {
                m_startPipe = nextId;
            }
            ++nextId.row;
        }
        m_pipes.push_back(std::move(pipes));
    }

    void solveMap()
    {
        std::vector< std::vector< Id > > routes;
        const Id upperNeighbour = { m_startPipe.column - 1, m_startPipe.row };
        const Id lowerNeighbour = { m_startPipe.column + 1, m_startPipe.row };
        const Id rightNeighbour = { m_startPipe.column, m_startPipe.row + 1 };
        const Id leftNeighbour = { m_startPipe.column, m_startPipe.row - 1 };
        auto& startPipe = getPipe(m_startPipe);
        for (const auto& neighbour : { upperNeighbour, lowerNeighbour, rightNeighbour, leftNeighbour }) {
            if (isValidId(neighbour)) {
                std::vector< Id > route;
                std::optional< Pipe > nextPipe = getPipe(neighbour);
                route.push_back(nextPipe->getId());
                auto direction = startPipe.getDirectionToField(neighbour);
                nextPipe = getNextPipe(*nextPipe, direction);
                if (nextPipe.has_value()) {
                    std::cout << nextPipe->getType() << " -> ";
                }
                while (nextPipe.has_value() && nextPipe->getId() != m_startPipe && nextPipe->getId() != neighbour) {
                    route.push_back(nextPipe->getId());
                    nextPipe = getNextPipe(*nextPipe, direction);
                    if (nextPipe.has_value()) {
                        std::cout << nextPipe->getType() << "\n";
                    }
                }
                if (nextPipe.has_value() && nextPipe->getType() == 'S') {
                    routes.push_back(route);
                }
            }
        }

        for (const auto& route : routes) {
            for (auto i = 0; i < route.size(); ++i) {
                auto distance = i + 1;
                auto& pipe = getPipe(route[i]);
                if (pipe.getDistance() != -1 && pipe.getDistance() > distance) {
                    pipe.setDistance(distance);
                } else if (pipe.getDistance() == -1) {
                    pipe.setDistance(distance);
                }
            }
        }

        auto longestDistance = 0;
        for (const auto& row : m_pipes) {
            for (const auto& pipe : row) {
                if (pipe.getDistance() > longestDistance) {
                    longestDistance = pipe.getDistance();
                }
            }
        }

        std::cout << longestDistance << "\n";


        auto enclosedByLoop = 0;
        auto& route = routes[0];
        for (const auto& row : m_pipes) {
            for (const auto& pipe : row) {
                auto inRoute = std::any_of(route.cbegin(), route.cend(), [pipe](const Id& id) { return id == pipe.getId(); });
                if (!inRoute) {
                    const auto neighbours = pipe.getNeighbours();
                    auto isEnclosed = std::all_of(neighbours.cbegin(), neighbours.cend(), [this, route](const Id& id) {
                        if (isValidId(id)) {
                            auto& pipe = getPipe(id);
                            return std::any_of(route.cbegin(), route.cend(), [pipe](const Id& id) { return id == pipe.getId(); });
                        }
                        else {
                            return true;
                        }
                        });
                    if (isEnclosed) {
                        enclosedByLoop++;
                    }
                }
            }
        }
        std::cout << enclosedByLoop << "\n";
    }

private:
    bool isValidId(const Id& id) {
        return id.row >= 0 && id.row < m_pipes.size() && id.column >= 0 && id.column < m_pipes[id.row].size();
    }

    Pipe& getPipe(const Id& id) {
        return m_pipes[id.column][id.row];
    }

    std::optional< Pipe > getNextPipe(const Pipe& pipe, Direction& direction) {
        const auto newDirection = pipe.getNewDirection(direction);
        const auto nextId = pipe.getNextPipe(newDirection);
        if (isValidId(nextId)) {
            const auto& nextPossiblePipe = getPipe(nextId);
            if (pipe.canMoveToPipe(newDirection, nextPossiblePipe.getType())) {
                direction = newDirection;
                return nextPossiblePipe;
            }
        }
        return {};
    }

    std::vector< std::vector< Pipe > > m_pipes;
    Id m_startPipe = { -1, -1 };
};

class SecondTaskSolver : public TaskSolver
{
public:
    SecondTaskSolver(const std::string_view fileName)
        : TaskSolver{ fileName }
    {
    }

    void parseLine(std::string_view line) override
    {
    }
};

void solveFirstTask(const std::string_view file)
{
    FirstTaskSolver f{ file };
    f.solveTask();
    f.solveMap();
}

void solveSecondTask(const std::string_view file)
{
    SecondTaskSolver f{ file };
    f.solveTask();
}

int main()
{
    solveFirstTask("sample.txt");
    solveFirstTask("complete.txt");
    //solveSecondTask("sample.txt");
    //solveSecondTask("complete.txt");
}
