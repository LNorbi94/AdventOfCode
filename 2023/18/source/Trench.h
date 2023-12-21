#pragma once

#include "TrenchNode.h"

#include <set>
#include <string_view>
#include <optional>
#include <memory>
#include <vector>

class Trench
{
public:
    Trench();

    void dig(std::string_view line);
    void alternativeDig(std::string_view line);

    int getPossibleLavaVolume();

private:
    int floodFill(Id id, std::set< Id >& examinedIds);

    int countTrenchNeighbours(Id id);
    int countTrenchNeighbours(Id id, std::set< std::shared_ptr< TrenchNode > >& insideTrench);
    std::vector<Id> getNonTrenchNeighbours(Id id, std::set<std::shared_ptr<TrenchNode>>& insideTrench);

    bool isValidId(Id id) const;

    void writeTrenchToFile(std::string_view fileName);

    std::set< std::shared_ptr< TrenchNode > > m_trench;
    std::set< std::shared_ptr< TrenchNode > > m_insideTrench;
    std::shared_ptr< TrenchNode > m_start;
    std::shared_ptr< TrenchNode > m_lastNode;

    Id m_leftCorner;
    Id m_rightCorner;
};
