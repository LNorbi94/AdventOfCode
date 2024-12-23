#include "Card.h"

#include <set>
#include <map>

Card::Card(std::string cardNumbers, const int bid)
    : m_numbers{ std::move(cardNumbers) }
    , m_bid{ bid }
{
    determineType();
}

int Card::getPower() const
{
    return 6 - static_cast<int>(m_type);
}

int Card::getBid() const
{
    return m_bid;
}

const std::string& Card::getCardNumbers() const
{
    return m_numbers;
}

bool Card::operator<(const Card& other) const
{
    if (getPower() == other.getPower()) {
        for (auto i = 0; i < m_numbers.size(); ++i) {
            auto compareResult = compareNumbers(m_numbers[i], other.getCardNumbers()[i]);
            if (compareResult != 0) {
                return compareResult == -1 ? true : false;
            }
        }
        return false;
    }
    return getPower() < other.getPower();
}

void Card::determineType()
{
    auto highestSeries = 0;
    char highestSeriesNumber;
    auto secondHighestSeries = 0;
    std::multiset< char > numbers;
    for (const auto& number : m_numbers) {
        numbers.insert(number);
    }
    const auto cstr = m_numbers.c_str();
    for (const auto& number : numbers) {
        auto numberCount = numbers.count(number);
        if (numberCount > highestSeries) {
            if (highestSeries > secondHighestSeries) {
                secondHighestSeries = highestSeries;
            }
            highestSeries = numberCount;
            highestSeriesNumber = number;
        } else if (numberCount > secondHighestSeries && number != highestSeriesNumber) {
            secondHighestSeries = numberCount;
        }
    }

    if (highestSeries == 5) {
        m_type = Type::FiveOfAKind;
    }
    else if (highestSeries == 4) {
        m_type = Type::FourOfAKind;
    }
    else if (highestSeries == 3 && secondHighestSeries == 2) {
        m_type = Type::FullHouse;
    }
    else if (highestSeries == 3) {
        m_type = Type::ThreeOfAKind;
    }
    else if (highestSeries == 2 && secondHighestSeries == 2) {
        m_type = Type::TwoPair;
    }
    else if (highestSeries == 2) {
        m_type = Type::OnePair;
    }
}

int Card::compareNumbers(const char numberOne, const char numberTwo) const
{
    if (numberOne == numberTwo) {
        return 0;
    }

    std::map<char, int> valueMap{
        {'A', 13},
        {'K', 12},
        {'Q', 11},
        {'J', 10},
        {'T', 9},
        {'9', 8},
        {'8', 7},
        {'7', 6},
        {'6', 5},
        {'5', 4},
        {'4', 3},
        {'3', 2},
        {'2', 1},
    };
    if (valueMap[numberOne] < valueMap[numberTwo]) {
        return -1;
    }
    return 1;
}
