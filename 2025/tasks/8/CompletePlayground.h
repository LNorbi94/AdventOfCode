#pragma once

#include "Circuit.h"
#include "JunctionBox.h"

#include <string>
#include <vector>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <map>

class CompletePlayground
{
public:
    explicit CompletePlayground(const std::vector<std::string> &lines);

    void FindClosestJunctionBoxes(size_t count);
    void MergeUntilOneCircuit();

    size_t MultiplyCircuitCount(size_t number);

private:
    std::list<std::unique_ptr<Circuit>> circuits;
    std::set<std::pair<size_t, size_t>> connectedPairs;
    std::pair<size_t, size_t> lastPair;
    std::pair<double, double> lastXPair;
};
