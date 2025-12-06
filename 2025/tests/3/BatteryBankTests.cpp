#include <gtest/gtest.h>

#include <common/StringManipulation.h>
#include <3/BatteryBank.h>
#include <3/UnlimitedBatteryBank.h>

class BatteryBankTests : public testing::Test
{
};

TEST_F(BatteryBankTests, StartOfBankTest)
{
    BatteryBank bank("99123456780");
    EXPECT_EQ(bank.getLargestJolt(), 99);
}

TEST_F(BatteryBankTests, EndOfBankTest)
{
    BatteryBank bank("1234567890");
    EXPECT_EQ(bank.getLargestJolt(), 90);
}

TEST_F(BatteryBankTests, MiddleOfBankTest)
{
    BatteryBank bank("12349956780");
    EXPECT_EQ(bank.getLargestJolt(), 99);
}

TEST_F(BatteryBankTests, StartAndEndOfBankTest)
{
    BatteryBank bank("8346573259");
    EXPECT_EQ(bank.getLargestJolt(), 89);
}

TEST_F(BatteryBankTests, SampleTest)
{

    BatteryBank bank("818181911112111");
    EXPECT_EQ(bank.getLargestJolt(), 92);
}

TEST_F(BatteryBankTests, UnlimitedBatteryBankTest)
{
    /*UnlimitedBatteryBank bank("987654321111111");
    EXPECT_EQ(bank.getLargestJolt(), 987654321111);*/
    UnlimitedBatteryBank bank2("234234234234278");
    EXPECT_EQ(bank2.getLargestJolt(), 434234234278);
}