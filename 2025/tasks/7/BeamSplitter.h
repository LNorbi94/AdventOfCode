#pragma once

#include <string>
#include <vector>
#include <map>

class BeamSplitter
{
public:
    // Process the input lines to track beam splitting.
    // - First line: find 'S' and save its position (column index).
    // - Subsequent lines: process beams one by one.
    //   - Empty line: beams continue at their current positions.
    //   - '^' character: splits beams at that position to left and right (with boundary checks).
    //   - Counts the number of times beams are split.
    void ProcessLines(const std::vector<std::string> &lines);

    void ProcessQuantumLines(const std::vector<std::string> &lines);

    // Returns the number of times the beam was split.
    size_t GetSplitCount() const;

    size_t GetNumberOfTimelines() const;

private:
    size_t splitCount = 0;
    size_t sPosition = 0;

    // Helper to check if a position is within bounds.
    bool isValidPosition(size_t position, size_t lineLength) const;

    std::map<size_t, int64_t> timelineCountMap;
};
