#include "Date.hpp"

namespace safe
{
Date::Date(const std::string& dateStr) : theCTime{}
{
    theCTime.tm_year = std::stoi(dateStr.substr(0,4)) - 1900;
    theCTime.tm_mon = std::stoi(dateStr.substr(4,2)) - 1;
    theCTime.tm_mday = std::stoi(dateStr.substr(6,2));
    mktime( &theCTime );
}

Date::Date(std::int32_t rawDay, std::int32_t rawMonth, std::int32_t rawYear) : theCTime{}
{
    theCTime.tm_year = rawYear - 1900;
    theCTime.tm_mon = rawMonth;
    theCTime.tm_mday = rawDay;
    mktime( &theCTime );
}

Day Date::getDay() const
{
    return Day(theCTime.tm_wday);
}

Month Date::getMonth() const
{
    return Month(theCTime.tm_mon);
}

Year Date::getYear() const
{
    return Year { .value = (1900 + theCTime.tm_year) };
}

bool Date::isWeekDay() const
{
    auto dayOfWeek = getDay();
    return !(dayOfWeek == Day::Saturday || dayOfWeek == Day::Sunday);
}

bool Date::isLeapYear() const
{
    return getYear().isLeapYear();
}

bool Date::operator<(const Date& other) const {
    return lessThanOr<false>(other);
}

bool Date::operator>(const Date& other) const {
    return greaterThanOr<false>(other);
}

bool Date::operator<=(const Date& other) const {
    return lessThanOr<true>(other);
}

bool Date::operator>=(const Date& other) const {
    return greaterThanOr<true>(other);
}

bool Date::operator==(const Date& other) const
{
    return other.theCTime.tm_mday == theCTime.tm_mday &&
        other.theCTime.tm_mon == theCTime.tm_mday &&
        other.theCTime.tm_year == theCTime.tm_year;
}

bool Date::operator!=(const Date& other) const
{
    return !(other == *this);
}

Date& Date::operator++()
{
    auto month = getMonth();
    auto year = getYear();

    auto maxDaysInMonth = safe::NumberOfDaysInMonth(month, year);

    auto rawYear = year.value;
    auto rawMonth = safe::toUnderlying(month);
    auto rawDay = theCTime.tm_mday;

    rawDay += 1;
    if (rawDay > maxDaysInMonth)
    {
        rawDay = 1;
        rawMonth += 1;

        if (rawMonth > 11)
        {
            rawMonth = 0;
            rawYear += 1;
        }
    }

    theCTime.tm_year =  rawYear - 1900;
    theCTime.tm_mon = rawMonth;
    theCTime.tm_mday = rawDay;

    mktime( &theCTime );

    return *this;
}

Date Date::operator++(int)
{
    Date temp = *this;
    ++*this;
    return temp;
}

} // namespace safe