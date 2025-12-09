#include "Circuit.h"

#include <algorithm>
#include <limits>

Circuit::Circuit()
{
}

void Circuit::AddJunctionBox(JunctionBox &&junctionBox)
{
    junctionBoxes.insert(junctionBox);
}

std::optional<Circuit::JunctionBoxPair> Circuit::GetClosestJunctionBox(
    const Circuit &otherCircuit,
    const std::set<std::pair<size_t, size_t>> &connectedPairs) const
{
    if (junctionBoxes.empty() || otherCircuit.junctionBoxes.empty())
    {
        return std::nullopt;
    }

    std::optional<JunctionBoxPair> minPair;

    for (const auto &boxA : junctionBoxes)
    {
        const size_t boxAId = boxA.getId();

        for (const auto &boxB : otherCircuit.junctionBoxes)
        {
            const size_t boxBId = boxB.getId();
            const auto pairKey = (boxAId < boxBId) ? std::make_pair(boxAId, boxBId)
                                                   : std::make_pair(boxBId, boxAId);

            // Skip pairs that are already connected elsewhere
            if (connectedPairs.find(pairKey) != connectedPairs.end())
            {
                continue;
            }

            const double distance = boxA.getDistanceFrom(boxB);
            if (!minPair.has_value() || distance < minPair->distance)
            {
                const auto coords = (boxAId < boxBId) ? std::make_pair(boxA.GetX(), boxB.GetX())
                    : std::make_pair(boxB.GetX(), boxA.GetX());
                minPair = {pairKey.first, coords.first, pairKey.second, coords.second, distance};
            }
        }
    }

    return minPair;
}

void Circuit::MergeCircuit(Circuit *other)
{
    junctionBoxes.merge(std::move(other->GetMoveableJunctionBoxes()));
    other->MarkAsMerged();
}

void Circuit::MarkAsMerged()
{
    merged = true;
}

bool Circuit::IsMerged() const
{
    return merged;
}

const std::set<JunctionBox> &Circuit::GetJunctionBoxes() const
{
    return junctionBoxes;
}

std::set<JunctionBox> &&Circuit::GetMoveableJunctionBoxes()
{
    return std::move(junctionBoxes);
}
