
#include "common/TaskSolver.h"
#include "common/StringManipulation.h"

#include <functional>
#include <regex>
#include <set>
#include <map>
#include "FourthTask.h"
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "4.txt";
}

class FourthCard
{
public:
    FourthCard(const int cardNumber)
        : m_cardNumber{cardNumber}
    {
    }

    void addWinningNumber(const int number)
    {
        m_winningNumbers.insert(number);
    }

    void addCardNumber(const int number)
    {
        m_cardNumbers.insert(number);
    }

    int getCardNumber() const
    {
        return m_cardNumber;
    }

    int cardScore() const
    {
        int winningNumbers = getWinningNumbers();
        if (winningNumbers == 0)
        {
            return 0;
        }
        return static_cast<int>(std::pow(2, winningNumbers - 1));
    }
    int getWinningNumbers() const
    {
        int winningNumbers = 0;
        for (const auto &number : m_cardNumbers)
        {
            if (m_winningNumbers.contains(number))
            {
                ++winningNumbers;
            }
        }
        return winningNumbers;
    }

private:
    std::set<int> m_winningNumbers;
    std::set<int> m_cardNumbers;
    int m_cardNumber = 0;
};

class FourthTaskPartOneSolver : public TaskSolver
{
public:
    FourthTaskPartOneSolver(const std::string_view fileName)
        : TaskSolver{fileName}
    {
        ParseFile(std::bind_front(&FourthTaskPartOneSolver::parseLine, this));
    }

    void parseLine(const std::string &line)
    {
        const auto lines = common::splitString(line, '|');

        const auto winningNumbers = common::extractNumbers<int>(lines[0]);
        if (winningNumbers.empty())
        {
            return;
        }
        FourthCard card{winningNumbers[0]};
        for (auto i = 1; i < winningNumbers.size(); ++i)
        {
            card.addWinningNumber(winningNumbers[i]);
        }

        const auto cardNumbers = common::extractNumbers<int>(lines[1]);
        for (const auto &number : cardNumbers)
        {
            card.addCardNumber(number);
        }

        m_solution += card.cardScore();
    }
};

class FourthTaskPartTwoSolver : public TaskSolver
{
public:
    FourthTaskPartTwoSolver(const std::string_view fileName)
        : TaskSolver{fileName}
    {
        ParseFile(std::bind_front(&FourthTaskPartTwoSolver::parseLine, this));
    }

    void parseLine(const std::string &line)
    {
        const auto lines = common::splitString(line, '|');

        const auto winningNumbers = common::extractNumbers<int>(lines[0]);
        if (winningNumbers.empty())
        {
            return;
        }

        const auto cardNumber = winningNumbers[0];
        auto copies = 1 + m_extraCopies[cardNumber];
        FourthCard card{cardNumber};
        for (auto i = 1; i < winningNumbers.size(); ++i)
        {
            card.addWinningNumber(winningNumbers[i]);
        }

        const auto cardNumbers = common::extractNumbers<int>(lines[1]);
        for (const auto &number : cardNumbers)
        {
            card.addCardNumber(number);
        }

        auto numberOfWins = card.getWinningNumbers();
        for (auto i = cardNumber + 1; i < (cardNumber + 1 + numberOfWins); ++i)
        {
            m_extraCopies[i] += copies;
        }

        m_solution += copies;
    }

private:
    std::map<int, int> m_extraCopies;
};

void FourthTask::SolveFirstPart()
{
    FourthTaskPartOneSolver f{inputFileName.string()};
    f.solveTask();
}

void FourthTask::SolveSecondPart()
{
    FourthTaskPartTwoSolver f{inputFileName.string()};
    f.solveTask();
}
