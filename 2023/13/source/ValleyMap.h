#pragma once

#include <vector>

#include <string>
#include "LineDirection.h"

class ValleyMap
{
public:
    void addRow(std::string row);

    size_t differentFields(LineDirection direction, size_t idx, size_t distance) const;

    size_t columnDifferences(size_t idx, size_t otherIdx) const;

    size_t rowDifferences(size_t idx, size_t otherIdx) const;

    size_t size(LineDirection direction) const;

private:
    std::vector<std::string> fields;
};
