#include "BeamSplitter.h"

#include <algorithm>
#include <functional>
#include <map>
#include <iostream>
#include <ranges>
#include <set>

void BeamSplitter::ProcessLines(const std::vector<std::string> &lines)
{
    if (lines.empty())
    {
        return;
    }

    // Find 'S' in the first line
    const std::string &firstLine = lines[0];
    auto sPos = firstLine.find('S');
    if (sPos == std::string::npos)
    {
        return; // No 'S' found
    }
    sPosition = sPos;

    // Initialize beams with the S position
    std::set<size_t> beams = {sPosition};

    // Process subsequent lines
    for (size_t i = 1; i < lines.size(); ++i)
    {
        const std::string &line = lines[i];
        std::set<size_t> newBeams;

        if (line.empty())
        {
            // Empty line: beams continue at their current positions
            newBeams = beams;
        }
        else
        {
            // Process each beam position
            for (size_t beamPos : beams)
            {
                if (beamPos < line.length())
                {
                    if (line[beamPos] == '^')
                    {
                        // Split the beam to left and right
                        ++splitCount;

                        // Left split (position - 1)
                        if (beamPos > 1)
                        {
                            newBeams.insert(beamPos - 1);
                        }

                        // Right split (position + 1)
                        if (isValidPosition(beamPos + 1, line.length()))
                        {
                            newBeams.insert(beamPos + 1);
                        }
                    }
                    else
                    {
                        // Beam continues at the same position
                        newBeams.insert(beamPos);
                    }
                }
            }
        }

        beams = std::move(newBeams);
    }
}

size_t BeamSplitter::GetSplitCount() const
{
    return splitCount;
}

void BeamSplitter::ProcessQuantumLines(const std::vector<std::string> &lines)
{
    if (lines.empty())
    {
        return;
    }

    // Find 'S' in the first line
    const std::string &firstLine = lines[0];
    auto sPos = firstLine.find('S');
    if (sPos == std::string::npos)
    {
        return; // No 'S' found
    }
    sPosition = sPos;

    timelineCountMap[sPosition] = 1;
    for (const auto &line : lines | std::views::drop(1))
    {
        std::map<size_t, int64_t> newTimelineCountMap;
        for (auto &[beamPos, numberOfTimelines] : timelineCountMap)
        {
            if (line[beamPos] == '^')
            {
                newTimelineCountMap[beamPos] -= numberOfTimelines;
                newTimelineCountMap[beamPos - 1] += numberOfTimelines;
                newTimelineCountMap[beamPos + 1] += numberOfTimelines;
            }
        }
        for (auto &[beamPos, numberOfTimelines] : newTimelineCountMap)
        {
            timelineCountMap[beamPos] += numberOfTimelines;
        }
    }
}

size_t BeamSplitter::GetNumberOfTimelines() const
{
    return std::ranges::fold_left(timelineCountMap | std::views::values, 0, std::plus<int64_t>());
}

bool BeamSplitter::isValidPosition(size_t position, size_t lineLength) const
{
    return position < lineLength;
}
