#include "Platform.h"

#include <algorithm>
#include <functional>
#include <ranges>
#include <iostream>

#include <set>

void Platform::addRow(const std::string &line)
{
    std::vector<Rock> row;
    for (const auto &ch : line)
    {
        row.emplace_back(ch);
    }
    rocks.emplace_back(row);
}

void Platform::MoveRocksTo(Direction direction)
{
     if (direction == Direction::North || direction == Direction::West) {
         for (const auto& i : std::ranges::iota_view{ 0ull, rocks.size() })
         {
             for (const auto& j : std::ranges::iota_view{ 0ull, rocks[i].size() })
             {
                 MoveRockToTheEnd(direction, std::make_pair(i, j));
             }
         }
     } else {
         for (const auto& i : std::ranges::iota_view{ 0ull, rocks.size() } | std::views::reverse)
         {
             for (const auto& j : std::ranges::iota_view{ 0ull, rocks[i].size() } | std::views::reverse)
             {
                 MoveRockToTheEnd(direction, std::make_pair(i, j));
             }
         }
     }
}

void Platform::SpinCycle(size_t times)
{
    if (times > 134)
    {
        times = 135 + ((times - 135) % 21);
    }

    for (auto i = 0; i < times; ++i)
    {
        MoveRocksTo(Platform::Direction::North);
        MoveRocksTo(Platform::Direction::West);
        MoveRocksTo(Platform::Direction::South);
        MoveRocksTo(Platform::Direction::East);
    }
}

void Platform::SlowSpinCycle(size_t times)
{
   /* std::set<uint64_t> loads;
    std::set<uint64_t> loads2;
    bool firstDiff = false;*/

    for (auto i = 0; i < times; ++i)
    {
        MoveRocksTo(Platform::Direction::North);
        MoveRocksTo(Platform::Direction::West);
        MoveRocksTo(Platform::Direction::South);
        MoveRocksTo(Platform::Direction::East);

        const auto load = CalculateMaxLoad();
        /*if (i > 133) {
            std::cout << i << ". load: " << load << "\n";
        }*/
        /*if (!loads.contains(load)) {
            loads.insert(load);
        }
        else if (!firstDiff) {
            std::cout << "First diff: " << i << "\n";
            firstDiff = true;
        }

        if (loads.size() == 133) {
            if (!loads2.contains(load)) {
                loads2.insert(load);
            }
            else {
                std::cout << "Unique variants: " << loads2.size() << "\n";
            }
        }*/
    }
}

uint64_t Platform::CalculateMaxLoad()
{
    uint64_t load = 0;
    for (auto i = 0; i < rocks.size(); ++i)
    {
        for (auto j = 0; j < rocks[i].size(); ++j)
        {
            auto &rock = rocks[i][j];
            //std::cout << rock.ToChar();
            if (rock.GetType() == Rock::Type::Rounded)
            {
                load += rocks.size() - i;
            }
        }
        //std::cout << "\n";
    }
    return load;
}

bool Platform::IsValidIndex(const RockIdx rockIdx) const
{
    auto [i, j] = rockIdx;
    return i >= 0 && i < rocks.size() && j >= 0 && j < rocks[i].size();
}

std::optional<Platform::RockIdx> Platform::GetNextRock(Direction direction, RockIdx rockIdx) const
{
    switch (direction)
    {
    case Direction::North:
        rockIdx.first -= 1;
        break;
    case Direction::West:
        rockIdx.second -= 1;
        break;
    case Direction::South:
        rockIdx.first += 1;
        break;
    case Direction::East:
        rockIdx.second += 1;
        break;
    }

    if (IsValidIndex(rockIdx))
    {
        return rockIdx;
    }
    return std::nullopt;
}

void Platform::MoveRockToTheEnd(Direction direction, RockIdx rockIdx)
{
    while (auto nextRockIdx = GetNextRock(direction, rockIdx))
    {
        auto& currentRock = rocks[rockIdx.first][rockIdx.second];
        auto& nextRock = rocks[nextRockIdx->first][nextRockIdx->second];
        if (currentRock.CanBeMoved() && nextRock.CanPlaceRockHere())
        {
            currentRock.ChangeType(Rock::Type::Empty);
            nextRock.ChangeType(Rock::Type::Rounded);
            rockIdx = *nextRockIdx;
        }
        else
        {
            break;
        }
    }
}
