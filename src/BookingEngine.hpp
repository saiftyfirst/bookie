#pragma once
#include <ctime>

#include "datetime/Date.hpp"
#include "datetime/DateRange.hpp"
#include "IdTypes.hpp"

namespace safe
{
class BookingEngine {
public:
    explicit BookingEngine(const Date& startDate, const Date& endDate, Price weekDayTariff, Price weekendTariff);
    void updateToSpecialTariff(const Date& date, Price specialTariff);
    void updateToSpecialTariff(const DateRange& dateRange, Price specialTariff);

    Price getTariff(const Date& date);

    BookingEngine(const BookingEngine&) = delete;
    BookingEngine(BookingEngine&&) = delete;

    BookingEngine& operator=(const BookingEngine&) = delete;
    BookingEngine& operator=(BookingEngine&&) = delete;

private:
    const DateRange mFullDateRange;
    const Price mStdWeekDayTariff;
    const Price mStdWeekendTariff;

    std::vector<std::pair<DateRange, Price>> mSpecialTariffs;
};
} // namespace safe


//inline std::ostream& operator<<(std::ostream& os, const Booking& booking){
//    bookingMap bookingData = booking.bookingData;
//    for(bookingMap::iterator it=bookingData.begin(); it!=bookingData.end(); ++it){
//        os<< it->second.begin()->first<<" => " << it->second.begin()->second<< std::endl;
//    }
//    return os;
//}
