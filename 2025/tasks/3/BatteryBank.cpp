#include "BatteryBank.h"

#include <format>

BatteryBank::BatteryBank(const std::string &bank)
{
    for (auto i = 0; i < bank.size(); ++i)
    {
        for (auto j = i + 1; j < bank.size(); ++j)
        {
            auto jolt = std::stoi(std::format("{}{}", bank[i], bank[j]));
            if (jolt > largestJolt)
            {
                largestJolt = jolt;
            }
        }
    }
}

size_t BatteryBank::getLargestJolt() const
{
    return largestJolt;
}
