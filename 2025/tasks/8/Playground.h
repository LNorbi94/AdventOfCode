/* #pragma once

#include "Circuit.h"
#include "JunctionBox.h"

#include <string>
#include <vector>
#include <memory>
#include <set>
#include <utility>
#include <map>

class Playground
{
public:
    explicit Playground(const std::vector<std::string> &lines);

    void FindClosestJunctionBoxes(size_t count);

    size_t MultiplyCircuitCount(size_t number) const;

private:
    std::vector<JunctionBox> allJunctionBoxes;
    std::map<size_t, Circuit *> junctionBoxToCircuit;
    std::map<size_t, std::unique_ptr<Circuit>> circuits;
    std::set<std::pair<size_t, size_t>> connectedPairs;
    size_t nextCircuitId = 0;

    size_t getNextCircuitId();
    Circuit *getOrCreateCircuit(size_t circuitId);
    Circuit *getCircuitForJunctionBox(size_t index);
};
 */