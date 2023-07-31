#pragma once

#include "Date.hpp"

namespace safe
{
class DateRange {
public:
    DateRange(const Date& startDate, const Date& endDate);
    DateRange(const DateRange&) = default;
    DateRange(DateRange&&) = default;

    DateRange& operator=(const DateRange&) = default;
    DateRange& operator=(DateRange&&) = default;

    [[nodiscard]] bool contains(const Date& date) const;

private:
    Date mStartDate;
    Date mEndDate;
};
}
