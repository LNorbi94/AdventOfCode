#pragma once

#include <string>

class Card
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

    Card(std::string cardNumbers, int bid);

    int getPower() const;
    int getBid() const;
    const std::string& getCardNumbers() const;

    bool operator<(const Card& other) const;

private:
    void determineType();
    int compareNumbers(char numberOne, char numberTwo) const;

    std::string m_numbers;
    Type m_type = Type::HighCard;
    int m_bid = 0;
};