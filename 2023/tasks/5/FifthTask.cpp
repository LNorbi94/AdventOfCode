
#include "common/TaskSolver.h"
#include "common/StringManipulation.h"

#include <fstream>
#include <regex>
#include <set>
#include <map>
#include <iostream>
#include "FifthTask.h"
#include <filesystem>

namespace
{
    const std::filesystem::path inputFileName = "5.txt";
}

struct MapEntry
{
    int64_t mapping = 0;
    int64_t length = 0;
};

class Range
{
public:
    Range(const int64_t start, const int64_t end)
        : m_start{start}, m_end{end}
    {
    }

    std::optional<Range> getIntersection(const Range &other)
    {
        if (containsRange(other))
        {
            return other;
        }

        Range possibleIntersection{std::max(m_start, other.getStart()), std::min(m_end, other.getEnd())};
        if (containsRange(possibleIntersection))
        {
            return possibleIntersection;
        }
        return {};
    }

    std::vector<Range> getDifference(const Range &other)
    {
        auto intersection = getIntersection(other);
        if (!intersection.has_value())
        {
            return {other};
        }

        std::vector<Range> ranges;
        Range lowerDiff{other.getStart(), intersection->getStart() - 1};
        if (other.containsRange(lowerDiff))
        {
            ranges.push_back(lowerDiff);
        }
        Range upperDiff{intersection->getEnd() + 1, other.getEnd()};
        if (other.containsRange(upperDiff))
        {
            ranges.push_back(upperDiff);
        }

        return ranges;
    }

    int64_t getStart() const
    {
        return m_start;
    }

    int64_t getEnd() const
    {
        return m_end;
    }

    bool containsRange(const Range &other) const
    {
        return m_start <= other.getStart() && m_end >= other.getEnd() && other.getStart() < other.getEnd();
    }

private:
    int64_t m_start = 0;
    int64_t m_end = 0;
};

class Map
{
public:
    void addEntry(const int64_t start, const int64_t destination, const int64_t length)
    {
        m_entries[start] = MapEntry{destination - start, length};
    }

    int64_t mapItem(const int64_t item)
    {
        const auto mappedItem = findInEntries(item);
        return mappedItem.value_or(item);
    }

    const std::map<int64_t, MapEntry> &getEntries() const
    {
        return m_entries;
    }

private:
    std::optional<int64_t> findInEntries(const int64_t item)
    {
        for (const auto &[start, entry] : m_entries)
        {
            const auto length = entry.length;
            if (start <= item && item < start + length)
            {
                return item + entry.mapping;
            }
        }
        return {};
    }

    std::map<int64_t, MapEntry> m_entries;
};

struct Seed
{
    int64_t start = 0;
    int64_t length = 0;
};

class Seeds
{
public:
    void addSeed(const int64_t start, const int64_t length)
    {
        m_seeds.emplace_back(start, length);
    }

    std::vector<Seed> getSeeds() const
    {
        return m_seeds;
    }

    void applyMapping(Map &map)
    {
        std::vector<Seed> newSeeds;

        for (const auto &[start, length] : m_seeds)
        {
            std::vector<Range> remainingRanges;
            remainingRanges.emplace_back(start, start + length - 1);

            for (const auto &[mapStart, entry] : map.getEntries())
            {
                std::vector<Range> newRanges;
                Range mapRange{mapStart, mapStart + entry.length - 1};
                for (const auto &range : remainingRanges)
                {
                    auto intersection = mapRange.getIntersection(range);
                    if (intersection.has_value())
                    {
                        newSeeds.emplace_back(intersection->getStart() + entry.mapping, intersection->getEnd() - intersection->getStart() + 1);
                        newRanges.append_range(mapRange.getDifference(range));
                    }
                    else
                    {
                        newRanges.push_back(range);
                    }
                }
                remainingRanges.swap(newRanges);
            }
            for (const auto &range : remainingRanges)
            {
                newSeeds.emplace_back(range.getStart(), range.getEnd() - range.getStart() + 1);
            }
        }

        m_seeds.swap(newSeeds);
    }

private:
    std::vector<Seed> m_seeds;
};

