#include "ValleyMap.h"
#include "ValleyMap.h"
#include "ValleyMap.h"
#include <iostream>

void ValleyMap::addRow(std::string row)
{
    fields.push_back(std::move(row));
}

size_t ValleyMap::differentFields(LineDirection direction, size_t idx, size_t distance) const
{
    if (distance >= idx || idx + distance >= size(direction)) {
        return 0;
    }
    switch (direction)
    {
    case LineDirection::Vertical:
        return columnDifferences(idx - distance - 1, idx + distance);
    case LineDirection::Horizontal:
        return rowDifferences(idx - distance - 1, idx + distance);
    default:
        break;
    }
}

size_t ValleyMap::columnDifferences(size_t idx, size_t otherIdx) const
{
    size_t diff = 0;
    for (auto i = 0; i < fields.size(); ++i) {
        if (fields[i][idx] != fields[i][otherIdx]) {
            ++diff;
        }
    }
    return diff;
}

size_t ValleyMap::rowDifferences(size_t idx, size_t otherIdx) const
{
    size_t diff = 0;
    for (auto i = 0; i < fields[idx].size(); ++i) {
        if (fields[idx][i] != fields[otherIdx][i]) {
            ++diff;
        }
    }
    return diff;
}

size_t ValleyMap::size(LineDirection direction) const
{
    if (fields.empty())
    {
        return 0;
    }

    switch (direction)
    {
    case LineDirection::Vertical:
        return fields[0].size();
    case LineDirection::Horizontal:
        return fields.size();
    default:
        break;
    }
}
