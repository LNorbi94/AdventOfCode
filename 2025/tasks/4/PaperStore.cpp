#include "PaperStore.h"

PaperStore::PaperStore(const std::vector<std::string> &lines)
{
    matrix.reserve(lines.size());
    for (const auto &line : lines)
    {
        matrix.emplace_back(line.begin(), line.end());
    }
}

const std::vector<std::vector<char>> &PaperStore::GetMatrix() const
{
    return matrix;
}

size_t PaperStore::GetAccessiblePapers() const
{
    size_t accessiblePaperCount = 0;

    if (matrix.empty())
    {
        return accessiblePaperCount;
    }

    const auto rowCount = matrix.size();
    const auto colCount = matrix.front().size();

    for (std::size_t r = 0; r < rowCount; ++r)
    {
        for (std::size_t c = 0; c < colCount; ++c)
        {
            if (matrix[r][c] != '@')
            {
                continue;
            }

            std::size_t rollNeighbours = 0;

            for (int dr = -1; dr <= 1; ++dr)
            {
                for (int dc = -1; dc <= 1; ++dc)
                {
                    if (dr == 0 && dc == 0)
                    {
                        continue;
                    }

                    const auto nr = static_cast<int>(r) + dr;
                    const auto nc = static_cast<int>(c) + dc;

                    if (nr < 0 || nc < 0)
                    {
                        continue;
                    }

                    const auto ur = static_cast<std::size_t>(nr);
                    const auto uc = static_cast<std::size_t>(nc);

                    if (ur >= rowCount || uc >= colCount)
                    {
                        continue;
                    }

                    if (matrix[ur][uc] == '@')
                    {
                        ++rollNeighbours;
                    }
                }
            }

            if (rollNeighbours < 4)
            {
                ++accessiblePaperCount;
            }
        }
    }

    return accessiblePaperCount;
}

size_t PaperStore::GetAccessiblePapersWithRemovedPaper()
{
    size_t accessiblePaperCount = 0;

    if (matrix.empty())
    {
        return accessiblePaperCount;
    }

    const auto rowCount = matrix.size();
    const auto colCount = matrix.front().size();

    bool removedAnyPaper = true;
    while (removedAnyPaper)
    {
        removedAnyPaper = false;

        for (std::size_t r = 0; r < rowCount; ++r)
        {
            for (std::size_t c = 0; c < colCount; ++c)
            {
                if (matrix[r][c] != '@')
                {
                    continue;
                }

                std::size_t rollNeighbours = 0;

                for (int dr = -1; dr <= 1; ++dr)
                {
                    for (int dc = -1; dc <= 1; ++dc)
                    {
                        if (dr == 0 && dc == 0)
                        {
                            continue;
                        }

                        const auto nr = static_cast<int>(r) + dr;
                        const auto nc = static_cast<int>(c) + dc;

                        if (nr < 0 || nc < 0)
                        {
                            continue;
                        }

                        const auto ur = static_cast<std::size_t>(nr);
                        const auto uc = static_cast<std::size_t>(nc);

                        if (ur >= rowCount || uc >= colCount)
                        {
                            continue;
                        }

                        if (matrix[ur][uc] == '@')
                        {
                            ++rollNeighbours;
                        }
                    }
                }

                if (rollNeighbours < 4)
                {
                    ++accessiblePaperCount;
                    removedAnyPaper = true;
                    matrix[r][c] = '.';
                }
            }
        }
    }

    return accessiblePaperCount;
}

std::size_t PaperStore::GetRowCount() const
{
    return matrix.size();
}

std::size_t PaperStore::GetColumnCount() const
{
    return matrix.empty() ? 0U : matrix.front().size();
}
