#include <iostream>
#include <ctime>

#include "Booking.h"

using namespace std;

int main(){
	Booking testBooking = Booking("28-12-2017", "10-01-2018");
	cout<<testBooking<<endl;
	testBooking.addSpecialDateRange("31-12-2017", "05-01-2018", 600);
	cout<<testBooking<<endl;
	return 0;
}