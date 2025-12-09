#pragma once

#include "JunctionBox.h"

#include <vector>
#include <memory>
#include <set>

class Circuit
{
public:
    explicit Circuit();

    void AddJunctionBox(JunctionBox &&junctionBox);
    struct JunctionBoxPair
    {
        size_t firstIdx = 0;
        double firstXCoord = 0.0;
        size_t secondIdx = 0;
        double secondXCoord = 0.0;
        double distance = 0.0;
    };
    std::optional<JunctionBoxPair> GetClosestJunctionBox(const Circuit &otherCircuit, const std::set<std::pair<size_t, size_t>> &connectedPairs) const;

    void MergeCircuit(Circuit *other);
    void MarkAsMerged();
    bool IsMerged() const;

    const std::set<JunctionBox> &GetJunctionBoxes() const;
    std::set<JunctionBox> &&GetMoveableJunctionBoxes();

private:
    std::set<JunctionBox> junctionBoxes;
    bool merged = false;
};
