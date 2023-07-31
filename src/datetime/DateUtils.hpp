#pragma once

#include <type_traits>
#include <array>

namespace safe
{
enum class Month
{
    January, February, March, April, May, June, July, August, September, October, November, December
};

enum class Day
{
    Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
};

struct Year
{
    std::int32_t value;

    [[nodiscard]] bool isLeapYear() const
    {
        return value % 4 == 0;
    }
};

template <typename T>
static auto toUnderlying(T t)
{
    return static_cast<std::underlying_type_t<T>>(t);
}

static std::int32_t NumberOfDaysInMonth(Month month, Year year)
{
    static constexpr std::array<std::int32_t, 12> theUsualNumberOfDaysByMonth =
    {
            31, 30, 31, 30, 31, 30,
            31, 31, 30, 31, 30, 31
    };

    if (year.isLeapYear() && month == Month::February)
    {
        return 29;
    }

    return theUsualNumberOfDaysByMonth[toUnderlying(month)];
}
} // namespace Day

