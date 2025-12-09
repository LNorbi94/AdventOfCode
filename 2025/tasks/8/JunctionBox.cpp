#include "JunctionBox.h"

#include "common/StringManipulation.h"

#include <cmath>
#include <stdexcept>
#include <iostream>

JunctionBox::JunctionBox(const size_t id, const std::string &coordinateString) : id{id}
{
    auto parts = common::splitToMultipleString(coordinateString, ',');
    if (parts.size() != 3)
    {
        throw std::invalid_argument("JunctionBox requires exactly 3 coordinates");
    }

    x = std::stod(parts[0]);
    y = std::stod(parts[1]);
    z = std::stod(parts[2]);
    circuitId = std::nullopt;
}

double JunctionBox::getDistanceFrom(const JunctionBox &other) const
{
    double dx = x - other.x;
    double dy = y - other.y;
    double dz = z - other.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

void JunctionBox::print() const
{
    std::cout << x << ", " << y << ", " << z << "\n";
}

size_t JunctionBox::getId() const
{
    return id;
}

double JunctionBox::GetX() const
{
    return x;
}

bool JunctionBox::operator<(const JunctionBox &other) const
{
    return getDistanceFrom(other);
}

void JunctionBox::connectToCircuit(size_t id)
{
    circuitId = id;
}

std::optional<size_t> JunctionBox::getCircuitId() const
{
    return circuitId;
}
