#include"Clock.h"
#include"QoutationList.h"
#include<iostream>
#include<cmath>

Clock :: Clock() : dayCheck(0), quotationIndex(0)
{}

Clock :: Clock(const Date & d, const Time & t):SimpleClock(d,t)
{}

void Clock :: displayClock()
{
	if(dayCheck != Date :: getDay())
	{
		dayCheck = Date :: getDay();
		quotationIndex = ql.getRandomQuotationFromTheListToDisplayOnClock();
	}
	std :: cout << std :: endl <<  " ";

	while(!ql.displayQuotation(quotationIndex))
		quotationIndex = ql.getRandomQuotationFromTheListToDisplayOnClock();

	std :: cout << std :: endl;
	SimpleClock :: displayClock();
}

void Clock :: removeQuotationStringWise(CString & str)
{
	ql.removeQuotation(str);
}

void Clock :: removeQuotation()
{
	ql.removeQuotation();
}

void Clock :: addQuotation()
{
	CString quote;
	CString author;

	std :: cout << "Quotation : ";
	std :: cin >> quote;
	std :: cout << "Authors Name : ";
	std :: cin >> author;

	ql.addQuotation(quote,author);
}