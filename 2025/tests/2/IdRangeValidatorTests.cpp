#include <gtest/gtest.h>

#include <common/StringManipulation.h>
#include <2/IdRangeValidator.h>

namespace
{
    const std::string sampleInput = R"(11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124)";
}

class IdRangeValidatorTests : public testing::Test
{
protected:
    void SetUp() override
    {
        splitSampleInput = common::splitToMultipleString(sampleInput, ',');
    }

    std::vector<std::string> splitSampleInput;
};

TEST_F(IdRangeValidatorTests, SampleTest)
{
    size_t invalidIdSum = 0;
    for (auto& range : splitSampleInput) {
        auto [from, to] = common::splitString(range, "-");
        IdRangeValidator validator(std::stoi(from), std::stoi(to));
        invalidIdSum += validator.getInvalidIdSum();
    }
    EXPECT_EQ(invalidIdSum, 1227775554);
}
