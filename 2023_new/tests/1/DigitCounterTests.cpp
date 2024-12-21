#include <gtest/gtest.h>

#include "1/DigitCounter.h"

class DigitCounterTests : public testing::Test
{
};

TEST_F(DigitCounterTests, SampleTest)
{
    const std::string input = R"(1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet)";
    DigitAdder summer;

    EXPECT_EQ(summer.AddDigits(input), 142);
}

TEST_F(DigitCounterTests, Sample2Test)
{
    const std::string input = R"(two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen)";
    DigitAdder summer{DigitAdder::DigitType::NormalOrSpelledOut};

    EXPECT_EQ(summer.AddDigits(input), 281);
}
