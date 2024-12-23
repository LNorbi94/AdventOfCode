#pragma once

#include <string>

class Card2
{
public:
    enum class Type {
        FiveOfAKind,
        FourOfAKind,
        FullHouse,
        ThreeOfAKind,
        TwoPair,
        OnePair,
        HighCard
    };

    Card2(std::string cardNumbers, int bid);

    int getPower() const;
    int getBid() const;
    const std::string& getCardNumbers() const;

    bool operator<(const Card2& other) const;

private:
    void determineType();
    int compareNumbers(char numberOne, char numberTwo) const;

    std::string m_numbers;
    Type m_type = Type::HighCard;
    int m_bid = 0;
};