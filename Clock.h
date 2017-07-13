#ifndef CLOCK_H
#define CLOCK_H
#include"SimpleClock.h"
#include"QoutationList.h"
#include<ctime>
class Clock:public SimpleClock
{
	QuotationList ql;
	int dayCheck;
	int quotationIndex;
public:
	Clock();
	Clock(const Date & d, const Time & t);
	void displayClock();
	void addQuotation();
	void removeQuotation();
	void removeQuotationAuthorWise(CString & author);
	void removeQuotationStringWise(CString & str);
	//Clock(int hr, int min, int sec, int day, int month, int year);
};
#endif