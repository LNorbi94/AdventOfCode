#pragma once

#include <array>
#include <list>
#include <string>

struct Lens
{
    std::string label;
    int64_t focalLength = 0;
};

class Box
{
public:
    void setBoxNumber(int64_t boxNumber);

    void removeValue(std::string_view label);
    void addValue(std::string_view label, int64_t focalLength);

    int64_t getFocusingPower() const;

private:
    int64_t m_boxNumber = 0;
    std::list< Lens > m_lenses;
};

class HashMap
{
public:
    HashMap();

    void removeValue(std::string_view label);
    void addValue(std::string_view label, int64_t focalLength);

    int64_t calculateFocusingPower() const;

private:
    std::array< Box, 256 > m_boxes{};
};