class FifthTaskPartOneSolver
{
public:
    FifthTaskPartOneSolver(const std::string_view fileName)
    {
        std::ifstream stream{fileName.data()};

        std::string line;
        std::getline(stream, line);
        const auto seeds = common::extractNumbers<int64_t>(line);
        std::getline(stream, line);

        extractMap(stream, m_seedToSoil);
        extractMap(stream, m_soilToFertilizer);
        extractMap(stream, m_fertilizerToWater);
        extractMap(stream, m_waterToLight);
        extractMap(stream, m_lightToTemperature);
        extractMap(stream, m_temperatureToHumidity);
        extractMap(stream, m_humidityToLocation);

        int64_t closestLocation = std::numeric_limits<int64_t>::max();
        for (const auto &seed : seeds)
        {
            const auto soil = m_seedToSoil.mapItem(seed);
            const auto fertilizer = m_soilToFertilizer.mapItem(soil);
            const auto water = m_fertilizerToWater.mapItem(fertilizer);
            const auto light = m_waterToLight.mapItem(water);
            const auto temperature = m_lightToTemperature.mapItem(light);
            const auto humidity = m_temperatureToHumidity.mapItem(temperature);
            const auto location = m_humidityToLocation.mapItem(humidity);
            if (location < closestLocation)
            {
                closestLocation = location;
            }
        }

        std::cout << closestLocation << "\n";
    }

private:
    void extractMap(std::ifstream &stream, Map &map)
    {
        std::string line;
        std::getline(stream, line);
        while (std::getline(stream, line))
        {
            auto numbers = common::extractNumbers<int64_t>(line);
            if (numbers.empty())
            {
                break;
            }
            map.addEntry(numbers[1], numbers[0], numbers[2]);
        }
    }

    Map m_seedToSoil;
    Map m_soilToFertilizer;
    Map m_fertilizerToWater;
    Map m_waterToLight;
    Map m_lightToTemperature;
    Map m_temperatureToHumidity;
    Map m_humidityToLocation;
};

class FifthTaskPartTwoSolver
{
public:
    FifthTaskPartTwoSolver(const std::string_view fileName)
    {
        std::ifstream stream{fileName.data()};

        std::string line;
        std::getline(stream, line);
        const auto seeds = common::extractNumbers<int64_t>(line);
        std::getline(stream, line);

        extractMap(stream, m_seedToSoil);
        extractMap(stream, m_soilToFertilizer);
        extractMap(stream, m_fertilizerToWater);
        extractMap(stream, m_waterToLight);
        extractMap(stream, m_lightToTemperature);
        extractMap(stream, m_temperatureToHumidity);
        extractMap(stream, m_humidityToLocation);

        Seeds rangeOfSeeds;
        for (auto i = 0; i < seeds.size() - 1; i += 2)
        {
            rangeOfSeeds.addSeed(seeds[i], seeds[i + 1]);
        }

        rangeOfSeeds.applyMapping(m_seedToSoil);
        rangeOfSeeds.applyMapping(m_soilToFertilizer);
        rangeOfSeeds.applyMapping(m_fertilizerToWater);
        rangeOfSeeds.applyMapping(m_waterToLight);
        rangeOfSeeds.applyMapping(m_lightToTemperature);
        rangeOfSeeds.applyMapping(m_temperatureToHumidity);
        rangeOfSeeds.applyMapping(m_humidityToLocation);

        int64_t closestLocation = std::numeric_limits<int64_t>::max();
        for (const auto &seed : rangeOfSeeds.getSeeds())
        {
            if (seed.start < closestLocation)
            {
                closestLocation = seed.start;
            }
        }
        std::cout << closestLocation << "\n";
    }

private:
    void extractMap(std::ifstream &stream, Map &map)
    {
        std::string line;
        std::getline(stream, line);
        while (std::getline(stream, line))
        {
            auto numbers = common::extractNumbers<int64_t>(line);
            if (numbers.empty())
            {
                break;
            }
            map.addEntry(numbers[1], numbers[0], numbers[2]);
        }
    }

    Map m_seedToSoil;
    Map m_soilToFertilizer;
    Map m_fertilizerToWater;
    Map m_waterToLight;
    Map m_lightToTemperature;
    Map m_temperatureToHumidity;
    Map m_humidityToLocation;
};

void FifthTask::SolveFirstPart()
{
    FifthTaskPartOneSolver f{inputFileName.string()};
}

void FifthTask::SolveSecondPart()
{
    FifthTaskPartTwoSolver f{inputFileName.string()};
}
