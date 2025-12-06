#pragma once

#include <string>
#include <vector>

class PaperStore
{
public:
    // Construct a matrix from the given input lines.
    // Each string in the input becomes one row, and each character in the
    // string becomes one cell in the matrix.
    explicit PaperStore(const std::vector<std::string> &lines);

    const std::vector<std::vector<char>> &GetMatrix() const;

    std::size_t GetRowCount() const;
    std::size_t GetColumnCount() const;

    // Returns the positions (row, column) of all accessible papers.
    // A paper is a cell containing '@' that has fewer than 4 neighbouring
    // "roll" cells (considering all 8 adjacent directions).
    size_t GetAccessiblePapers() const;
    size_t GetAccessiblePapersWithRemovedPaper();

private:
    std::vector<std::vector<char>> matrix;
};
