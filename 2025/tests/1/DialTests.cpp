#include <gtest/gtest.h>

#include "1/Dial.h"
#include <common/StringManipulation.h>
#include <ranges>
#include <string_view>

namespace
{

    const std::string sampleInput = R"(L68
L30
R48
L5
R60
L55
L1
L99
R14
L82)";

}

class DialTests : public testing::Test
{
};

TEST_F(DialTests, SampleTest)
{
    Dial dial;
    for (const auto &line : std::views::split(sampleInput, '\n'))
    {
        dial.runCommand(std::string(std::string_view(line)));
    }
    EXPECT_EQ(dial.zeroPositionReachedAfterCompletingCommandsCount(), 3);
}
