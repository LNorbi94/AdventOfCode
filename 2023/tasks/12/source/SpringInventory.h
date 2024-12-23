#pragma once

#include "Item.h"

#include <string_view>
#include <vector>
#include <queue>
#include <map>

class SpringInventory
{
public:
    SpringInventory(std::string_view input);

    int64_t findAllVariants(const std::string_view cfg, std::deque<size_t> numbers);

private:

    std::map<std::pair<std::string_view, std::deque<size_t>>, int64_t> m_cache;
};
