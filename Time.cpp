#include"Time.h"
#include<ctime>
#include<iostream>

Time :: Time(int hrs, int min, int sec)
{
	setHour(hrs);
	setMinute(min);
	setSeconds(sec);
}

bool Time :: operator==(const Time & t) const
{
	if(hour == t.getHour() && min == t.getMinute() && sec == t.getSecond())
		return 1;
	return 0;
}

bool Time :: operator > (const Time & t) const 
{
	if(sec > t.getSecond() && min > t.getMinute() && hour >= t.getHour())
		return 1;
	return 0;
}

int Time :: timeToInteger()
{
	return (((getHour() * 100) + getMinute()) * 100) + getSecond();
}

Time Time :: integerToTime(int some)
{
	int s = some % 10000;
	return Time(some / 10000, s / 100, s % 100);
}

std :: ostream & operator << (std :: ostream & os, Time & t)
{
	t.printTwelveHourFormat();
	if(t.getHour() >= 12)
		std :: cout << " PM";
	else
		std :: cout << " AM";
	return os;
}

Time Time :: getTime()
{
	return Time(hour,min,sec);
}

bool Time :: operator < (const Time & t) const 
{
	if(sec < t.getSecond() && min < t.getMinute() && hour <= t.getHour())
		return 1;
	return 0;
}

void Time :: setHour(int h)
{
	if(h >= 0 && h <= 23)
		hour = h;
}

void Time :: setMinute(int m)
{
	if(m >= 0 && m <= 59)
		min = m;
}

void Time :: setSeconds(int s)
{
	if(s >= 0 && s <= 59)
		sec = s;
}

void Time :: setTime(int h, int m, int s)
{
	setHour(h);
	setMinute(m);
	setSeconds(s);
}

int Time :: getHour() const
{
	return hour;
}
	
int Time :: getMinute() const
{
	return min;
}

int Time :: getSecond() const
{
	return sec;
}

void Time :: incHour(int a)
{
	hour += a;
	hour %= 24;
}

void Time :: incMin(int a)
{
	int h;
	min += a;
	h = min / 60;
	min %= 60;
	incHour(h);
}

void Time :: decHour(int a)
{
	hour += a;
	if(hour < 0)
		hour = 23;
}

void Time :: decMin(int a)
{
	min += a;
	while(min < 0)
	{
		min = 60 + min;
		decHour(-1);
	}
}

void Time :: decSec(int a )
{
	sec += a;
	while(sec < 0)
	{
		sec = 60 + sec;
		decMin(-1);
	}
}

Time :: Time()
{
	time_t now = time(0);
	tm * ltm = localtime(&now);
	hour =  ltm->tm_hour;
	min = ltm->tm_min;
	sec = ltm->tm_sec;
}

void Time :: incSec(int a)
{
	int m;
	sec += a;
	m = sec / 60;
	sec %= 60;
	incMin(m);
}

void Time :: printTwentyFourHourFormat()
{
	std :: cout << hour << " : " << min << " : " << sec;
}

void Time :: printTwelveHourFormat()
{
	int h = hour % 12;
	if(h == 0)
		h = 12;

	std :: cout << h << " : " << min << " : " << sec;
}

void Time :: operator=(const Time & t)
{
	setTime(t.hour, t.min, t.sec);
}