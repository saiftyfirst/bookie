#pragma once

#include "DateUtils.hpp"

#include <ctime>
#include <string>

namespace safe
{
class Date
{
public:
    explicit Date(const std::string& dateStr);

    Date(const Date&) = default;
    Date(Date&&) = default;

    Date& operator=(const Date&) = default;
    Date& operator=(Date&&) = default;

    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    Date& operator++();
    Date operator++(int);

    [[nodiscard]] Day getDay() const;
    [[nodiscard]] Month getMonth() const;
    [[nodiscard]] Year getYear() const;

    // derived
    [[nodiscard]] bool isWeekDay() const;
    [[nodiscard]] bool isLeapYear() const;

private:
    Date(std::int32_t rawDay, std::int32_t rawMonth, std::int32_t rawYear);

    template<bool Default>
    [[nodiscard]] bool lessThanOr(const Date& other) const
    {
        auto thisYear = theCTime.tm_year;
        auto otherYear = other.theCTime.tm_year;
        if (thisYear < otherYear) return true;
        if (thisYear > otherYear) return false;

        auto thisMonth = theCTime.tm_mon;
        auto otherMonth = other.theCTime.tm_mon;
        if (thisMonth < otherMonth) return true;
        if (thisMonth > otherMonth) return false;

        auto thisDay = theCTime.tm_mday;
        auto otherDay = other.theCTime.tm_mday;
        if (thisDay < otherDay) return true;
        if (thisDay > otherDay) return false;

        return Default;
    }

    template<bool Default>
    [[nodiscard]] bool greaterThanOr(const Date& other) const
    {
        auto thisYear = theCTime.tm_year;
        auto otherYear = other.theCTime.tm_year;
        if (thisYear > otherYear) return true;
        if (thisYear < otherYear) return false;

        auto thisMonth = theCTime.tm_mon;
        auto otherMonth = other.theCTime.tm_mon;
        if (thisMonth > otherMonth) return true;
        if (thisMonth < otherMonth) return false;

        auto thisDay = theCTime.tm_mday;
        auto otherDay = other.theCTime.tm_mday;
        if (thisDay > otherDay) return true;
        if (thisDay < otherDay) return false;

        return Default;
    }



    tm theCTime;
};

} // safe