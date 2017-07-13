#include<iostream>
#include"CString.h"
#include"Date.h"
#include<ctime>
using namespace std;

bool Date :: isLeapYear()
{
	if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return true;
	return false;
}

bool Date :: operator==(const Date & dt) const
{
	if(day == dt.getDay() && month == dt.getMonth() && year == dt.getYear())
		return 1;
	return 0;
}

ostream & operator << (ostream & os, Date & d)
{
	d.printFormat2();
	return os;
}

Date Date :: integerToDate(int some)
{
	int s = some / 10000;
	return Date(s/100,s%100,some % 10000);
}

int Date :: dateToInteger()
{
	return (((getDay() * 100) + getMonth()) * 10000) + getYear();
}

Date :: Date()
{
	time_t now = time(0);
	tm * ltm = localtime(&now);

	wDay = ltm -> tm_wday;
	day = ltm -> tm_mday;
	month = ltm -> tm_mon +1;
	year = ltm -> tm_year + 1900;
}

const int Date :: daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

Date :: Date(int d, int mon, int y)
{
	setDate(d,mon,y);
}

Date Date :: getDate()
{
	return Date(*this);
}

bool Date ::  operator > (const Date & d) const
{
	if(year > d.getYear())
		return 1;
	if(year == d.getYear())
	{
		if(month > d.getMonth())
			return 1;
		if(month == d.getMonth())
		{
			if(day > d.getDay())
				return 1;
		}
	}
	return 0;
	/*if(day > d.getDay() && month >= d.getMonth() && year >= d.getYear())
		return 1;
	return 0;*/
}

bool Date ::  operator < (const Date & d) const
{
	if(year < d.getYear())
		return 1;
	if(year == d.getYear())
	{
		if(month < d.getMonth())
			return 1;
		if(month == d.getMonth())
		{
			if(day < d.getDay())
				return 1;
		}
	}
	return 0;
	/*if(day < d.getDay() && month <= d.getMonth() && year <= d.getYear())
		return 1;
	return 0;*/
}

void Date :: setDate(int d, int mon, int y)
{
	setYear(y);
	setMonth(mon);
	setDay(d);

}

void Date :: setDay(int d)
{
	bool status = isLeapYear();
	if(status == true && month == 2)
	{
		if(d > 0 && d < 30)
			day = d;
		if(d < 0)
			day = 1;
		if(d > 29)
			day = 29;
	}
	else
	{
		if(d > 0 && d <= daysInMonth[month])
			day = d;
		if(d < 0)
			day = 0;
		if(d > daysInMonth[month])
			day = daysInMonth[month];
	}
}

void Date :: incWDay(int i)
{
	wDay += i;

	if(wDay < 0)
		wDay = 7 + wDay;
	if(wDay > 6)
		wDay = wDay - 7;
}

int Date :: getWDay() const
{
	return wDay;
}

void Date :: setMonth(int mon)
{
	if(mon > 0 && mon < 13)
		month = mon;
	if(mon < 0)
		month = 1;
	if(mon > 12)
		month = 12;
}

void Date :: setYear(int y)
{
	if(y >= 1900 && y <= 2100)
		year = y;
	if(y < 1900)
		year = 1900;
	if(y > 2100)
		year = 2100;
}

int Date :: getDay() const
{
	return day;
}

int Date :: getMonth() const
{
	return month;
}

int Date :: getYear() const
{
	return year;
}

void Date :: printFormat1() const
{
	cout << month << "/" << day << "/" << year;
}

void Date :: printFormat2() const
{
	cout << day << "/" << month << "/" << year;
}

void Date :: printFormat3() const
{
	cout << year << "/" << month << "/" << day;
}

void Date :: incDay(int a)
{
	day += a;
	incWDay(a);

	if(day <= 0)
	{
		incMonth(-1);
		if(isLeapYear() && month == 2)
			day = 29 + day;
		else
			day = daysInMonth[month] + day;
	}

	bool status = isLeapYear();

	while(day > daysInMonth[month])
	{
		if(month == 2 && isLeapYear() == true)
			day -= 29;
		else
			day -= daysInMonth[month];
		incMonth();
	}

	if(day == 0)
	{
		day = 1;
	}
}

void Date :: incMonth(int a)
{
	int temp;
	month += a;

	

	if(month == 2 && isLeapYear() == false && day == 29)
	{
		day = 1;
		incMonth();
	}

	if(month == 0)
	{
		month = 12;
		incYear(-1);
	}
	if(month == 13)
	{
		month = 1;
		incYear();
	}
}

void Date :: incYear(int a)
{
	year += a;

	if(year < 1900)
		year = 1900;
	if(year > 2100)
		year = 2100;
}


CString Date :: getDateInFormat1()const
{
	CString dayC(CString ::toCString(day));
	CString monthC(CString :: toCString(month));
	CString yearC(CString :: toCString(year));

	monthC.reSize(1);
	monthC.at(monthC.getLength() - 2) = '/';

	monthC.concatEqual(dayC);
	monthC.at(monthC.getLength()) = '/';

	monthC.concatEqual(yearC);

	return monthC;
}

CString Date :: returnMonth(int month)
{
	if(month == 1)
	{
		CString mon("January");
		return mon;
	}
	if(month == 2)
	{
		CString mon("February");
		return mon;
	}
	if(month == 3)
	{
		CString mon("March");
		return mon;
	}
	if(month == 4)
	{
		CString mon("April");
		return mon;
	}
	if(month == 5)
	{
		CString mon("May");
		return mon;
	}
	if(month == 6)
	{
		CString mon("June");
		return mon;
	}
	if(month == 7)
	{
		CString mon("July");
		return mon;
	}
	if(month == 8)
	{
		CString mon("August");
		return mon;
	}
	if(month == 9)
	{
		CString mon("September");
		return mon;
	}
	if(month == 10)
	{
		CString mon("October");
		return mon;
	}
	if(month == 11)
	{
		CString mon("November");
		return mon;
	}
	if(month == 12)
	{
		CString mon("December");
		return mon;
	}
	exit(0);
}

CString Date :: getDateInFormat2()const
{
	CString monthC(returnMonth(month));
	monthC.reSize(1);

	CString dayC(CString :: toCString(day));
	monthC.concatEqual(dayC);
	monthC.at(monthC.getLength()) = ',';

	CString yearC(CString :: toCString(year));
	monthC.concatEqual(yearC);

	return monthC;
}

CString Date ::getDateInFormat3()const
{
	CString dayC(CString :: toCString(day));
	dayC.reSize(1);

	dayC.at(dayC.getLength() - 1) = ' ';
	CString monthC(returnMonth(month));
	dayC.concatEqual(monthC);

	dayC.at(dayC.getLength()) = ' ';
	CString yearC(CString ::toCString(year));
	dayC.concatEqual(yearC);

	return dayC;
}

void Date :: operator=(const Date& dt)
{
	this->setDate(dt.day,dt.month,dt.year);
}