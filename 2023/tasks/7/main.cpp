
#include "TaskSolver.h"
#include "StringManipulation.h"

#include <regex>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

#include "source/Card.h"
#include "source/Card2.h"

class FirstTaskSolver : public TaskSolver
{
public:
    FirstTaskSolver( const std::string_view fileName )
        : TaskSolver{ fileName }
    {
    }

    void parseLine(std::string_view line) override
    {
        std::stringstream ss{ line.data() };
        std::string cardNumber;
        ss >> cardNumber;
        int bid;
        ss >> bid;

        m_cards.insert(Card{ cardNumber, bid });
    }

    void getSolution() const
    {
        int rank = 1;
        int64_t solution = 0;
        for (const auto& card : m_cards) {
            solution += (card.getBid() * rank);
            ++rank;
        }
        std::cout << solution << "\n";
    }

private:
    std::set< Card > m_cards;
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
        std::stringstream ss{ line.data() };
        std::string cardNumber;
        ss >> cardNumber;
        int bid;
        ss >> bid;

        m_cards.insert(Card2{ cardNumber, bid });
    }

    void getSolution() const
    {
        int rank = 1;
        int64_t solution = 0;
        for (const auto& card : m_cards) {
            solution += (card.getBid() * rank);
            ++rank;
        }
        std::cout << solution << "\n";
    }

private:
    std::set< Card2 > m_cards;
};

void solveFirstTask( const std::string_view file )
{
    FirstTaskSolver f{ file };
    f.solveTask();
    f.getSolution();
}

void solveSecondTask( const std::string_view file )
{
    SecondTaskSolver f{ file };
    f.solveTask();
    f.getSolution();
}

int main()
{
    solveFirstTask("sample.txt");
    solveFirstTask( "complete.txt" );
    solveSecondTask( "sample.txt" );
    solveSecondTask( "complete.txt" );
}
