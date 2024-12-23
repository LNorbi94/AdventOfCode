#include "Trench.h"

#include <algorithm>
#include <array>
#include <sstream>
#include <queue>

#include <iostream>
#include <fstream>

#include "ConvexhullCalculator.hpp"

Trench::Trench()
{
    m_start = std::make_shared<TrenchNode>(Id{}, "");
    //m_points.emplace_back(0.0, 0.0);
}

void Trench::dig(std::string_view line)
{
    std::stringstream input{line.data()};
    std::string extractedInput;
    std::getline(input, extractedInput, ' ');
    const auto direction = stringToDirection(extractedInput);

    std::getline(input, extractedInput, ' ');
    const auto steps = std::stoi(extractedInput);

    std::getline(input, extractedInput, ' ');
    const auto rgbCode = extractedInput.substr(1, extractedInput.size() - 2);

    const auto &lastPoint = m_points.empty() ? Point(0.0, 0.0) : m_points.back();
    switch (direction)
    {
    case Direction::Top:
        m_points.emplace_back(lastPoint.GetX(), lastPoint.GetY() - steps);
        break;
    case Direction::Bottom:
        m_points.emplace_back(lastPoint.GetX(), lastPoint.GetY() + steps);
        break;
    case Direction::Left:
        m_points.emplace_back(lastPoint.GetX() - steps, lastPoint.GetY());
        break;
    case Direction::Right:
        m_points.emplace_back(lastPoint.GetX() + steps, lastPoint.GetY());
        break;
    }

    pathLength += steps;
}

void Trench::alternativeDig(std::string_view line)
{
     std::stringstream input{line.data()};
     std::string extractedInput;
     std::getline(input, extractedInput, ' ');
     auto direction = stringToDirection(extractedInput);

     std::getline(input, extractedInput, ' ');
     auto steps = std::stoi(extractedInput);

     std::getline(input, extractedInput, ' ');
     const auto rgbCode = extractedInput.substr(2, extractedInput.size() - 3);

     std::stringstream ss;
     ss << std::hex << rgbCode.substr(0, 5);
     ss >> steps;

     switch (rgbCode[rgbCode.size() - 1])
     {
     case '0':
         direction = Direction::Right;
         break;
     case '1':
         direction = Direction::Bottom;
         break;
     case '2':
         direction = Direction::Left;
         break;
     case '3':
         direction = Direction::Top;
         break;
     }

     const auto& lastPoint = m_points.empty() ? Point(0.0, 0.0) : m_points.back();
     switch (direction)
     {
     case Direction::Top:
         m_points.emplace_back(lastPoint.GetX(), lastPoint.GetY() - steps);
         break;
     case Direction::Bottom:
         m_points.emplace_back(lastPoint.GetX(), lastPoint.GetY() + steps);
         break;
     case Direction::Left:
         m_points.emplace_back(lastPoint.GetX() - steps, lastPoint.GetY());
         break;
     case Direction::Right:
         m_points.emplace_back(lastPoint.GetX() + steps, lastPoint.GetY());
         break;
     }

     pathLength += steps;
}

int64_t Trench::getPossibleLavaVolume()
{
    //Point origin(0.0, 0.0);
    //std::ranges::sort(m_points, [origin](Point& l, Point& r) { return l.Distance(origin)  < r.Distance(origin); });
    ConvexhullCalculator calc(m_points);
    // Figured out one part of this, but https://aymarino.github.io/polygon-area/ this article helped in the last bit; Pick's theorem was the key
    //calc.CalculateConvexhull();
    return abs(calc.CalculateArea()) + pathLength / 2 + 1;
    // writeTrenchToFile("trench.txt");
    // std::set<Id> examinedIds;
    // for (const auto &trenchNode : m_trench)
    // {
    //     for (const auto &neighbour : trenchNode->getNonTrenchNeighbours())
    //     {
    //         if (countTrenchNeighbours(neighbour) >= 2 && !examinedIds.contains(neighbour))
    //         {
    //             if (floodFill(neighbour, examinedIds) == 1)
    //             {
    //                 break;
    //             }
    //             examinedIds.insert(neighbour);
    //         }
    //     }
    // }
    // writeTrenchToFile("trench2.txt");
    // return m_trench.size() + m_insideTrench.size();
}
