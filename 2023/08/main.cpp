
#include "TaskSolver.h"
#include "StringManipulation.h"

#include <regex>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

class MapNode
{
public:
    MapNode(const std::string_view id, const std::string_view left, const std::string_view right)
        : m_id{ id }
        , m_left{ left }
        , m_right{ right }
    {}

    const std::string& getId() const
    {
        return m_id;
    }

    const std::string& goLeft() const
    {
        return m_left;
    }
    const std::string& goRight() const
    {
        return m_right;
    }

private:
    std::string m_id;
    std::string m_left;
    std::string m_right;
};

class FirstTaskSolver
{
public:
    FirstTaskSolver(const std::string_view fileName)
    {
        std::ifstream stream{ fileName.data() };

        std::string line;
        std::getline(stream, line);
        const auto instructions = line;
        std::getline(stream, line);

        std::map< std::string, MapNode > nodes;
        while (std::getline(stream, line)) {
            const auto parsedNodes = common::extractWords(line);
            nodes.emplace(parsedNodes[0], MapNode{ parsedNodes[0], parsedNodes[1], parsedNodes[2] });
        }

        auto steps = 0;
        auto nextNode = nodes.at("AAA");
        while (nextNode.getId() != "ZZZ") {
            for (auto i = 0; i < instructions.size() && nextNode.getId() != "ZZZ"; ++i) {
                steps++;
                switch (instructions[i]) {
                case 'L':
                    nextNode = nodes.at(nextNode.goLeft());
                    break;
                case 'R':
                    nextNode = nodes.at(nextNode.goRight());
                    break;
                }
            }
        }

        std::cout << steps << "\n";
    }
};

class SecondTaskSolver
{
public:
    SecondTaskSolver(const std::string_view fileName)
    {
        std::ifstream stream{ fileName.data() };

        std::string line;
        std::getline(stream, line);
        const auto instructions = line;
        std::getline(stream, line);

        std::map< std::string, MapNode > nodes;
        while (std::getline(stream, line)) {
            const auto parsedNodes = common::extractWords(line);
            nodes.emplace(parsedNodes[0], MapNode{ parsedNodes[0], parsedNodes[1], parsedNodes[2] });
        }

        auto instruction = 0;
        size_t steps = 0;
        std::vector< MapNode > startingNodes;
        for (const auto& [id, node] : nodes) {
            if (id.ends_with('A')) {
                startingNodes.push_back(node);
            }
        }
        std::vector< int > endReached;
        while (endReached.size() != startingNodes.size()) {
            for (auto& node : startingNodes) {
                if (!node.getId().ends_with('Z')) {
                    switch (instructions[instruction]) {
                    case 'L':
                        node = nodes.at(node.goLeft());
                        break;
                    case 'R':
                        node = nodes.at(node.goRight());
                        break;
                    }
                    if (node.getId().ends_with('Z')) {
                        endReached.push_back(steps + 1);
                    }
                }
            }
            if (instruction + 1 < instructions.size()) {
                ++instruction;
            }
            else {
                instruction = 0;
            }
            ++steps;
        }

        if (endReached.size() == 2) {
            std::cout << getLeastCommonMultiple(endReached[0], endReached[1]) << "\n";
        }
        else if (endReached.size() > 2) {
            auto solution = getLeastCommonMultiple(endReached[0], endReached[1]);
            for (auto i = 2; i < endReached.size(); ++i) {
                solution = getLeastCommonMultiple(endReached[i], solution);
            }
            std::cout << solution << "\n";
        }
    }

    size_t getLeastCommonMultiple(size_t a, size_t b)
    {
        auto gcd = a;
        auto temp = b;
        while (temp != 0) {
            auto c = gcd % temp;
            gcd = temp;
            temp = c;
        }

        return a * b / gcd;
    }

};

void solveFirstTask(const std::string_view file)
{
    FirstTaskSolver f{ file };
}

void solveSecondTask(const std::string_view file)
{
    SecondTaskSolver f{ file };
}

int main()
{
    solveFirstTask("sample.txt");
    solveFirstTask("complete.txt");
    solveSecondTask("sample2.txt");
    solveSecondTask("complete.txt");
}
