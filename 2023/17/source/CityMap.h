#pragma once

#include "CityBlock.h"

#include <string_view>
#include <optional>
#include <vector>

class CityMap
{
public:
    void addCityBlocks(std::string_view line);

    int getMinimalHeatLoss();
    int getMinimalHeatLossWithUltraCrucible();

private:

    bool isValidId(const Id& id) const;
    CityBlock& getCityBlock(const Id& id);

    std::vector< std::vector< CityBlock > > m_cityBlocks;
};
