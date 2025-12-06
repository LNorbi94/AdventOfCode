#pragma once

#include <cstdint>
#include <vector>

class IdRangeValidator {
public:
    IdRangeValidator(size_t from, size_t to);

    size_t getInvalidIdSum() const;

private:

    std::vector<uint8_t> fromDigits;
    std::vector<uint8_t> toDigits;
    size_t invalidIdSum = 0;
};
