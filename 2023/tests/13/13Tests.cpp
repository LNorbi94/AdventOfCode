#include <gtest/gtest.h>

#include "13/Valley.h"
#include <StringManipulation.h>

class ValleyTests : public testing::Test
{
protected:
    void ReadInput(const std::string &input)
    {
        const auto lines = common::splitToMultipleString(input, '\n');
        for (auto &line : lines)
        {
            v.addRow(line);
        }
    }

    Valley v;
};

TEST_F(ValleyTests, HorizontalEq)
{
    ValleyMap map;
    map.addRow("#####.##.");
    map.addRow("#####.##.");
    map.addRow("#####.##.");

    EXPECT_EQ(map.rowDifferences(0, 2), 0);
}

TEST_F(ValleyTests, HorizontalEq2)
{
    ValleyMap map;
    map.addRow("#####.##.");
    map.addRow("#.#.#.##.");

    EXPECT_EQ(map.rowDifferences(0, 1), 2);
}

TEST_F(ValleyTests, VerticalEq)
{
    ValleyMap map;
    map.addRow("...");
    map.addRow("..#");
    map.addRow("...");
    map.addRow("..#");

    EXPECT_EQ(map.columnDifferences(0, 1), 0);
    EXPECT_EQ(map.columnDifferences(1, 2), 2);
}

TEST_F(ValleyTests, Horizontal1)
{
    v.addRow("#.#.#.#.");
    v.addRow("#.#.#.#.");

    EXPECT_EQ(v.mirrorScore(), 100);
}

TEST_F(ValleyTests, Horizontal2)
{
    const std::string input = R"(#...##..#
#....#..#
..##..###
#####.##.
#####.##.
..##..###
#....#..#)";
    ReadInput(input);

    EXPECT_EQ(v.mirrorScore(), 400);
}

TEST_F(ValleyTests, Vertical1)
{
    v.addRow("..");
    v.addRow("##");

    EXPECT_EQ(v.mirrorScore(), 1);
}

TEST_F(ValleyTests, Vertical2)
{
    const std::string input = R"(#.##..##.
..#.##.#.
##......#
##......#
..#.##.#.
..##..##.
#.#.##.#.)";
    ReadInput(input);

    EXPECT_EQ(v.mirrorScore(), 5);
}
