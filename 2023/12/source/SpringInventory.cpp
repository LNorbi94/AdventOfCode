#include "SpringInventory.h"

#include "SpringInventoryItem.h"

#include <deque>
#include <set>
#include <sstream>
#include <iostream>

#include <ranges>

SpringInventory::SpringInventory(std::string_view input)
{
    /*for (const auto& item : input) {
        if (item == '?') {
            m_items.emplace_back(Item::Unknown);
        }
        else if (item == '#') {
            m_items.emplace_back(Item::Damaged);
        }
        else if (item == '.') {
            m_items.emplace_back(Item::Operative);
        }
    }*/
}

std::string ItemToString(Item item) {
    switch (item) {
    case Item::Unknown: {
        return "?";
    }
    case Item::Operative:
        return ".";
    case Item::Damaged:
        return "#";
    }
    return "";
}

struct Spring {
    Item currentItem;
    size_t currentItemIdx = 0;
    size_t state = 0;

    auto operator<=>(const Spring& other) const = default;
};

bool HasSpring(std::vector<Spring>& springs, Spring spring) {
    auto springInSprings = std::ranges::find(springs, spring);
    return springInSprings != springs.cend();
}

int64_t SpringInventory::findAllVariants(const std::string_view cfg, std::deque<size_t> numbers)
{
    if (cfg == "") {
        return numbers.empty() ? 1 : 0;
    }
    if (numbers.empty()) {
        return cfg.contains('#') ? 0 : 1;
    }

    auto key = std::make_pair(cfg, numbers);
    if (m_cache.contains(key)) {
        return m_cache[key];
    }

    int64_t result = 0;

    if (std::string_view{ ".?" }.contains(cfg[0])) {
        result += findAllVariants(cfg.substr(1), numbers);
    }

    if (std::string_view{ "#?" }.contains(cfg[0])) {
        const auto nextBlockSize = numbers[0];
        auto enoughCharLeft = nextBlockSize <= cfg.size();
        auto noOperational = enoughCharLeft && !cfg.substr(0, nextBlockSize).contains('.');
        auto something = enoughCharLeft && (nextBlockSize == cfg.size() || cfg[nextBlockSize] != '#');
        if ( noOperational && something) {
            auto numbersCopy = numbers;
            numbersCopy.pop_front();
            if (cfg.size() == nextBlockSize) {
                result += findAllVariants("", numbersCopy);
            }
            else {

                result += findAllVariants(cfg.substr(nextBlockSize + 1), numbersCopy);
            }
        }
    }

    m_cache[key] = result;
    return result;
}
