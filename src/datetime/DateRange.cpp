#include "DateRange.hpp"

namespace safe
{
DateRange::DateRange(const Date& startDate, const Date& endDate) : mStartDate(startDate), mEndDate(endDate)
{}

bool DateRange::contains(const Date& date) const
{
    return date >= mStartDate && date <=mEndDate;
}
}
