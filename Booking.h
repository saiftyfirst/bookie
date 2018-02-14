#include <string>
#include <map>
#include <ctime>
#include <iostream>
#include <stdio.h>

#ifndef BOOKING
#define BOOKING

typedef std::map<std::string, int> dataMap;
typedef std::map<int, dataMap > bookingMap;

class Booking{
private:
	std::string startDate;
	std::string endDate;
	bookingMap bookingData;
	int sum;

	dataMap specialDates;

	void calculateSum();
	void populateBookingData();
	void numerifyDate(std::string date, int*, int*, int*);
	int getDayOfWeek(int,int,int);
	bool isWeekDay(int);
	void incrementDate(int&, int&, int&);
	void prepareDateString(int, int, int, std::string&);
	bool dateInRange(const int&, const int&, const int&, const int&, const int& ,const int&);
	void recallibratePrices();
public:
	Booking();
	Booking(std::string, std::string);
	bool setStartDate(std::string);
	std::string getStartDate();
	bool setEndDate(std::string);
	std::string getEndDate();
	int getBookingSum();
	void addSpecialDateRange(std::string, std::string, int);
	friend std::ostream& operator<<(std::ostream&, const Booking&);
};

inline std::ostream& operator<<(std::ostream& os, const Booking& booking){
	bookingMap bookingData = booking.bookingData;
	for(bookingMap::iterator it=bookingData.begin(); it!=bookingData.end(); ++it){
		os<< it->second.begin()->first<<" => " << it->second.begin()->second<<endl;
	} 
	return os;
}

#endif