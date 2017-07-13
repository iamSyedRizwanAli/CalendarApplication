
#ifndef TIME_H
#define TIME_H
#include<iostream>
class Time
{
private:
	int hour;
	int min;
	int sec;
	void setHour(int h);
	void setMinute(int m);
	void setSeconds(int s);
public:
	Time();
	Time(int hrs, int min, int sec);
	void setTime(int h, int m, int s);
	int getHour() const;
	int getMinute() const;
	int getSecond() const;
	void incHour(int a = 1);
	void incMin(int a = 1);
	void incSec(int a = 1);
	void decHour(int a);
	void decMin(int a);
	void decSec(int a);
	void printTwentyFourHourFormat();
	void printTwelveHourFormat();
	void operator=(const Time & t);
	bool operator==(const Time & t) const;
	bool operator > (const Time & t) const;
	bool operator < (const Time & t) const;
	Time getTime();
	int timeToInteger();
	static Time integerToTime(int);
};

std :: ostream & operator << (std :: ostream & os, Time & t);
#endif