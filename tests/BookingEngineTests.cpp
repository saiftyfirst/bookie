#include <gtest/gtest.h>
#include "BookingEngine.hpp"
#include "datetime/Date.hpp"
#include "datetime/DateUtils.hpp"

class BookingEngineTests : public ::testing::Test
{
protected:
    BookingEngineTests() : mVictim(mStart, mEnd, mWeekdayPrice, mWeekendPrice)
    {}

    safe::Date mStart { "20230110" };
    safe::Date mEnd { "20230709" };
    Price mWeekdayPrice { .value = 100.0 };
    Price mWeekendPrice { .value = 50.0 };
    safe::BookingEngine mVictim;
};

TEST_F(BookingEngineTests, RespondsWithCorrectWeekdayTariff)
{
    EXPECT_NEAR(mVictim.getTariff(safe::Date{ "20230216" }).value, 100.0, 0.001);
}

TEST_F(BookingEngineTests, RespondsWithCorrectWeekendTariff)
{
    std::cout << mVictim.getTariff(safe::Date{ "20230716" }).value << std::endl;
    EXPECT_NEAR(mVictim.getTariff(safe::Date{ "20230716" }).value, 50.0, 0.001);
}


TEST_F(BookingEngineTests, RespondsWithCorrectSpecialTariff)
{
    mVictim.updateToSpecialTariff(safe::Date{ "20230716" }, Price{ 70.0 });
    EXPECT_NEAR(mVictim.getTariff(safe::Date{ "20230716" }).value, 70.0, 0.001);
}

TEST_F(BookingEngineTests, RespondsWithCorrectWeekdayTariffAfterSpecialIsApplied)
{
    mVictim.updateToSpecialTariff(safe::Date{ "20230716" }, Price{ 70.0 });
    EXPECT_NEAR(mVictim.getTariff(safe::Date{ "20230715" }).value, 50.0, 0.001);
}

TEST_F(BookingEngineTests, RespondsWithCorrectSpecialTariffForRange)
{
    const safe::Date startDate = safe::Date{ "20231220" };
    const safe::Date endDate = safe::Date{ "20240105" };

    safe::DateRange specialRange{ startDate, endDate };
    mVictim.updateToSpecialTariff(specialRange, Price{ 20.0 });

    safe::Date currDate { startDate };
    while (currDate <= endDate)
    {
        EXPECT_NEAR(mVictim.getTariff(currDate).value, 20.0, 0.001);
        currDate++;
    }
}