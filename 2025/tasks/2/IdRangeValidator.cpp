#include "IdRangeValidator.h"

#include <cmath>
#include <iostream>
#include <ranges>

namespace {
    std::vector<uint8_t> splitIntoDigits(size_t number) {
        std::vector<uint8_t> digits;
        while (number > 0) {
            digits.push_back(number % 10);
            number /= 10;
        }
        return digits;
    }

    bool areHalfsEqual(std::ranges::input_range auto&& firstHalf, std::ranges::input_range auto&& secondHalf) {
        if (std::ranges::distance(firstHalf) != secondHalf.size()) {
            return false;
        }
        auto firstIt = std::ranges::begin(firstHalf);
        auto secondIt = secondHalf.begin();
        for (; firstIt != std::ranges::end(firstHalf); ++firstIt, ++secondIt) {
            if (*firstIt != *secondIt) {
                return false;
            }
        }
        return true;
    }

    bool hasAnyRepetition(std::ranges::input_range auto&& digits) {
        for (auto windowSize = 1; windowSize <= digits.size() / 2; ++windowSize) {
            auto foundRepetition = true;
            for (auto i = 0; i <= (digits.size() - windowSize); i += windowSize) {
                for (auto k = 0; k < windowSize; ++k) {
                    if (digits[k] != digits[i + k]) {
                        foundRepetition = false;
                        break;
                    }
                }

                if (!foundRepetition) {
                    break;
                }
            }

            if (foundRepetition && digits.size() % windowSize == 0) {
                return true;
            }
        }
        return false;
    }
}

IdRangeValidator::IdRangeValidator(const size_t from, const size_t to) : fromDigits(splitIntoDigits(from)), toDigits(splitIntoDigits(to))
{
    for (auto i = from; i <= to; ++i) {
        auto digits = splitIntoDigits(i);
        if (hasAnyRepetition(digits | std::ranges::views::reverse)) {
            invalidIdSum += i;
        }
    }
}

size_t IdRangeValidator::getInvalidIdSum() const
{
    return invalidIdSum;
}
