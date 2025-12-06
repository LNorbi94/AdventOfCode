#pragma once

#include <cstdint>
#include <string>

class BatteryBank
{
public:
    BatteryBank(const std::string &bank);

    size_t getLargestJolt() const;

private:
    size_t largestJolt = 0;
};
