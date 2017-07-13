#ifndef SIMPLECLOCK_H
#define SIMPLECLOCK_H
#include"Time.h"
#include"Date.h"
#include<ctime>
class SimpleClock:public Time, public Date
{
public:
	SimpleClock();
	SimpleClock(const Date & d, const Time & t);
	void displayClock();
	void refresh();
	SimpleClock(int hr, int min, int sec, int day, int month, int year);
};
#endif