/* #include "Playground.h"

#include <algorithm>
#include <limits>
#include <ranges>
#include <map>
#include <memory>
#include <iostream>

Playground::Playground(const std::vector<std::string> &lines)
{
    // Create a JunctionBox for each line
    for (const auto &line : lines)
    {
        allJunctionBoxes.emplace_back(line);
    }
}

void Playground::FindClosestJunctionBoxes(size_t count)
{
    for (size_t i = 0; i < count; ++i)
    {
        double minDistance = std::numeric_limits<double>::max();
        size_t box1Index = 0;
        size_t box2Index = 0;
        bool foundPair = false;

        // Find the closest pair that hasn't been connected yet
        for (size_t j = 0; j < allJunctionBoxes.size(); ++j)
        {
            for (size_t k = j + 1; k < allJunctionBoxes.size(); ++k)
            {
                // Check if this pair has already been connected
                std::pair<size_t, size_t> pair = (j < k) ? std::make_pair(j, k) : std::make_pair(k, j);
                if (connectedPairs.find(pair) != connectedPairs.end())
                {
                    continue; // Skip already connected pairs
                }

                double distance = allJunctionBoxes[j].getDistanceFrom(allJunctionBoxes[k]);
                if (distance < minDistance)
                {
                    minDistance = distance;
                    box1Index = j;
                    box2Index = k;
                    foundPair = true;
                }
            }
        }

        if (!foundPair)
        {
            // No more pairs to connect
            break;
        }

        // Store the connected pair
        std::pair<size_t, size_t> connectedPair = (box1Index < box2Index)
                                                      ? std::make_pair(box1Index, box2Index)
                                                      : std::make_pair(box2Index, box1Index);
        connectedPairs.insert(connectedPair);

        // Connect them to a circuit
        Circuit *box1Circuit = getCircuitForJunctionBox(box1Index);
        Circuit *box2Circuit = getCircuitForJunctionBox(box2Index);

        if (box1Circuit != nullptr && box2Circuit != nullptr)
        {
            // Both are in circuits - merge box2's circuit into box1's circuit
            if (box1Circuit->getId() != box2Circuit->getId())
            {
                // Update all junction boxes in box2's circuit to point to box1's circuit
                for (auto &[index, circuit] : junctionBoxToCircuit)
                {
                    if (circuit == box2Circuit)
                    {
                        circuit = box1Circuit;
                    }
                }
                // Remove box2's circuit from the circuits map
                circuits.erase(box2Circuit->getId());
            }
        }
        else if (box1Circuit != nullptr)
        {
            // Box1 is already in a circuit, add box2 to that circuit
            junctionBoxToCircuit[box2Index] = box1Circuit;
        }
        else if (box2Circuit != nullptr)
        {
            // Box2 is already in a circuit, add box1 to that circuit
            junctionBoxToCircuit[box1Index] = box2Circuit;
        }
        else
        {
            // Neither is in a circuit, create a new one
            size_t newCircuitId = getNextCircuitId();
            auto newCircuit = std::make_unique<Circuit>(newCircuitId);
            Circuit *circuitPtr = newCircuit.get();
            circuits[newCircuitId] = std::move(newCircuit);
            junctionBoxToCircuit[box1Index] = circuitPtr;
            junctionBoxToCircuit[box2Index] = circuitPtr;
        }
    }
}

size_t Playground::MultiplyCircuitCount(size_t number) const
{
    std::map<size_t, size_t> circuitCounts;
    for (const auto &[index, circuit] : junctionBoxToCircuit)
    {
        if (circuit != nullptr)
        {
            circuitCounts[circuit->getId()]++;
        }
    }
    size_t result = 1;
    size_t count = 0;
    std::vector<size_t> largestCircuits;
    for (const auto &[id, cnt] : circuitCounts)
    {
        if (largestCircuits.size() < number) {
            largestCircuits.push_back(cnt);
            continue;
        }
        auto smallestIt = std::min_element(largestCircuits.begin(), largestCircuits.end());
        if (*smallestIt < cnt) {
            largestCircuits.push_back(cnt);
             smallestIt = std::min_element(largestCircuits.begin(), largestCircuits.end());
               largestCircuits.erase(smallestIt);
        }
    }
    for (const auto& largestCurcuit : largestCircuits) {
        result *= largestCurcuit;
        std::cout << largestCurcuit << "\n";
    }
    return result;
}

size_t Playground::getNextCircuitId()
{
    return nextCircuitId++;
}

Circuit *Playground::getOrCreateCircuit(size_t circuitId)
{
    auto it = std::find_if(junctionBoxToCircuit.begin(), junctionBoxToCircuit.end(),
                           [circuitId](const auto &pair)
                           {
                               return pair.second != nullptr && pair.second->getId() == circuitId;
                           });
    if (it != junctionBoxToCircuit.end())
    {
        return it->second;
    }
    return nullptr;
}

Circuit *Playground::getCircuitForJunctionBox(size_t index)
{
    auto it = junctionBoxToCircuit.find(index);
    if (it != junctionBoxToCircuit.end())
    {
        return it->second;
    }
    return nullptr;
}
 */