#include <gtest/gtest.h>

#include "1/DigitAdder.h"

namespace
{

    const std::string sampleInput = R"(1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet)";

    const std::string sampleInput2 = R"(two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen)";

}

class DigitAdderTests : public testing::Test
{
};

TEST_F(DigitAdderTests, SampleTest)
{
    DigitAdder adder;
    EXPECT_EQ(adder.AddDigits(sampleInput), 142);
}

TEST_F(DigitAdderTests, Sample2Test)
{
    DigitAdder adder{DigitAdder::DigitType::NormalOrSpelledOut};
    EXPECT_EQ(adder.AddDigits(sampleInput2), 281);
}
