#ifndef DATE_H
#define DATE_H
#include"CString.h"
#include<iostream>
class Date
{
private:
	int day;
	int month;
	int year;
	int wDay;
	bool isLeapYear();
public:	
	static CString returnMonth(int);
	static const int daysInMonth[13];
	Date();
	Date(int,int,int);
	void setDate(int, int, int);
	void setDay(int);
	void setMonth(int);
	void setYear(int);
	int getDay() const;
	int getWDay() const;
	int getMonth() const;
	int getYear() const;
	void printFormat1() const;
	void printFormat2() const;
	void printFormat3() const;
	void incDay(int = 1);
	void incWDay(int = 1);
	void incMonth(int  = 1);
	void incYear(int = 1);
	CString getDateInFormat1()const;
	CString getDateInFormat2()const;
	CString getDateInFormat3()const;
	void operator=(const Date& dt);
	bool operator == (const Date& dt) const;
	bool operator > (const Date & dt) const;
	bool operator < (const Date & dt) const;
	Date getDate();
	int dateToInteger();
	static Date integerToDate(int);
};

std :: ostream & operator << (std :: ostream & os, Date & d);
#endif