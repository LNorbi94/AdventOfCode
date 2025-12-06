#include <gtest/gtest.h>

#include <5/CafeteriaDatabase.h>

class CafeteriaDatabaseTests : public testing::Test
{
};

TEST_F(CafeteriaDatabaseTests, NonOverlappingRangesDoNotDuplicate)
{
    CafeteriaDatabase database;

    // Add non-overlapping ranges: [1-5] and [10-15]
    // Total should be: 5 + 6 = 11 items
    database.AddFreshFoodRange(1, 5);
    database.AddFreshFoodRange(10, 15);

    // Expected: (5-1+1) + (15-10+1) = 5 + 6 = 11
    size_t expectedTotal = (5 - 1 + 1) + (15 - 10 + 1);
    EXPECT_EQ(database.TotalNumberOfFreshFood(), expectedTotal);
}

TEST_F(CafeteriaDatabaseTests, OverlappingRangesDoNotDuplicate)
{
    CafeteriaDatabase database;

    // Add overlapping ranges: [1-5] and [3-7]
    // Unique items: 1,2,3,4,5,6,7 = 7 items (not 5+5=10)
    database.AddFreshFoodRange(1, 5);
    database.AddFreshFoodRange(3, 7);

    // Expected: 7 unique items (1 through 7)
    size_t expectedTotal = 7;
    EXPECT_EQ(database.TotalNumberOfFreshFood(), expectedTotal);
}

TEST_F(CafeteriaDatabaseTests, FullyContainedRangeDoesNotDuplicate)
{
    CafeteriaDatabase database;

    // Add ranges where one is fully contained: [1-10] and [3-5]
    // Unique items: 1,2,3,4,5,6,7,8,9,10 = 10 items (not 10+3=13)
    database.AddFreshFoodRange(1, 10);
    database.AddFreshFoodRange(3, 5);
    database.AddFreshFoodRange(1, 2);
    database.AddFreshFoodRange(9, 10);

    // Expected: 10 unique items (1 through 10)
    size_t expectedTotal = 10;
    EXPECT_EQ(database.TotalNumberOfFreshFood(), expectedTotal);
}

TEST_F(CafeteriaDatabaseTests, MultipleOverlappingRangesDoNotDuplicate)
{
    CafeteriaDatabase database;

    // Add multiple overlapping ranges: [1-5], [3-7], [6-10]
    // Unique items: 1,2,3,4,5,6,7,8,9,10 = 10 items
    database.AddFreshFoodRange(3, 7);
    database.AddFreshFoodRange(6, 10);
    database.AddFreshFoodRange(1, 5);

    // Expected: 10 unique items (1 through 10)
    size_t expectedTotal = 10;
    EXPECT_EQ(database.TotalNumberOfFreshFood(), expectedTotal);
}

TEST_F(CafeteriaDatabaseTests, AdjacentRangesDoNotDuplicate)
{
    CafeteriaDatabase database;

    // Add adjacent ranges: [1-5] and [6-10]
    // Unique items: 1,2,3,4,5,6,7,8,9,10 = 10 items
    database.AddFreshFoodRange(1, 5);
    database.AddFreshFoodRange(6, 10);

    // Expected: 10 unique items
    size_t expectedTotal = 10;
    EXPECT_EQ(database.TotalNumberOfFreshFood(), expectedTotal);
}

TEST_F(CafeteriaDatabaseTests, FragmentedRanges)
{
    CafeteriaDatabase database;

    // Add adjacent ranges: [1-5] and [6-10]
    // Unique items: 1,2,3,4,5,6,7,8,9,10 = 10 items
    database.AddFreshFoodRange(1, 1);
    database.AddFreshFoodRange(2, 2);
    database.AddFreshFoodRange(3, 4);

    // Expected: 10 unique items
    size_t expectedTotal = 4;
    EXPECT_EQ(database.TotalNumberOfFreshFood(), expectedTotal);
}
