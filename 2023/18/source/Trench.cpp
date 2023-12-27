#include "Trench.h"

#include <array>
#include <sstream>
#include <queue>

#include <iostream>
#include <fstream>

Trench::Trench()
{
    m_start = std::make_shared< TrenchNode >(Id{ }, "");
}

void Trench::dig(std::string_view line)
{
    std::stringstream input{ line.data() };
    std::string extractedInput;
    std::getline(input, extractedInput, ' ');
    const auto direction = stringToDirection(extractedInput);

    std::getline(input, extractedInput, ' ');
    const auto steps = std::stoi(extractedInput);

    std::getline(input, extractedInput, ' ');
    const auto rgbCode = extractedInput.substr(1, extractedInput.size() - 2);

    if (m_lastNode == nullptr) {
        m_lastNode = m_start;
    }
    for (auto i = 0; i < steps; ++i) {
        auto id = m_lastNode->getNeighbour(direction);
        m_lastNode->addNeighbour(id);
        m_lastNode = std::make_shared< TrenchNode >(id, rgbCode);
        m_trench.insert(m_lastNode);

        if (id.column > m_rightCorner.column) {
            m_rightCorner.column = id.column;
        }
        if (id.row > m_rightCorner.row) {
            m_rightCorner.row = id.row;
        }
        if (id.column < m_leftCorner.column) {
            m_leftCorner.column = id.column;
        }
        if (id.row < m_leftCorner.row) {
            m_leftCorner.row = id.row;
        }
    }
}

void Trench::alternativeDig(std::string_view line)
{
    std::stringstream input{ line.data() };
    std::string extractedInput;
    std::getline(input, extractedInput, ' ');
    auto direction = stringToDirection(extractedInput);

    std::getline(input, extractedInput, ' ');
    auto steps = std::stoi(extractedInput);

    std::getline(input, extractedInput, ' ');
    const auto rgbCode = extractedInput.substr(2, extractedInput.size() - 3);

    std::stringstream ss;
    ss << std::hex << rgbCode.substr(0, 5);
    ss >> steps;

    switch (rgbCode[rgbCode.size() - 1]) {
        case '0':
            direction = Direction::Right;
            break;
        case '1':
            direction = Direction::Bottom;
            break;
        case '2':
            direction = Direction::Left;
            break;
        case '3':
            direction = Direction::Top;
            break;
    }

    if (m_lastNode == nullptr) {
        m_lastNode = m_start;
    }
    for (auto i = 0; i < steps; ++i) {
        auto id = m_lastNode->getNeighbour(direction);
        m_lastNode->addNeighbour(id);
        m_lastNode = std::make_shared< TrenchNode >(id, rgbCode);
        m_trench.insert(m_lastNode);

        if (id.column > m_rightCorner.column) {
            m_rightCorner.column = id.column;
        }
        if (id.row > m_rightCorner.row) {
            m_rightCorner.row = id.row;
        }
        if (id.column < m_leftCorner.column) {
            m_leftCorner.column = id.column;
        }
        if (id.row < m_leftCorner.row) {
            m_leftCorner.row = id.row;
        }
    }
}

int Trench::getPossibleLavaVolume()
{
    writeTrenchToFile("trench.txt");
    std::set< Id > examinedIds;
    for (const auto& trenchNode : m_trench) {
        for (const auto& neighbour : trenchNode->getNonTrenchNeighbours()) {
            if (countTrenchNeighbours(neighbour) >= 2 && !examinedIds.contains(neighbour)) {
                if (floodFill(neighbour, examinedIds) == 1) {
                    break;
                }
                examinedIds.insert(neighbour);
            }
        }
    }
    writeTrenchToFile("trench2.txt");
    return m_trench.size() + m_insideTrench.size();
}

