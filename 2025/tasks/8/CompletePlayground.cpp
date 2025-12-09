#include "CompletePlayground.h"

#include <algorithm>
#include <limits>
#include <ranges>
#include <map>
#include <memory>
#include <iostream>

CompletePlayground::CompletePlayground(const std::vector<std::string> &lines)
{
    // Create a JunctionBox for each line
    size_t id = 0;
    for (const auto &line : lines)
    {
        JunctionBox box{id++, line};
        circuits.push_back(std::make_unique<Circuit>());
        circuits.back()->AddJunctionBox(std::move(box));
    }
}

void CompletePlayground::FindClosestJunctionBoxes(size_t count)
{
    // Does not work for task 1, because it does not seek pairs _inside_ a circuit
    for (size_t i = 0; i < count - 1; ++i)
    {
        std::optional<Circuit::JunctionBoxPair> closestJunctionBoxPair;
        std::pair<decltype(circuits)::iterator, decltype(circuits)::iterator> circuitPair;

        // Find the closest pair that hasn't been connected yet
        if (circuits.size() == 1) {
            break;
        }
        for (auto circuitIt = circuits.begin(); circuitIt != circuits.end(); ++circuitIt)
        {
            auto otherCircuitIt = circuitIt;
            ++otherCircuitIt;
            for (; otherCircuitIt != circuits.end(); ++otherCircuitIt)
            {
                auto junctionBoxPair = (*circuitIt)->GetClosestJunctionBox(**otherCircuitIt, connectedPairs);
                if (!closestJunctionBoxPair.has_value() || junctionBoxPair.has_value() && junctionBoxPair->distance < closestJunctionBoxPair->distance)
                {
                    closestJunctionBoxPair = junctionBoxPair;
                    circuitPair = std::make_pair(circuitIt, otherCircuitIt);
                }
            }
        }

        // Store the connected pair
        auto &[boxAId, xCoord, boxBId, secondXCoord, _] = *closestJunctionBoxPair;
        lastPair = (boxAId < boxBId) ? std::make_pair(boxAId, boxBId)
                                               : std::make_pair(boxBId, boxAId);
        connectedPairs.insert(lastPair);
        lastXPair = std::make_pair(xCoord, secondXCoord);

        // Connect them to a circuit
        auto [circuitIt, otherCircuitIt] = circuitPair;
        (*circuitIt)->MergeCircuit(otherCircuitIt->get());
    }
}

void CompletePlayground::MergeUntilOneCircuit()
{
    while (true)
    {
        FindClosestJunctionBoxes(2);
        if (circuits.size() == 1)
        {
            break;
        }
        // Remove merged circuits
        circuits.erase(std::remove_if(circuits.begin(), circuits.end(),
                                      [](const std::unique_ptr<Circuit> &circuit) { return circuit->IsMerged(); }),
                       circuits.end());
    }

    std::cout << static_cast<int64_t>(lastXPair.first) * static_cast<int64_t>(lastXPair.second) << std::endl;
}

size_t CompletePlayground::MultiplyCircuitCount(size_t number)
{
    circuits.sort([](const std::unique_ptr<Circuit> &a, const std::unique_ptr<Circuit> &b) {
        return a->GetJunctionBoxes().size() > b->GetJunctionBoxes().size();
        });
    size_t result = 1;
    for (const auto& circuit : circuits | std::views::take(number)) {
        result *= circuit->GetJunctionBoxes().size();
    }
    return result;
}
