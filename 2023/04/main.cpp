
#include "TaskSolver.h"
#include "StringManipulation.h"

#include <regex>
#include <set>
#include <map>

class Card
{
public:
    Card( const int cardNumber )
        : m_cardNumber{ cardNumber }
    {}

    void addWinningNumber( const int number )
    {
        m_winningNumbers.insert( number );
    }

    void addCardNumber( const int number )
    {
        m_cardNumbers.insert( number );
    }

    int getCardNumber() const
    {
        return m_cardNumber;
    }

    int cardScore() const
    {
        int winningNumbers = getWinningNumbers();
        if ( winningNumbers  == 0 ) {
            return 0;
        }
        return static_cast< int >( std::pow( 2, winningNumbers - 1 ) );
    }
    int getWinningNumbers() const
    {
        int winningNumbers = 0;
        for ( const auto& number : m_cardNumbers ) {
            if ( m_winningNumbers.contains( number ) ) {
                ++winningNumbers;
            }
        }
        return winningNumbers;
    }

private:
    std::set< int > m_winningNumbers;
    std::set< int > m_cardNumbers;
    int m_cardNumber = 0;
};

class FirstTaskSolver : public TaskSolver
{
public:
    FirstTaskSolver( const std::string_view fileName )
        : TaskSolver{ fileName }
    {}

    void parseLine( const std::string_view line ) override
    {
        const auto lines = common::splitString( line, '|' );

        const auto winningNumbers = common::extractNumbers< int >( lines[ 0 ] );
        if ( winningNumbers.empty() ) {
            return;
        }
        Card card{ winningNumbers[ 0 ] };
        for ( auto i = 1; i < winningNumbers.size(); ++i ) {
            card.addWinningNumber( winningNumbers[ i ] );
        }

        const auto cardNumbers = common::extractNumbers< int >( lines[ 1 ] );
        for ( const auto& number : cardNumbers ) {
            card.addCardNumber( number );
        }

        m_solution += card.cardScore();
    }
};

class SecondTaskSolver : public TaskSolver
{
public:
    SecondTaskSolver( const std::string_view fileName )
        : TaskSolver{ fileName }
    {}

    void parseLine( const std::string_view line ) override
    {
        const auto lines = common::splitString( line, '|' );

        const auto winningNumbers = common::extractNumbers< int >( lines[ 0 ] );
        if ( winningNumbers.empty() ) {
            return;
        }

        const auto cardNumber = winningNumbers[ 0 ];
        auto copies = 1 + m_extraCopies[ cardNumber ];
        Card card{ cardNumber };
        for ( auto i = 1; i < winningNumbers.size(); ++i ) {
            card.addWinningNumber( winningNumbers[ i ] );
        }

        const auto cardNumbers = common::extractNumbers< int >( lines[ 1 ] );
        for ( const auto& number : cardNumbers ) {
            card.addCardNumber( number );
        }

        auto numberOfWins = card.getWinningNumbers();
        for ( auto i = cardNumber + 1; i < (cardNumber + 1 + numberOfWins); ++i ) {
            m_extraCopies[ i ] += copies;
        }

        m_solution += copies;
    }

private:
    std::map< int, int > m_extraCopies;
};

void solveFirstTask( const std::string_view file )
{
    FirstTaskSolver f{ file };
    f.solveTask();
}

void solveSecondTask( const std::string_view file )
{
    SecondTaskSolver f{ file };
    f.solveTask();
}

int main()
{
    solveFirstTask( "04_sample.txt" );
    solveFirstTask( "04.txt" );
    solveSecondTask( "04_sample.txt" );
    solveSecondTask( "04.txt" );
}
