#include "Booking.h"

Booking::Booking(){
	startDate = "";
	endDate = "";
}

Booking::Booking(std::string sDate, std::string eDate) : startDate(sDate), endDate(eDate){
	populateBookingData();
}

bool Booking::setStartDate(std::string sDate){
	startDate = sDate;
	if(endDate!="" && startDate!="") populateBookingData();
	return true;
}

std::string Booking::getStartDate(){
	return startDate;
}

bool Booking::setEndDate(std::string eDate){
	endDate = eDate;
	if(endDate!="" && startDate!="") populateBookingData();
	return true;
}

std::string Booking::getEndDate(){
	return endDate;
}

int Booking::getBookingSum(){
	bookingMap::iterator it = bookingData.begin();
	dataMap::iterator find_it;
	for(it; it!= bookingData.end(); ++it){
		find_it = specialDates.find(it->second.begin()->first);
		if(find_it != specialDates.end())
			it->second.begin()->second = find_it->second;
	}
}

//Utilities
void Booking::numerifyDate(std::string date, int* day, int* month, int* year){
	*day = atoi(date.substr(0,2).c_str());
	*month = atoi(date.substr(3,2).c_str());
	*year = atoi(date.substr(6,4).c_str());
}

int Booking::getDayOfWeek(int day,int month,int year){
	tm timeStruct = {};
	timeStruct.tm_year = year - 1900;
	timeStruct.tm_mon = month - 1;
	timeStruct.tm_mday = day;
	timeStruct.tm_hour = 12;
	mktime( &timeStruct );
	return timeStruct.tm_wday;
}

bool Booking::isWeekDay(int dayOfWeek){
	if(dayOfWeek==0 || dayOfWeek==6) return false;
	else return true;
}

void Booking::incrementDate(int& day, int& month, int& year){
	bool toMonths[12] = {true, false, true, false, true, false, true, true, false, true, false, true};
	day++;
	if((toMonths[month-1] && day==32) || (!toMonths[month-1] && day==31) || (month==2 && (year%4!=0) && day==29) || (month==2 && day==30)){
		day = 1;
		month++;
	}
	if(month>12){
		month =1;
		year++;
	}
}

bool Booking::dateInRange(const int& day, const int& month, const int& year, const int& eDay, const int& eMonth, const int& eYear){
	if( year > eYear) return false;
	else if( year==eYear && month > eMonth) return false;
	else if (year==eYear && month==eMonth && day>eDay) return false;
	else return true;
}

void Booking::prepareDateString(int day, int month, int year, string& dateStr){
	int date[3] = {day, month, year};
	char buffer[5] = {};
	for(int i=0; i<3; i++){
		if(date[i] < 10) dateStr.append("0");
		sprintf(buffer, "%d", date[i]);
		dateStr.append(buffer);
		dateStr.append("-");
	}
	dateStr = dateStr.substr(0, dateStr.size()-1);
}

//Public to add special dates
void Booking::addSpecialDateRange(std::string sDate, std::string eDate, int price){
	int day, month, year;
	int lastDay, lastMonth, lastYear;
	numerifyDate(sDate, &day, &month, &year);
	numerifyDate(eDate, &lastDay, &lastMonth, &lastYear);
	std::string dateStr;
	bool rangeLimit = dateInRange(day, month, year, lastDay, lastMonth, lastYear);
	while(rangeLimit){
		dateStr = "";
		prepareDateString(day, month, year, dateStr);
		specialDates.insert(std::pair<std::string,int>(dateStr, price));
		incrementDate(day, month, year);
		rangeLimit = dateInRange(day, month, year, lastDay, lastMonth, lastYear);
	}
	recallibratePrices();
}

//Populating data
void Booking::populateBookingData(){
	int day, month, year;
	int endDay, endMonth, endYear;
	std::string dateStr = "";
	bool weekDay; 
	int roomValue;
	bool rangeLimit;
	dataMap key;
	int counter =0;
	sum = 0;
	numerifyDate(startDate,&day, &month, &year);
	numerifyDate(endDate,&endDay, &endMonth, &endYear);
	rangeLimit = dateInRange(day, month, year, endDay, endMonth, endYear);
	dataMap::iterator it;
	while(rangeLimit){
		key.clear();
		dateStr.erase(0,10);
		prepareDateString(day, month, year, dateStr);
		weekDay = isWeekDay(getDayOfWeek(day, month, year));
		if(weekDay) roomValue = 100;
		else roomValue = 200;
		it = specialDates.find(dateStr);
		if(it != specialDates.end()) roomValue = it->second;
		sum += roomValue;
		key.insert(std::pair<std::string, int>(dateStr, roomValue));
		bookingData.insert(std::pair<int, dataMap >(++counter, key));
		incrementDate(day,month,year);
		rangeLimit = dateInRange(day, month, year, endDay, endMonth, endYear);
	}
	key.clear();
	key.insert(std::pair<std::string, int>("Sum: ", sum));
	bookingData.insert(std::pair<int, dataMap >(++counter, key));
}

//Update Changes after Special Dates
//N-square time : Possible Improvement using custom binary search 
void Booking::recallibratePrices(){
	bookingMap::iterator it = bookingData.begin();
	dataMap::iterator find_it;
	for(it; it!= bookingData.end(); ++it){
		find_it = specialDates.find(it->second.begin()->first);
		if(find_it != specialDates.end()){
			sum += (find_it->second - it->second.begin()->second);
			it->second.begin()->second = find_it->second;
		}
	}
	bookingData.rbegin()->second.begin()->second = sum;
}