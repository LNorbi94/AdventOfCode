#pragma once

#include <cstdint>
#include <string>
#include <list>

class UnlimitedBatteryBank
{
public:
    UnlimitedBatteryBank(const std::string &bank);

    size_t getLargestJolt() const;

private:
    void addToBank(char digit);

    std::list<char> bank;
    size_t bankLimit = 12;
};
