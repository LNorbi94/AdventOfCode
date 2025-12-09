#pragma once

#include <string>
#include <optional>

class JunctionBox
{
public:
    explicit JunctionBox(size_t id, const std::string &coordinateString);

    double getDistanceFrom(const JunctionBox &other) const;

    void print() const;
    size_t getId() const;

    double GetX() const;

    bool operator<(const JunctionBox &other) const;
    bool operator==(const JunctionBox &other) const = default;

    void connectToCircuit(size_t circuitId);
    std::optional<size_t> getCircuitId() const;

private:
    double x;
    double y;
    double z;
    size_t id = 0;
    std::optional<size_t> circuitId;
};
