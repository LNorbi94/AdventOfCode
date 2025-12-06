#include "UnlimitedBatteryBank.h"

#include <format>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <ranges>

UnlimitedBatteryBank::UnlimitedBatteryBank(const std::string &bank)
{
    for (const auto& digit : bank)
    {
        addToBank(digit);
    }
}

size_t UnlimitedBatteryBank::getLargestJolt() const
{
    std::stringstream ss;
    for (const auto &digit : bank)
    {
        ss << digit;
    }
    return std::stoull(ss.str());
}

void UnlimitedBatteryBank::addToBank(char digit)
{
    std::cout << "Adding digit " << digit << " to bank\n";
    bank.push_back(digit);
    if (bank.size() > bankLimit)
    {
        for (auto it = bank.begin(); it != bank.end(); ++it)
        {
            auto nextIt = std::next(it);
            if (nextIt != bank.end() && *it < *nextIt)
            {
                std::cout << "Removing digit " << *it << " from bank\n";
                bank.erase(it);
                return;
            }
        }
        std::cout << "Removing digit just added to bank\n";
        bank.pop_back();
    }
}
