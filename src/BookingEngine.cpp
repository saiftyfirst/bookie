#include "BookingEngine.hpp"

namespace safe {

BookingEngine::BookingEngine(const Date& startDate, const Date& endDate, Price weekDayTariff, Price weekendTariff) :
    mFullDateRange{startDate, endDate},
    mStdWeekDayTariff(weekDayTariff),
    mStdWeekendTariff(weekendTariff),
    mSpecialTariffs{} { }

void BookingEngine::updateToSpecialTariff(const Date& date, Price specialTariff) {
    // Assumes special dates for same date not called multiple times
    mSpecialTariffs.push_back({DateRange{date, date}, specialTariff});
}

void BookingEngine::updateToSpecialTariff(const DateRange& dateRange, Price specialTariff) {
    // Assumes special dates for same date not called multiple times
    mSpecialTariffs.push_back({dateRange, specialTariff});
}

Price BookingEngine::getTariff(const safe::Date &date) {
    Price possibleTariff = date.isWeekDay() ? mStdWeekDayTariff : mStdWeekendTariff;

    for (const auto& [dateRange, specialTariff] : mSpecialTariffs) {
        if (dateRange.contains(date)) {
            possibleTariff = specialTariff;
        }
    }

    return possibleTariff;
}
}