int Trench::floodFill(Id id, std::set< Id >& examinedIds)
{
    auto absoluteRow = m_leftCorner.row + id.row;
    auto absoluteColumn = m_leftCorner.column - id.column;
    int volume = 0;
    std::queue< Id > q;
    q.push(id);

    std::set< std::shared_ptr<TrenchNode> > insideTrench;
    insideTrench.insert(std::make_shared<TrenchNode>(id, ""));
    while (!q.empty()) {
        auto node = q.front();
        q.pop();

        examinedIds.insert(node);

        if (isValidId(node)) {
            for (const auto& neighbour : getNonTrenchNeighbours(node, insideTrench)) {
                insideTrench.insert(std::make_shared<TrenchNode>(neighbour, ""));
                q.push(neighbour);
            }
        } else {
            return -1;
        }
    }

    for (const auto& id : insideTrench) {
        auto containsTrench = std::count_if(m_insideTrench.cbegin(), m_insideTrench.cend(), [id](const auto& currentNode) { return currentNode->getId() == id->getId(); }) > 0;
        containsTrench = containsTrench || std::count_if(m_trench.cbegin(), m_trench.cend(), [id](const auto& currentNode) { return currentNode->getId() == id->getId(); }) > 0;
        if (!containsTrench) {
            const auto debugId = id->getId();
            m_insideTrench.insert(id);
        }
    }

    return 1;
}

int Trench::countTrenchNeighbours(Id id)
{
    const std::array< const Id, 4> possibleNeighbours{
        Id{ id.column, id.row - 1 },
        Id{ id.column, id.row + 1 },
        Id{ id.column - 1, id.row },
        Id{ id.column + 1, id.row }
    };
    auto numberOfTrench = 0;
    for (const auto& neighbour : possibleNeighbours) {
        auto containsNeighbour = std::count_if(m_trench.cbegin(), m_trench.cend(), [neighbour](const auto& node) { return node->getId() == neighbour; }) > 0;
        if (containsNeighbour) {
            ++numberOfTrench;
        }
    }
    return numberOfTrench;
}

int Trench::countTrenchNeighbours(Id id, std::set< std::shared_ptr< TrenchNode > >& insideTrench)
{
    const std::array< const Id, 4> possibleNeighbours{
        Id{ id.column, id.row - 1 },
        Id{ id.column, id.row + 1 },
        Id{ id.column - 1, id.row },
        Id{ id.column + 1, id.row }
    };
    auto numberOfTrench = 0;
    for (const auto& neighbour : possibleNeighbours) {
        auto containsNeighbour = std::count_if(m_trench.cbegin(), m_trench.cend(), [neighbour](const auto& node) { return node->getId() == neighbour; }) > 0;
        containsNeighbour = containsNeighbour || std::count_if(insideTrench.cbegin(), insideTrench.cend(), [neighbour](const auto& node) { return node->getId() == neighbour; }) > 0;
        if (containsNeighbour) {
            ++numberOfTrench;
        }
    }
    return numberOfTrench;
}

std::vector<Id> Trench::getNonTrenchNeighbours(Id id, std::set< std::shared_ptr< TrenchNode > >& insideTrench)
{
    std::vector<Id> nonTrenchNeighbours;
    const std::array< const Id, 4> possibleNeighbours{
        Id{ id.column, id.row - 1 },
        Id{ id.column, id.row + 1 },
        Id{ id.column - 1, id.row },
        Id{ id.column + 1, id.row }
    };

    for (const auto& neighbour : possibleNeighbours) {
        auto containsNeighbour = std::count_if(m_trench.cbegin(), m_trench.cend(), [neighbour](const auto& node) { return node->getId() == neighbour; }) > 0;
        containsNeighbour = containsNeighbour || std::count_if(insideTrench.cbegin(), insideTrench.cend(), [neighbour](const auto& node) { return node->getId() == neighbour; }) > 0;
        if (!containsNeighbour) {
            nonTrenchNeighbours.push_back(neighbour);
        }
    }

    return nonTrenchNeighbours;
}

bool Trench::isValidId(Id id) const
{
    return id.column >= m_leftCorner.column && id.column <= m_rightCorner.column && id.row >= m_leftCorner.row && id.row <= m_rightCorner.row;
}

void Trench::writeTrenchToFile(std::string_view fileName)
{
    std::ofstream f(fileName.data());
    for (auto i = m_leftCorner.column; i < m_rightCorner.column + 1; ++i) {
        for (auto j = m_leftCorner.row; j < m_rightCorner.row + 1; ++j) {
            auto containsNeighbour = std::count_if(m_trench.cbegin(), m_trench.cend(), [neighbour{ Id{ i, j } }](const auto& node) { return node->getId() == neighbour; }) > 0;
            containsNeighbour = containsNeighbour || std::count_if(m_insideTrench.cbegin(), m_insideTrench.cend(), [neighbour{ Id{ i, j } }](const auto& node) { return node->getId() == neighbour; }) > 0;
            if (containsNeighbour) {
                f << "#";
            }
            else {
                f << ".";
            }
        }
        f << "\n";
    }
}
