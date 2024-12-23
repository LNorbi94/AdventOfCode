#include <gtest/gtest.h>

#include "../14/source/Platform.h"
#include <StringManipulation.h>

#include <fstream>
#include <ranges>

class RockTests : public testing::Test
{
protected:
    void ReadInput(const std::string &input)
    {
        const auto lines = common::splitToMultipleString(input, '\n');
        for (auto &line : lines)
        {
            p.addRow(line);
        }
    }

    Platform p;
};

// TEST_F(RockTests, SimpleTest)
// {
//     const auto input = R"(O....#....
// O.OO#....#
// .....##...
// OO.#O....O
// .O.....O#.
// O.#..O.#.#
// ..O..#O..O
// .......O..
// #....###..
// #OO..#....)";
//     ReadInput(input);

//     // p.MoveRocksTo(Platform::Direction::South);
//     p.SlowSpinCycle(2);
//     EXPECT_EQ(p.CalculateMaxLoad(), 64);
// }

TEST_F(RockTests, CompleteInputTest)
{
    std::ifstream file("complete.txt");

    if (!file.is_open())
    {
        return;
    }

    // Read the file line by line into a string
    std::string line;
    while (getline(file, line))
    {
        p.addRow(line);
    }

    for (const auto &i : std::ranges::iota_view{150, 180})
    {
        Platform p2 = p;
        p2.SpinCycle(i);
        const auto load = p2.CalculateMaxLoad();
        Platform p3 = p;
        p3.SlowSpinCycle(i);
        const auto load2 = p3.CalculateMaxLoad();
        EXPECT_EQ(load, load2) << i << " cycles";
        std::cout << i << "\n";
    }
}
