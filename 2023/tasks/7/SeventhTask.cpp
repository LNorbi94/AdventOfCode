
#include "common/TaskSolver.h"
#include "common/StringManipulation.h"

#include <functional>
#include <regex>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Card.h"
#include "Card2.h"
#include "SeventhTask.h"
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "7.txt";
}

class SeventhTaskPartOneSolver
{
public:
    SeventhTaskPartOneSolver(const std::string_view fileName)
    {
        FileParser parser{fileName};
        parser.ParseFile(std::bind_front(&SeventhTaskPartOneSolver::parseLine, this));
    }

    void parseLine(std::string_view line)
    {
        std::stringstream ss{line.data()};
        std::string cardNumber;
        ss >> cardNumber;
        int bid;
        ss >> bid;

        m_cards.emplace(cardNumber, bid);
    }

    void getSolution() const
    {
        int rank = 1;
        int64_t solution = 0;
        for (const auto &card : m_cards)
        {
            solution += (card.getBid() * rank);
            ++rank;
        }
        std::cout << solution << "\n";
    }

private:
    std::set<Card> m_cards;
};

class SeventhTaskPartTwoSolver
{
public:
    SeventhTaskPartTwoSolver(const std::string_view fileName)
    {
        FileParser parser{fileName};
        parser.ParseFile(std::bind_front(&SeventhTaskPartTwoSolver::parseLine, this));
    }

    void parseLine(std::string_view line)
    {
        std::stringstream ss{line.data()};
        std::string cardNumber;
        ss >> cardNumber;
        int bid;
        ss >> bid;

        m_cards.emplace(cardNumber, bid);
    }

    void getSolution() const
    {
        int rank = 1;
        int64_t solution = 0;
        for (const auto &card : m_cards)
        {
            solution += (card.getBid() * rank);
            ++rank;
        }
        std::cout << solution << "\n";
    }

private:
    std::set<Card2> m_cards;
};

void SeventhTask::SolveFirstPart()
{
    SeventhTaskPartOneSolver f{inputFileName.string()};
    f.getSolution();
}

void SeventhTask::SolveSecondPart()
{
    SeventhTaskPartTwoSolver f{inputFileName.string()};
    f.getSolution();
}
