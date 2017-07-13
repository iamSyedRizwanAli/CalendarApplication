#include"SimpleClock.h"

SimpleClock :: SimpleClock()
{}

SimpleClock :: SimpleClock(const Date & d, const Time & t):Date(d),Time(t)
{}

SimpleClock :: SimpleClock(int hr, int min, int sec, int day, int month, int year):Time(hr,min,sec),Date(day,month,year)
{}

void SimpleClock :: displayClock()
{
	std :: cout << " ";
	getDateInFormat2().display();
	std :: cout << std :: endl << " ";
	printTwelveHourFormat();
}

void SimpleClock :: refresh()
{
	Date s;
	Time t;

	this -> Date :: operator=(s);
	this->Time :: operator=(t);

}