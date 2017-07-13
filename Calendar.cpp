#include"Calendar.h"
#include<iomanip>
#include<iostream>
#include"CString.h"
#include"Schedular.h"
#include<Windows.h>
using namespace std;

const int Calendar :: _REFERNCE_TO_2000[12] = {6,2,3,6,1,4,6,2,5,0,3,5};
const int Calendar :: _REFERNCE_TO_1900[12] = {1,4,4,0,2,5,0,3,6,1,4,6};

Calendar :: Calendar() : schedule(30) {}

char* color(int color= 240, char* message = "")
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    return message;
}

void Calendar :: printColors(CString msg, int type)
{
	int size = msg.getLength();
	char * something = new char [size + 1];

	for(int i = 0 ; i < size ; i++)
		something[i] = msg.at(i);
	
	something[size] = '\0';
	
	switch(type)
	{
	case 0:
		cout << color(252,something);//Red Front
		break;
	case 1:
		cout << color(247,something);//Grey Front
		break;
	case 2:
		cout << color(242,something);//Green front
		break;
	case 3:
		cout << color(250, something);//Light front
		break;
	case 4:
		cout << color(143, something);//Dark Grey Back
		break;
	case 5:
		cout << color(127, something);//Grey Back
		break;
	case 6:
		cout << color(159, something);//Blue Back
		break;
	case 7:
		cout << color(207, something);//Red Back
		break;
	case 8:
		cout << color(175, something);//Light Green Back
		break;
	case 9:
		cout << color(47, something);//Green Back
		break;
	case 10:
		cout << color(95, something);//Purple Back
		break;
	case 11:
		cout << color(249,something);//Blue front
		break;
	case 12:
		cout << color(240,something);//Black front
		break;
	case 13:
		cout << color(248,something);//Grey front
		break;
	case 14:
		cout << color(253,something);//Pink Front
		break;
	}

	color();
}

int Calendar :: colorForTheDayInWeek(int i, int month, int year)
{
	if(i == runningDate.getDay() && i == displayClock.getDay() && month == runningDate.getMonth() && month == displayClock.getMonth() && year == displayClock.getYear())
	{
		return 2;
	}
	if(i == runningDate.getDay())
		return 0;
	if( i == displayClock.getDay() && month == displayClock.getMonth() && year == displayClock.getYear())
		return 11;
	return 12;
}

int Calendar :: colorForTheDay(int i, int month, int year)
{
	if(i == runningDate.getDay() && i == displayClock.getDay() && month == runningDate.getMonth() && month == displayClock.getMonth() && displayClock.getYear() == year)
	{
		if((schedule.doesTaskExistOfType(Date(i,month,year),1) != -1) || (schedule.doesTaskExistOfType(Date(i,month,year),0) != -1))
			return 4;
		return 3;
	}
	if(i == runningDate.getDay())
		return 0;
	if( i == displayClock.getDay() && month == displayClock.getMonth() && year == displayClock.getYear())
		return 11;
	return 12;
}

void Calendar :: incrementMonth(int val)
{
	runningDate.incMonth(val);
}

void Calendar :: incrementYear(int val)
{
	runningDate.incYear(val);
}

void Calendar :: incrementWeek(int val)
{
	incrementDay(val * 7);
}

int Calendar :: getDecade()
{
	int dec = runningDate.getYear() / 10;
	return dec * 10;
}

void Calendar :: refreshClock()
{

	time_t now = time(0);
	tm * ltm = localtime(&now);

	int hr = ltm->tm_hour;
	int min = ltm->tm_min;
	int sec = ltm->tm_sec;
	int day = ltm->tm_mday;
	int mon = ltm->tm_mon;
	int year = ltm->tm_year;

	refreshTime(hr, min, sec);

	if(day != clockForComparison.getDay() && mon != clockForComparison.getMonth() && year != clockForComparison.getYear())
		refreshDate(day, mon, year);
}

void Calendar :: refreshDate(int day, int mon, int year)
{
	int temp1;

	if(clockForComparison.getDay() <= day)
		temp1 = day - clockForComparison.getDay();
	if(day < clockForComparison.getDay())
		temp1 = (Date :: daysInMonth[clockForComparison.getMonth()] - clockForComparison.getDay()) + day;
	clockForComparison.incDay(temp1);
	displayClock.incDay(temp1);

	if(clockForComparison.getMonth() <= mon)
		temp1 = mon - clockForComparison.getMonth();
	if(mon < clockForComparison.getMonth())
		temp1 = ( 12 - clockForComparison.getMonth()) + mon;
	clockForComparison.incMonth(temp1);
	displayClock.incMonth(temp1);

	if(clockForComparison.getYear() < year)
		temp1 = year - clockForComparison.getYear();
	displayClock.incYear(temp1);
	clockForComparison.incYear(temp1);
}

void Calendar :: refreshTime(int hr, int min, int sec)
{
	int temp1;

	if(clockForComparison.getSecond() > sec)
		temp1 = (60 - clockForComparison.getSecond()) + sec;
	if(clockForComparison.getSecond() <= sec)
		temp1 = sec - clockForComparison.getSecond();
	clockForComparison.incSec(temp1);
	displayClock.incSec(temp1);

	if(clockForComparison.getMinute() <= min)
		temp1  = min - clockForComparison.getMinute();
	if(clockForComparison.getMinute() > min)
		temp1 = (60 - clockForComparison.getMinute()) + min;
	clockForComparison.incMin(temp1);
	displayClock.incMin(temp1);

	if(clockForComparison.getHour() <= hr)
		temp1 = hr - clockForComparison.getHour();
	if(clockForComparison.getHour() > hr)
		temp1 = (60 - clockForComparison.getHour()) + hr;
	clockForComparison.incHour(temp1);
	displayClock.incHour(temp1);
}

void Calendar :: getFirstWordsOfTaskOnDate(Date & d)
{
	int ind = schedule.doesTaskExist(d);
	displaySmallString(ind);
}

void Calendar :: getFirstWordsOfAllDayTaskForWeeklyCalendar(Date & d)
{
	int ind =  schedule.doesTaskExistOfType(d, 1);
	displaySmallString(ind);
}

void Calendar :: getFirstWordsOfAllDayTask(Date & d)
{
	int ind =  schedule.doesTaskExistOfType(d, 1);
	displayLargeString(ind);
}

void Calendar :: getFirstWordsOfTask2OfAllDayTask(Date & d)
{
	int ind = schedule.returnIndexOfSecondType1TaskOnDay(d);
	displayLargeString(ind);
}

void  Calendar :: getFirstWordsOfTask1OnDateOnHourForDailyCalendar(Date & d, int hour)
{
	int ind = schedule.doesTaskExistOnHour(d,hour);
	displayLargeString(ind);
}

void  Calendar :: getFirstWordsOfTask2OnDateOnHourForDailyCalendar(Date & d, int hour)
{
	int ind = schedule.returnIndexOfSecondType0TaskOnDayAndHour(d,hour);
	displayLargeString(ind);
}

void Calendar :: getFirstWordsOfTaskOnDateOnHour(Date & d, int hour)
{
	int ind = schedule.doesTaskExistOnHour(d,hour);
	displaySmallString(ind);
}

void Calendar :: displaySmallString(int ind )
{
	if(ind == -1)
	{
		cout <<  setw(17);
		return;
	}
	cout <<  setw(16);
	CString x = schedule.getFirstWordsOfTask(ind);
	
	CString words(' ');
	for(int i = 0 ; i < 12 && i < x.getLength() ; i++)
		words.concatEqual(x.at(i));

	while(words.getLength() < 12)
		words.concatEqual('.');

	printColors(words);
}

void Calendar :: displayLargeString(int ind)
{
	if(ind == -1)
	{
		cout <<  setw(41);
		return;
	}
	CString x = schedule.getFirstWordsOfTask(ind);

	CString words(' ');
	for(int i = 0 ; i < 40 && i < x.getLength() ; i++)
		words.concatEqual(x.at(i));

	while(words.getLength() < 30)
		words.concatEqual('.');

	printColors(words);
}

void Calendar :: getSecondTaskNotificationOnDate(Date & d)
{
	if(schedule.numberOfTasksOnDate(d) >= 2)
	{
		int ind = schedule.returnIndexOfSecondType1TaskOnDay(d);
		displaySmallString(ind);
		cout << "|";
	}
	else
		cout << "                |";
}

void Calendar :: getSecondTaskNotificationOnDate(Date & d, Time & t)
{
	if(schedule.numberOfTasksOnDate(d,t) >= 2)
	{
		int ind = schedule.returnIndexOfSecondType0TaskOnDay(d);
		displaySmallString(ind);
		/*cout << setw(16) << right;
		CString c = "**             ";
		printColors(c);*/
		cout << "|";
	}
	else
		cout << "               ";
}

bool Calendar :: isLeapYear(int year)
{
	if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return true;
	return false;
}


int Calendar :: getFirstDayOfMonth(int month)
{
	decade = getDecade();
	int day;
	if(decade >= 2000)
		day = firstDayOfMonthForDecade2000(month);
	else
		day = firstDayOfMonthForDecade1900(month);
	return day;
}

int Calendar :: firstDayOfMonthForDecade1900(int mon)
{
	if(decade == 1900)
		return helperForDecadeAndYear1900(mon);
	else
		return helperForDecade1900(mon);
}

int Calendar :: helperForDecade1900(int mon)
{
	int temp, temp2;
	temp = 1900 - runningDate.getYear();
	temp2 = temp;
	temp %= 7;
	int i;
	if(mon == 1 || mon == 2)
	{
		i = 0;
		for(i; i < temp2 ; i++)
		{
			if(isLeapYear(1900 + i) == true)
				temp++;
		}
	}
	else
	{
		i = 1;
		for(i; i <= temp2 ; i++)
		{
			if(isLeapYear(1900 + i) == true)
				temp++;
		}
	}
	temp %= 7;
	temp = temp + _REFERNCE_TO_1900[mon-1];
	temp %= 7;
	return temp;
}

int Calendar :: helperForDecadeAndYear1900(int mon)
{
	int temp = runningDate.getYear() - 1900;
	int temp2 = temp;
	temp %= 7;
	int i;
	if(mon == 1 || mon == 2)
	{
		i = 0;
		for(i; i < temp2 ; i++)
		{
			if(isLeapYear(1900 + i) == true)
				temp++;
		}
	}
	else
	{
		i = 1;

		for(i; i <= temp2 ; i++)
		{
			if(isLeapYear(1900 + i) == true)
				temp++;
		}
	}
	temp %= 7;
	temp = temp + _REFERNCE_TO_1900[mon-1];
	temp %= 7;
	return temp;
}

int Calendar :: firstDayOfMonthForDecade2000(int mon)
{
	if(decade == 2000)
		return helperForDecadeAndYear2000(mon);
	else
		return helperForDecade2000(mon);
}

int Calendar :: helperForDecadeAndYear2000(int mon)
{
	int temp = runningDate.getYear() - 2000;
	int temp2 = temp;
	temp %= 7;
	int i;
	if(mon == 1 || mon == 2)
	{
		i = 0;
		for(i; i < temp2 ; i++)
		{
			if(isLeapYear(2000 + i) == true)
				temp++;
		}
	}
	else
	{
		i = 1;
		for(i; i <= temp2 ; i++)
		{
			if(isLeapYear(2000 + i) == true)
				temp++;
		}
	}
	temp %= 7;
	temp = temp + _REFERNCE_TO_2000[mon-1];
	temp %= 7;
	return temp;
}

int Calendar :: helperForDecade2000(int mon)
{
	int temp, temp2;
	temp = runningDate.getYear() - 2000;
	temp2 = temp;
	temp %= 7;
	int i;
	if(mon == 1 || mon == 2)
	{
		i = 0;
		for(i; i < temp2 ; i++)
		{
			if(isLeapYear(2000 + i) == true)
				temp++;
		}
	}
	else
	{
		i = 1;
		for(i; i <= temp2 ; i++)
		{
			if(isLeapYear(2000 + i) == true)
				temp++;
		}
	}
	temp %= 7;
	temp = temp + _REFERNCE_TO_2000[mon-1];
	temp %= 7;
	return temp;
}

void Calendar :: printCursorOrRunningDateFor1stWeek(int i, int mon, int year)
{
	cout << " ";
	printColors(CString :: toCString(i),colorForTheDay(i, mon, year));
	cout << "   ";
}

int Calendar :: displayFirstWeekOfMothInYearlyCalendar(int mon, int control)
{
	int startingDay;
	int previousMonthDays = previousMonthDay(mon , startingDay);

	int d = 0;
	int i = 1;

	if(control == 0)
		cout << '\t';

	while(d++ < startingDay)
	{
		printColors(CString :: toCString(previousMonthDays++),1);
		cout << "   ";
	}
	d--;
	while(d++ < 7)
	{
		if((i == runningDate.getDay() && mon == runningDate.getMonth())|| (i == displayClock.getDay() && mon == displayClock.getMonth()))
		{
			printCursorOrRunningDateFor1stWeek(i, mon, runningDate.getYear());
			i++;
		}
		else if((schedule.doesTaskExistOfType(Date(i,mon,runningDate.getYear()),1) != -1) || (schedule.doesTaskExistOfType(Date(i,mon,runningDate.getYear()),0) != -1))
		{
			cout << " ";
			printColors(CString :: toCString(i),14);
			cout << "   ";
			i++;
		}
		else
		{
			if(d == 1 || d == 7)
			{
				cout << " ";
				printColors(CString :: toCString(i),13);
				i++;
				cout << "   ";
			}
			else
				cout << " "<< i++  << "   ";
		}
	}
	return i;
}


int Calendar :: previousMonthDay( int mon, int & startingDay)
{
	
	startingDay = getFirstDayOfMonth(mon);
	int previousMonthDays;
	if( mon == 1)
		previousMonthDays = 31 - startingDay;
	else
		previousMonthDays = displayClock.daysInMonth[mon - 1] - startingDay;
	previousMonthDays ++;

	return previousMonthDays;
}

bool Calendar :: addTask(Date d, Time t, CString message, bool taskType)
{
	if(d > displayClock.getDate() && t > displayClock.getTime())
	{
		schedule.addTask(d,t,message,taskType);
		return 1;
	}
	return 0;
}

void Calendar :: helperForDisplayingDaysInFirstWeekOfMonthlyCalendar(int previousMonthDays, int month, int year)
{
	int d = 0 , x, i = 1;

	if(month == 1)
		x = 12;
	else
		x = month - 1;

	while(previousMonthDays <= Date::daysInMonth[x])
	{

		cout << setw(16) << right;
		printColors(CString :: toCString(previousMonthDays++), 1);
		cout << "|";
		d++;
	}
	while(d++ < 7)
	{
		if((i == runningDate.getDay() && month == runningDate.getMonth())|| (i == displayClock.getDay() && month == displayClock.getMonth()))
		{
			cout<< setw(15) << right;
			printColors(CString :: toCString(i),colorForTheDay(i, month, runningDate.getYear()));
			cout << " |";
			i++;
		}
		else
		{
			if(d == 0 || d == 7)
			{
				cout << setw(15) << right;
				printColors(CString :: toCString(i),13);
				i++;
				cout << " |";
			}
			else
				cout << setw(15) << right << i++  << " |";
		}
	}
}

void Calendar :: helperForDisplayingFirstTaskInFirstWeekInMonthOfMonthlyCalendar(int previousMonthDays, int month, int year)
{
	int d = 0, x, y;
	int i = 1;

	if(month == 1)
	{
		x = 12;
		y = year -1;
	}
	else
	{
		x = month - 1;
		y = year;
	}
	
	while(previousMonthDays <= Date :: daysInMonth[x])
	{
		cout << setw(16) << right;
		getFirstWordsOfTaskOnDate(Date(previousMonthDays,x ,y));
		cout << '|';
		previousMonthDays++;
		d++;
	}
	while(d++ < 7)
	{
		cout << setw(16) << right;
		getFirstWordsOfTaskOnDate(Date(i,month,year));
		cout << '|';
		i++;
	}
}

int Calendar :: helperForDisplayingSecondtTaskNotificationInFirstWeekInMonthOfMonthlyCalendar(int previousMonthDays, int month, int year)
{
	int d = 0, x, y;
	int i = 1;

	if(month == 1)
	{
		x = 12;
		y = year -1;
	}
	else
	{
		x = month - 1;
		y = year;
	}

	while(previousMonthDays <= Date :: daysInMonth[x])
	{
		getSecondTaskNotificationOnDate(Date(previousMonthDays,x ,y));
		previousMonthDays++;
		d++;
	}
	while(d++ < 7)
	{
		getSecondTaskNotificationOnDate(Date(i,month,year));
		i++;
	}
	return i;
}

int Calendar ::  displayFirstWeekOfMothInMonthlyCalendar(int mon)
{
	int startingDay;
	int previousMonthDays = previousMonthDay(mon , startingDay);
	int year = runningDate.getYear();

	int d = 0;
	int i;

	int count = 0;

	helperForDisplayingDaysInFirstWeekOfMonthlyCalendar(previousMonthDays, mon, year);

	cout << endl;

	printDecorateiveSpacesForWeek();

	cout << endl;
	
	helperForDisplayingFirstTaskInFirstWeekInMonthOfMonthlyCalendar(previousMonthDays,mon, year);
	
	cout << endl;

	i = helperForDisplayingSecondtTaskNotificationInFirstWeekInMonthOfMonthlyCalendar(previousMonthDays,mon,year);

	cout << endl;

	sketchBottomLineForMonthlyCalendar();

	cout << endl;

	return i;
}

int Calendar :: displaySecondWeekToThirdOfMothInMonthlyCalendar(int day, int mon)
{
	int d = 0;
	int x = 0;
	int year = runningDate.getYear();
	while(d < 3)
	{
		printDaysForWeekInMonthlyCalendar(day, mon);

		cout << endl;
		
		printDecorateiveSpacesForWeek();

		cout << endl;
		
		printFirWordsOfTaskNotificationsForWeek(day,mon,year);

		cout << endl;

		printSecondTaskNotificationsForWeek(day,mon,year);

		cout << endl;

		sketchBottomLineForMonthlyCalendar();

		day+=7;
		cout << endl;
		d++;
	}
	return day;
}

void Calendar :: helperOfFifthAndSixthWeekDAYDisplayInMonthlyCalendar(int sday, int month, int year, int k)
{
	for(int i = 0 ; i < 7 ; i++)
		{
			if(sday <= Date :: daysInMonth[month])
			{
				if(sday == runningDate.getDay() || (sday == displayClock.getDay() && month == displayClock.getMonth() && year == displayClock.getYear()))
				{
					cout<< setw(15) << right;
					printColors(CString :: toCString(sday),colorForTheDay(sday, month, runningDate.getYear()));
					cout << " |";
					sday++;
				}
				else
				{
					if(i == 0 || i == 6)
					{
						cout << setw(15);
						printColors(CString :: toCString(sday),13);
						sday++;
						cout << " |";
					}
					else
						cout<< setw(15) << right << sday++  << " |";
				}
			}
			else
			{
				cout<< setw(15) << right;

				if(k == displayClock.getDay() && (month + 1) == displayClock.getMonth() && year == displayClock.getYear())
					printColors(CString::toCString(k++),11);
				else
					printColors(CString::toCString(k++),1);

				cout << " |";
			}
		}
}

void Calendar :: helperOfFifthAndSixthWeekFirstTaskDisplayInMonthlyCalendar(int sday, int month, int year, int k)
{
	int x, y ;
	if(month == 12)
	{
		x = 1;
		y = year + 1;
	}
	else
	{
		x = month + 1;
		y = year;
	}
	for(int i = 0 ; i < 7 ; i++)
	{
		if(sday <= Date :: daysInMonth[month])
		{
			cout << setw(16) << right; 
			getFirstWordsOfTaskOnDate(Date(sday++,month,year));
			cout << '|';
		}
		else
		{
			cout << setw(16) << right;
			getFirstWordsOfTaskOnDate(Date(k++,x,y));
			cout << '|';
		}
	}
}

void Calendar :: helperOfFifthAndSixthWeekSecondTaskNotificationDisplayInMonthlyCalendar(int & sday, int & month, int & year, int & k)
{
	int x, y ;
	if(month == 12)
	{
		x = 1;
		y = year + 1;
	}
	else
	{
		x = month + 1;
		y = year;
	}
	for(int i = 0 ; i < 7 ;i++)
	{
		if(sday <= Date :: daysInMonth[month])
		{
			cout << setw(17) << right;
			getSecondTaskNotificationOnDate(Date(sday++,month,year));
		}
		else
		{
			cout << setw(17) << right;
			getSecondTaskNotificationOnDate(Date(k++,x,y));
		}
	}
}

int Calendar ::displayFifthAndSixthWeekOfMothInMonthlyCalendar(int sday, int month)
{
	int k = 1, count = 0, count2 = 0, x = 0;
	int year = runningDate.getYear();

	while(x < 2)
	{
		helperOfFifthAndSixthWeekDAYDisplayInMonthlyCalendar(sday, month, year, k);

		cout << endl;
	
		printDecorateiveSpacesForWeek();

		cout << endl;

		helperOfFifthAndSixthWeekFirstTaskDisplayInMonthlyCalendar(sday, month, year, k);

		cout << endl;

		helperOfFifthAndSixthWeekSecondTaskNotificationDisplayInMonthlyCalendar(sday,month,year,k);

		cout << endl;

		sketchBottomLineForMonthlyCalendar();

		cout << endl;

		x++;
	}
	
	return 0;
}

void Calendar :: printDaysForWeekInMonthlyCalendar(int sday, int month)
{
	for(int i = 0 ; i < 7 ; i++)
	{
		if(sday == runningDate.getDay() || (sday == displayClock.getDay() && month == displayClock.getMonth() && runningDate.getYear() == displayClock.getYear()))
		{
			cout<< setw(15) << right;
			printColors(CString :: toCString(sday),colorForTheDay(sday, month,runningDate.getYear()));
			cout << " |";
			sday++;
		}
		else
		{
			if(i == 0 || i == 6)
			{
				cout<< setw(15) << right;
				printColors(CString :: toCString(sday),13);
				sday++;
				cout << " |";
			}
			else
				cout<< setw(15) << right << sday++  << " |";
		}
	}
}

void Calendar :: printDecorateiveSpacesForWeek()
{
	for(int i = 0 ; i < 7 ; i++)
		cout << setw(17) << right << "|";
}

void Calendar :: sketchBottomLineForMonthlyCalendar()
{
	for(int x = 0 ; x < 7 ; x++)
		cout << "----------------|";
}

void Calendar :: printFirWordsOfTaskNotificationsForWeek(int sday, int mon, int year)
{
	for(int i = 0 ; i < 7 ; i++)
	{
		cout << setw(16) << right;
		getFirstWordsOfTaskOnDate(Date(sday,mon,year));
		cout << '|';
		sday ++;
	}
}

void Calendar :: printSecondTaskNotificationsForWeek(int sday, int mon, int year)
{
	for(int i = 0 ; i < 7 ; i++)
	{
		cout << setw(17) << right;
		getSecondTaskNotificationOnDate(Date(sday,mon,year));
		sday ++;
	}
}

int Calendar :: displaySecondWeekOfMothInYearlyCalendar(int sday, int mon)
{
	displayingWeekDays(sday, sday+7, mon);
	return sday + 7;
}

int Calendar :: displayThirdWeekOfMothInYearlyCalendar(int sday, int mon)
{
	displayingWeekDays(sday, sday+7, mon);
	return sday + 7;
}

int Calendar :: displayForthWeekOfMothInYearlyCalendar(int sday, int mon)
{
	displayingWeekDays(sday,sday+7,mon);
	
	return sday + 7;
}


void Calendar :: printCursorOrRunningDate(int i, int mon, int year)
{
	cout << setw(5);
	printColors(CString :: toCString(i),colorForTheDay(i, mon, year));
}

int Calendar ::  displayingWeekDays(int sday, int x, int mon)
{
	int i = 0;
	for(i ; i < 7 && sday <= x ; i++)
	{
		if((sday == runningDate.getDay() && mon == runningDate.getMonth()) || (sday == displayClock.getDay() && mon == displayClock.getMonth()))
		{
			printCursorOrRunningDate(sday,mon,runningDate.getYear());
			sday++;
		}
		else if((schedule.doesTaskExistOfType(Date(sday,mon,runningDate.getYear()),1) != -1) || (schedule.doesTaskExistOfType(Date(sday,mon,runningDate.getYear()),0) != -1))
		{
			cout << setw(5);
			printColors(CString :: toCString(sday),14);
			sday++;
		}
		else
		{
			if(i == 0 || i == 6)
			{
				cout << setw(5);
				printColors(CString :: toCString(sday), 13);
				sday++;
			}
			else
				cout << setw(5) << sday++;
		}
	}
	return i;
}

int Calendar :: displayFifthWeekOfMothInYearlyCalendar(int sday, int mon)
{
	int i = 0 , x;
	if(mon == 2 && isLeapYear(runningDate.getYear()) == true)
		x = 29;
	else
		x = Date :: daysInMonth[mon];

	i = displayingWeekDays(sday, x, mon);

	if(i < 7)
	{
		int j = 1;
		while(i < 7)
		{
			cout << setw(5);
			printColors(CString :: toCString(j),1);
			j++;
			i++;
		}
		return j;
	}
	return sday + 7;
}

int Calendar :: displaySixthWeekOfMothInYearlyCalendar(int sday, int mon)
{
	int i = 0;
	if(sday > 10)
	{
		int x;
		if(mon == 2 && isLeapYear(runningDate.getYear()) == true)
			x = 29;
		else
			x = Date :: daysInMonth[mon];

		for(i; i < 7 && sday <= x ; i++)
		{
			if((sday == runningDate.getDay() && mon == runningDate.getMonth()) || (sday == displayClock.getDay() && mon == displayClock.getMonth()))
			{
				cout << setw(5);
				printColors(CString :: toCString(sday),colorForTheDay(sday, mon,runningDate.getYear()));
				sday++;
			}
			else
			{
				if(i == 0 || i == 6)
				{
					cout << setw(5);
					printColors(CString :: toCString(sday), 13);
					sday++;
				}
				else
					cout << setw(5) << sday++;
			}
		}

		if(i < 7)
		{
			int j = 1;
			while(i < 7)
			{
				cout << setw(5);
				printColors(CString :: toCString(j), 1);
				j++;
				i++;
			}
			return j;
		}
		return sday;
	}
	else
	{
		for(i ; i < 7 ; i++)
		{
			cout << setw(5);
			printColors(CString :: toCString(sday),1);
			sday++;
		}
		return sday;
	}
}

void Calendar :: displaying1stWeekofConsecutive3Months(int i, bool doJob, int* temp)
{
	while(doJob)
	{
		temp[i] = displayFirstWeekOfMothInYearlyCalendar(i);
		if(i % 3 == 0)
			doJob = 0;
		i++;
	}
}

void Calendar :: displaying2ndWeekofConsecutive3Months(int i, bool doJob, int* temp)
{
	while(doJob)
	{
		cout << "     ";
		temp[i] = displaySecondWeekOfMothInYearlyCalendar(temp[i],i);
		if(i % 3 == 0)
			doJob = 0;
		i++;
	}
}

void Calendar :: displaying3rdWeekofConsecutive3Months(int i, bool doJob, int* temp)
{
	while(doJob)
	{
		cout << "     ";
		temp[i] = displayThirdWeekOfMothInYearlyCalendar(temp[i],i);
		if(i % 3 == 0)
			doJob = 0;
		i++;
	}
}

void Calendar :: displaying4thWeekofConsecutive3Months(int i, bool doJob, int* temp)
{
	while(doJob)
	{
		cout << "     ";
		temp[i] = displayForthWeekOfMothInYearlyCalendar(temp[i],i);
		if(i % 3 == 0)
			doJob = 0;
		i++;
	}
}

void Calendar :: displaying5thWeekofConsecutive3Months(int i, bool doJob, int* temp)
{
	while(doJob)
	{
		cout << "     ";
		temp[i] = displayFifthWeekOfMothInYearlyCalendar(temp[i],i);
		if(i % 3 == 0)
			doJob = 0;
		i++;
	}
}

void Calendar :: displaying6thWeekofConsecutive3Months(int i, bool doJob, int* temp)
{
	while(doJob)
	{
		cout << "     ";
		temp[i] = displaySixthWeekOfMothInYearlyCalendar(temp[i],i);
		if(i % 3 == 0)
			doJob = 0;
		i++;
	}
}

void Calendar ::  displayingMonthsInParticularYear(int i, bool doJob, int * temp)
{
		for(int k = 0 ; k < 3 ; k++)
		{
			cout << setw(40) << right ;
			printColors("      S    M    T    W    T    F    S",13);
		}
		cout << endl;

		i -= 2;

		displaying1stWeekofConsecutive3Months(i, doJob, temp);

		cout << endl;

		displaying2ndWeekofConsecutive3Months(i, doJob, temp);

		cout << endl;

		displaying3rdWeekofConsecutive3Months(i, doJob, temp);

		cout << endl;

		displaying4thWeekofConsecutive3Months(i, doJob, temp);

		cout << endl;

		displaying5thWeekofConsecutive3Months(i, doJob, temp);

		cout << endl;
		
		displaying6thWeekofConsecutive3Months(i, doJob, temp);
}

void Calendar :: checkIncomingYear(int year)
{
	if(year != 0)
	{
		if(year >= 1900 && year <= 2099)
			runningDate.setYear(year);
	}
}

void Calendar :: checkIncomingMonth(int & month)
{
	if(month != 0)
	{
		if(month >= 1 && month <= 12)
			runningDate.setMonth(month);
	}
	else
	{
		month = runningDate.getMonth();
	}
}

void Calendar :: showWholeYearCalendar(int year)
{
	system("mode 158");
	system("color F0");

	refreshClock();

	bool doJob = 1;
	int temp[13];

	checkIncomingYear(year);

	displayClock.displayClock();

	cout << endl;

	displayRunningActivity();

	cout << "\n\n\t\t\t\t\t\t\t   Year - " << runningDate.getYear() << "\n\n";
	
	for(int i = 1 ; i < 13 ; i++)
	{
		cout << setw(40) << right;
		printColors(Date :: returnMonth(i));
		if(i % 3 == 0)
		{
			cout << endl;
			
			displayingMonthsInParticularYear(i, doJob, temp);

			cout << endl << endl;
		}
	}
}


void Calendar ::showWholeMonthlyCalendar(int mon)
{
	system("mode 158");
	system("color F0");

	refreshClock();

	checkIncomingMonth(mon);

	displayClock.displayClock();

	cout << endl;

	displayRunningActivity();

	cout << "\n\n\t\t\t\t\t\t\t   " << Date :: returnMonth(runningDate.getMonth()) << " - " <<runningDate.getYear() << '\n';

	cout << "\n";
	printColors("           Sunday",13);
	cout << "           Monday          Tuesday        Wednesday         Thursday           Friday";
	printColors("         Saturday",13);
	cout << "\n";

	sketchBottomLineForMonthlyCalendar();
	cout << endl;
	
	displayFifthAndSixthWeekOfMothInMonthlyCalendar(displaySecondWeekToThirdOfMothInMonthlyCalendar(displayFirstWeekOfMothInMonthlyCalendar(mon),mon),mon);
}

CString Calendar :: returnWeekDay(int dayNumber)
{
	switch(dayNumber)
	{
	case 0:
		return "Sun";
		break;
	case 1:
		return "Mon";
		break;
	case 2:
		return "Tues";
		break;
	case 3:
		return "Wed";
		break;
	case 4:
		return "Thurs";
		break;
	case 5:
		return "Fri";
		break;
	case 6:
		return "Sat";
		break;
	}
}

CString Calendar :: returnFullWeekDay(int dayNumber)
{
	switch(dayNumber)
	{
	case 0:
		return "Sunday";
		break;
	case 1:
		return "Monday";
		break;
	case 2:
		return "Tuesday";
		break;
	case 3:
		return "Wednesday";
		break;
	case 4:
		return "Thursday";
		break;
	case 5:
		return "Friday";
		break;
	case 6:
		return "Saturday";
		break;
	}
}

void Calendar :: checkTheStartingDate(int & sDay, int mon)
{
	if(sDay == 0)
	{
		if(mon == 1)
			sDay = 31;
		if(mon == 3 && isLeapYear(runningDate.getYear()) == true)
			sDay = 29;
		else
			sDay = Date ::daysInMonth[mon - 1];
	}
	if(sDay < 0)
	{
		if(mon == 1)
			sDay = 31 + sDay;
		if(mon == 3 && isLeapYear(runningDate.getYear()) == true)
			sDay = 29 + sDay;
		else
			sDay = Date ::daysInMonth[mon - 1] + sDay;
	}
}

int Calendar :: getStartingDayOfWeek()
{
	int day = runningDate.getWDay();
	int count = 0 ;
	int mon = runningDate.getMonth();
	int presentDay = runningDate.getDay();
	
	while(day != 0)
	{
		day --;
		count++;
	}

	int sDay = presentDay;
	sDay -= count;

	checkTheStartingDate(sDay, mon);

	return sDay;
}

void Calendar :: printWeekForStartingDateGreaterThanPresentDate(int sDay, int mon)
{
	int k = 0;
	int d = 1;
	int y;
	
	if(mon == 1)
		y = 31;
	if(mon == 3 && isLeapYear(runningDate.getYear()) == true)
		y = 29;
	else
		y = Date :: daysInMonth[mon -1];

	cout << "             |";

	while(sDay <= y)
	{
		cout << setw(13);
		printColors(returnWeekDay(k++),1);
		cout << " " ;
		printColors(CString :: toCString(sDay++), 1);
	}

	while(k < 7)
	{
		if((d == runningDate.getDay() && mon == runningDate.getMonth()) || (k == displayClock.getDay() && mon == displayClock.getMonth()))
		{
			cout << setw(13);
			printColors(returnWeekDay(k), colorForTheDayInWeek(d, mon,runningDate.getYear()));
			printColors(CString :: toCString(d), colorForTheDayInWeek(d , mon, runningDate.getYear()));
			cout << " ";
			k++; 
			d++;
		}
		else
			cout << setw(14) << returnWeekDay(k++) << " "  << d++;
	}

}

void Calendar :: printWeekForStartingDateGreaterThan25(int sDay, int mon)
{
	int k = 0;
	int d = 1;
	int y;
	
	if(mon == 2 && isLeapYear(runningDate.getYear()) == true)
		y = 29;
	else
		y = Date :: daysInMonth[mon];

	cout << "             |";

	while(sDay <= y)
	{
		cout << setw(13);
		printColors(returnWeekDay(k++), colorForTheDayInWeek(sDay, mon,runningDate.getYear()));
		cout << " ";
		printColors(CString :: toCString(sDay), colorForTheDayInWeek(sDay, mon,runningDate.getYear()));
		sDay++;
	}

	while(k < 7)
	{
		cout << setw(13);
		printColors(returnWeekDay(k++),1);
		cout << " ";
		printColors(CString :: toCString(d++),1);
	}

}

void Calendar :: printSimpleWeek(int sDay, int month)
{
	int k = 0;

	cout << "             |";

	while(k < 7)
	{
		if((sDay == runningDate.getDay() && month == runningDate.getMonth()) || (sDay == displayClock.getDay() && month == displayClock.getMonth()))
		{
			cout << setw(13);
			printColors(returnWeekDay(k),colorForTheDayInWeek(sDay, month,runningDate.getYear()));
			cout << " ";
			printColors(CString :: toCString(sDay), colorForTheDayInWeek(sDay, month,runningDate.getYear()));
			k++;
			sDay++;
		}
		else
			cout << setw(13) << returnWeekDay(k++) << " " << sDay++;
	}
}

void Calendar :: displayWeekHeading(int sDay, int mon)
{
	if(sDay > runningDate.getDay())
		printWeekForStartingDateGreaterThanPresentDate(sDay,mon);
	else if(sDay > 25)
		printWeekForStartingDateGreaterThan25(sDay, mon);
	else
		printSimpleWeek(sDay, mon);
}

void Calendar :: checkMonthLimitMonthAndYearForDateGreaterThanPresentDate(int mon, int year, int & monthLimit, int & prevMonth, int & yearOfPreviousMonth)
{
	if(mon == 1)
	{
		prevMonth = 12;
		monthLimit = 31;
		yearOfPreviousMonth = year -1;
	}
	if(mon == 3 && isLeapYear(runningDate.getYear()) == true)
	{
		prevMonth = 2;
		monthLimit = 29;
		yearOfPreviousMonth = year;
	}
	else
	{
		prevMonth = mon - 1;
		monthLimit = Date :: daysInMonth[mon -1];
		yearOfPreviousMonth = year;
	}
}

void Calendar :: printTasksForWeekWhenStartingDateGreaterThanPresentDate(int sDay, int mon, int year)
{
	int k = 1;
	int temp = sDay;
	
	int monthLimit;
	int prevMonth;
	int yearOfPreviousMonth;

	checkMonthLimitMonthAndYearForDateGreaterThanPresentDate(mon, year, monthLimit, prevMonth, yearOfPreviousMonth);

	int hourCount = -1;

	while(hourCount < 24)
	{
		printSideTimeBar(hourCount);
		if(hourCount == -1)
		{
			for(int i = 0 ; i < 7 ; i++)
			{
				if(sDay <= monthLimit)
				{
					cout << setw(19);
					getFirstWordsOfAllDayTaskForWeeklyCalendar(Date(sDay++, prevMonth, yearOfPreviousMonth));
					cout << '|';
				}
				else
				{
					cout << setw(19);
					getFirstWordsOfAllDayTaskForWeeklyCalendar(Date(k++, mon, year));
					cout << '|';
				}
			}
			sDay = temp;
			cout << endl;
		}
		else
		{
			for(int i = 0 ; i < 7 ; i++)
			{
				if(sDay <= monthLimit)
				{
					cout << setw(19);
					getFirstWordsOfTaskOnDateOnHour(Date(sDay++, prevMonth, yearOfPreviousMonth), hourCount);
					cout << '|';
				}
				else
				{
					cout << setw(19);
					getFirstWordsOfTaskOnDateOnHour(Date(k++, mon, year), hourCount);
						cout << '|';
				}
			}
			sDay = temp;
			k = 1;
			cout << endl;
		}
		hourCount++;
	}

}

void Calendar :: checkMonthLimitMonthAndYearForDateGreaterThan25(int mon, int year, int & monthLimit, int & nextMonth, int & yearOfNextMonth)
{
	if(mon == 12)
	{
		nextMonth = 1;
		monthLimit = 31;
		yearOfNextMonth = year + 1;
	}
	if(mon == 2 && isLeapYear(runningDate.getYear()) == true)
	{
		nextMonth = 3;
		monthLimit = 29;
		yearOfNextMonth = year;
	}
	else
	{
		nextMonth = mon + 1;
		monthLimit = Date :: daysInMonth[mon];
		yearOfNextMonth = year;
	}
}

void Calendar :: printTasksForWeekWhenStartingDateGreaterThan25(int sDay, int mon, int year)
{
	int k = 1;
	int temp = sDay;
	int monthLimit;
	int nextMonth;
	int yearOfNextMonth;
	
	checkMonthLimitMonthAndYearForDateGreaterThan25(mon, year, monthLimit, nextMonth, yearOfNextMonth);
	
	int hourCount = -1;

	while(hourCount < 24)
	{
		printSideTimeBar(hourCount);
		if(hourCount == -1)
		{
			for(int i = 0 ; i < 7 ; i++)
			{
				if(sDay <= monthLimit)
				{
					cout << setw(19);
					getFirstWordsOfAllDayTaskForWeeklyCalendar(Date(sDay++, mon, year));
					cout << '|';
				}
				else
				{
					cout << setw(19);
					getFirstWordsOfAllDayTaskForWeeklyCalendar(Date(k++, nextMonth, yearOfNextMonth));
					cout << '|';
				}
			}
			sDay = temp;
		}
		else
		{
			for(int i = 0 ; i < 7 ; i++)
			{
				if(sDay <= monthLimit)
				{
					cout << setw(19);
					getFirstWordsOfTaskOnDateOnHour(Date(sDay++, mon, year), hourCount);
					cout << '|';
				}
				else
				{
					cout << setw(19);
					getFirstWordsOfTaskOnDateOnHour(Date(k++, nextMonth, yearOfNextMonth), hourCount);
					cout << '|';
				}
			}
		}
		sDay = temp;
		k = 1;

		hourCount++;
		cout << endl;
	}
}

void Calendar :: printSideTimeBar(int hourCount)
{
	int temp = hourCount % 12;
	if(temp == 0)
		temp = 12;
	if(hourCount == -1)
	{
		if(runningDate.getHour() != -1)
			cout << "   All day   ";
		else
			printColors("   All day   ");
		cout <<'|';
		return;
	}
	if(hourCount == runningDate.getHour())
	{
		cout << setw(7);
		printColors(CString :: toCString(temp));
		if(hourCount >= 12)
			printColors(" pm   ");
		else
			printColors(" am   ");
		cout << '|';
	}
	else
	{
		if(hourCount >= 12)
			cout << setw(7) << temp << " pm   |";
		else
			cout << setw(7) << temp << " am   |";
	}
}

void Calendar :: printTasksForSimpleWeek(int sDay, int month, int year)
{
	int hourCount = -1;
	int k = 0;
	int temp = sDay;

	while(hourCount < 24)
	{
		printSideTimeBar(hourCount);
		if(hourCount == -1)
		{
			for(int i = 0 ; i < 7 ; i++)
			{
				cout << setw(19);
				getFirstWordsOfAllDayTaskForWeeklyCalendar(Date(sDay++, month, year));
				cout << '|';
			}
			sDay = temp;
		}
		else
		{
			while(k < 7)
			{
				cout << setw(19);
				getFirstWordsOfTaskOnDateOnHour(Date(sDay++, month, year), hourCount);
				cout << '|';
				k++;
			}

			k = 0;
			sDay = temp;
		}
		hourCount++;
		cout << endl;
	}
}

void Calendar :: displayTasksForWeek(int sDay, int mon)
{
	if(sDay > runningDate.getDay())
		printTasksForWeekWhenStartingDateGreaterThanPresentDate(sDay, mon, runningDate.getYear());
	else if(sDay > 25)
		printTasksForWeekWhenStartingDateGreaterThan25(sDay, mon, runningDate.getYear());
	else
		printTasksForSimpleWeek(sDay, mon, runningDate.getYear());
}

void Calendar :: showWholeWeeklyCalendar()
{
	system("mode 158");
	system("color F0");

	refreshClock();

	displayClock.displayClock();

	cout << endl;

	displayRunningActivity();

	cout << setw(60) << Date :: returnMonth(runningDate.getMonth()) << " - " << runningDate.getYear() << endl;

	int startigDate = getStartingDayOfWeek();
	int month = runningDate.getMonth();

	displayWeekHeading(startigDate, month);

	cout << endl;

	displayTasksForWeek(startigDate, month);
	cout << endl;
}

void Calendar ::showWholeDailyCalendar()
{
	system("mode 158");
	system("color F0");

	refreshClock();

	displayClock.displayClock();

	cout << endl;

	displayRunningActivity();

	cout << setw(20) << runningDate.getDay() << " " << Date :: returnMonth(runningDate.getMonth()) << " " << runningDate.getYear() << endl;

	cout << '\n' << returnFullWeekDay(runningDate.getWDay()) << "\n\n";
	
	displayDayTaskinDailyCalendar(Date(runningDate.getDay(), runningDate.getMonth(), runningDate.getYear()));
}

int Calendar ::  printWeeklySegments(int x, int i, int mon)
{
	cout << "  ";
	if(i == 1)
	{
		cout << "   ";
		return displayFirstWeekOfMothInYearlyCalendar(mon,1);
	}
	if(i == 2)
		return displaySecondWeekOfMothInYearlyCalendar(x,mon);
	if(i == 3)
		return displayThirdWeekOfMothInYearlyCalendar(x,mon);
	if(i == 4)
		return displayForthWeekOfMothInYearlyCalendar(x,mon);
	if(i == 5)
		return displayFifthWeekOfMothInYearlyCalendar(x,mon);
	if(i == 6)
		return displaySixthWeekOfMothInYearlyCalendar(x,mon);
	else
	{}
}

void Calendar :: displayDayTaskinDailyCalendar(Date & d)
{
	int hourCount = -1;
	int temp = 0;
	bool status = 1;
	int j = 1;

	while(hourCount <= 23)
	{
		printSideTimeBar(hourCount);
		if(hourCount == -1)
		{
			std :: cout << setw(40);
			getFirstWordsOfAllDayTask(d);
			std :: cout << '|';
			std :: cout << endl << setw(14) << '|' << setw(40);
			getFirstWordsOfTask2OfAllDayTask(d);
			std :: cout << '|';

			hourCount++;
		}
		else
		{
			std :: cout << setw(40);
			getFirstWordsOfTask1OnDateOnHourForDailyCalendar(d, hourCount); 
			std :: cout << '|';

			if(status)
			{
				printColors("      S    M    T    W    T    F    S");
				status = 0;
			}
			
			cout  << endl << setw(14) << '|' << setw(40);
			getFirstWordsOfTask2OnDateOnHourForDailyCalendar(d,hourCount);
			cout << '|';
			temp = printWeeklySegments(temp, j++, runningDate.getMonth());
			

			hourCount++;
		}
		std :: cout << endl;
		
	}
}

void Calendar :: incrementHour(int hour)
{
	int temp = runningDate.getHour();
	runningDate.incHour(hour);

	if(runningDate.getHour() < temp)
	{
		runningDate.incDay();
		runningDate.setTime(0,runningDate.getMinute(),runningDate.getSecond());
		runningDate.incHour(-1);
	}
}

void Calendar :: decrementHour()
{
	int temp = runningDate.getHour();
	runningDate.incHour(-1);
	if(runningDate.getHour() < -1)
	{
		runningDate.incDay(-1);
		runningDate.setTime(23,runningDate.getMinute(),runningDate.getSecond());
	}
}

void Calendar :: incrementDay(int day)
{
	runningDate.incDay(day);
}

void Calendar :: deleteDayTaskAtRunningHour()
{
	system("mode 158");
	system("color F0");

	refreshClock();
	displayClock.displayClock();

	std :: cout << "\n\n";
	int ind;
	bool stats;


	if(runningDate.getHour() == -1)
	{
		ind =  schedule.numberOfType1TasksOnDate(runningDate.getDate());

		if(ind == 0)
		{
			cout << "There are no All day tasks Scheduled for ";
			runningDate.getDate().getDateInFormat2().display();
			cout << endl;
		}
		else
		{
			cout << "You're going to delete Type1 task, the task will not be displayed in future.\n";
			stats = schedule.removeTaskOnDateAndTimeOfType1(runningDate.getDate());
			if(stats)
				cout << "Task has been successfully removed. Press Backspace to return";
			else
				cout << "Task has not been successfully removed. Press Backspace to return";
		}
	}
	else
	{
		ind = schedule.numberOfType0TasksOnDateAndHour(runningDate.getDate(), runningDate.getHour());
		
		if(ind == 0)
		{
			cout << "No Task is scheduled for ";
			runningDate.getDate().printFormat2();
			cout <<" from " << runningDate.getHour() << " : 00 to "<< runningDate.getHour() << " : 59";
		}
		else
		{
			stats = schedule.removeTaskOnDateAndTimeOfType0(runningDate.getDate(),runningDate.getHour());
			if(stats)
				cout << "Task has been successfully removed. Press Backspace to return";
			else
				cout << "Task has not been successfully removed. Press Backspace to return";
		}
	}
		
}

void Calendar :: openDayTaskAtRunningHour()
{
	system("mode 158");
	system("color F0");

	refreshClock();
	displayClock.displayClock();

	std :: cout << "\n\n";
	int ind;
	if(runningDate.getHour() == -1)
	{
		ind = schedule.numberOfType1TasksOnDate(runningDate.getDate());
		if(ind == 0)
		{
			cout << "No Birthday, Anniversary or Annual Day scheduled for ";
			runningDate.getDate().getDateInFormat2().display();
		}
		else
		{
			schedule.displayType1TaskOnDate(runningDate.getDate());
		}
	}
	else
	{
		ind = schedule.doesTaskExistOnHour(runningDate.getDate(), runningDate.getHour());
		if(ind == -1)
		{
			cout << "No Task is scheduled for ";
			runningDate.getDate().printFormat2();
			cout <<" from " << runningDate.getHour() << " : 00 to "<< runningDate.getHour() << " : 59";
		}
		else
			schedule.displayTaskOnDateAndHour(runningDate.getDate(), runningDate.getHour());
	}
	
	std :: cout << std :: endl;
}

CString Calendar :: prepareBirthdayDisplay(CString & tsk, int index)
{
	CString name = tsk.tokenize("'");
	name.concatEqual(" turns ");
	
	int age = displayClock.getYear() - schedule.returnYearOfType1TaskAtIndex(index);

	name.concatEqual(CString :: toCString(age));
	name.concatEqual(" today");
	return name;
}

CString Calendar :: prepareAnniversaryDisplay(CString & tsk, int index)
{
	CString name("Today is ");
	int age = displayClock.getYear() - schedule.returnYearOfType1TaskAtIndex(index);

	name.concatEqual(CString :: toCString(age));
	int check = age % 10;

	if(age == 11 || age == 12 || age == 13)
		name.concatEqual("th ");
	else
	{
		if(check == 1)
			name.concatEqual("st ");
		if(check == 2)
			name.concatEqual("nd ");
		if(check == 3)
			name.concatEqual("rd ");
		if(check == 0 || check > 3)
			name.concatEqual("th ");
	}

	if(tsk.isSubString(" death") || tsk.isSubString(" Death"))
		name.concatEqual("Death ");
	if(tsk.isSubString(" Wedding") || tsk.isSubString(" wedding"))
		name.concatEqual("Wedding ");
	if(tsk.isSubString(" Engagement") || tsk.isSubString(" engagement"))
		name.concatEqual("Engagement ");

	name.concatEqual("Anniversay of ");

	name.concatEqual(tsk.tokenize("'"));

	return name;

}

CString Calendar :: prepareAnnualDayDisplay(CString & tsk, int index)
{
	CString name("Today is ");
	int age = displayClock.getYear() - schedule.returnYearOfType1TaskAtIndex(index);

	name.concatEqual(CString :: toCString(age));
	int check = age % 10;

	if(age == 11 || age == 12 || age == 13)
		name.concatEqual("th ");
	else
	{
		if(check == 1)
			name.concatEqual("st ");
		if(check == 2)
			name.concatEqual("nd ");
		if(check == 3)
			name.concatEqual("rd ");
		if(check == 0 || check > 3)
			name.concatEqual("th ");
	}

	name.concatEqual(tsk);
	return name;
}

CString Calendar :: prepareDisplayForRunningTask(int index, bool type)
{
	if(type == 1)
	{
		CString tsk = schedule.getMessageOfTaskAtIndex(index);

		if(tsk.isSubString("Birthday"))
			return prepareBirthdayDisplay(tsk, index);
		if(tsk.isSubString(" Day"))
			return prepareAnnualDayDisplay(tsk, index);
		if(tsk.isSubString("Anniversary"))
			return prepareAnniversaryDisplay(tsk, index);
		return tsk;
	}
	else
	{
		CString tsk = schedule.getMessageOfTaskAtIndex(index);
		if(tsk.isSubString(" class ") || tsk.isSubString(" meet "))
			return returnClassOrMeetingDisplay(tsk,index);
		return returnEvent(tsk,index);
	}
}

CString Calendar :: returnEvent(CString cs, int ind)
{
	cs.concatEqual(CString :: toCString(schedule.getTimeOfTaskAtIndex(ind).getHour()));
	cs.concatEqual(" : ");
	cs.concatEqual(CString :: toCString(schedule.getTimeOfTaskAtIndex(ind).getMinute()));
	return cs;
}

CString Calendar :: returnClassOrMeetingDisplay(CString & cs, int ind)
{
	cs.tokenize("'");
	CString you("You'");
	you.concatEqual(cs);

	you.concatEqual(" at ");
	you.concatEqual(CString :: toCString(schedule.getTimeOfTaskAtIndex(ind).getHour()));
	you.concatEqual(" : ");
	you.concatEqual(CString :: toCString(schedule.getTimeOfTaskAtIndex(ind).getMinute()));

	return you;
}

void Calendar :: displayRunningActivity()
{
	cout << " Current Activity : ";

	int ind = schedule.doesTaskExistOfType(displayClock.getDate(),1);
	int ind2 = schedule.doesTaskExistOnHour(displayClock.getDate(), displayClock.getTime().getHour());

	CString displ;

	if((ind == -1 && ind2 != -1) || (ind != -1 && ind2 != -1))
		displ = prepareDisplayForRunningTask(ind2, 0);
	if(ind != -1 && ind2 == -1)
		displ = prepareDisplayForRunningTask(ind,1);
	if(ind == -1 && ind2 == -1)
		displ = "No task for you uptil now";

	printColors(displ);

	cout << endl;
}

void Calendar:: functionF1()
{
	system("color F0");
	system("mode 158");

	refreshClock();

	displayClock.displayClock();

	cout << endl;

	displayRunningActivity();

	cout << endl;

	cout << "\n\t\t\t\tThis is Help Menu for Calendar Application, here you'll find the information \n\t\t\t\t\trelating to keys, which will be used in Calendar Application";
	cout << "\n\n\n Keys                Functionality\n\n";
	printColors(" < > ");
	cout << "...........Right and Left Arrow keys for changing Days in all Calendar Views\n\n";
	printColors(" ^ v ");
	cout << "...........Up and Down Arrow keys for changing week in Year and Monthly Calendar\n\t\tIn Day and Week view, these keys are used to change Time\n\n";
	printColors(" Tab ->| ");
	cout << ".......Tab key is for displaying next Year/Month/Week display\n\n";
	printColors(" SpaceBar ");
	cout << "......Space Bar for displaying previous Year/Month/Week display\n\n";
	printColors(" Backspace ");
	cout << "......Backspace for return to previous Calendar View\n\n";
	printColors(" Pg Up ");
	cout << ".........Page Up key is for displaying next Year/Month/Week display\n\n";
	printColors(" Pg Dn ");
	cout << ".........Page Down key is for displaying previous Year/Month/Week display\n\n";
	printColors(" Enter ");
	cout << ".........Entering key is for Entering from Year to Month, from Month to Day, \n\t\tfrom Week to Day, and from Day to current Time.\n\n";
	printColors(" Del/ Delete ");
	cout << "...Delete Key is used for entering deletion menu of task on current Day\n\n";
	printColors(" Insert ");
	cout << "........Insert Key is used for New Task on Date \n\n";
	printColors(" Esc ");
	cout << "...........Esc(Escape) Key for Exiting Application\n\n";
	printColors(" F9 ");
	cout << "............Function-9 key for Clock settings\n\n";
	printColors(" F2 ");
	cout << "............Function-2 key for Quotation List Editing\n\n";
	printColors(" F3 ");
	cout << "............Function-3 key for Tasks Editing\n\n";
	cout << "  Press Backspace for returning";
}

void Calendar :: setTime(int hr, int min, int sec)
{
	displayClock.setTime(hr,min,sec);
}

void Calendar :: setDate(int day, int month, int year)
{
	Date something(day, month, year);
	Date anotherThing(displayClock.getDate());

	if(something < anotherThing)
	{
		while(!(displayClock.getDate() == something))
			displayClock.incDay(-1);
	}
	if(something > anotherThing)
	{
		while(!(displayClock.getDate() == something))
			displayClock.incDay();
	}

	runningDate.setDate(day,month,year);
}

Date Calendar :: getDate()
{
	return displayClock.getDate();
}

Time Calendar :: getTime()
{
	return displayClock.getTime();
}


void Calendar :: insertType1BirthdayTask()
{
	cout << "\n\tJust write name of person in first field and Year of Birth in Second field\n";
	CString name;
	int y;
	cout  << '\n' << "Mr / Ms. ";
	cin >> name;

	cout << "Year (1900 -" << displayClock.getYear() << ") : ";
	cin >> y;
	cin.ignore();

	name.concatEqual("'s Birthday");

	schedule.addTask(Date(runningDate.getDay(),runningDate.getMonth(), y),Time(0,0,0),name,1);
}

void Calendar ::insertType1AnniversaryTask()
{
	CString name;
	CString type;
	
	cout << '\n' << "Mr / Ms. ";
	cin >> name;

	cout << "Anniversary Type (Wedding / Engagement / Death): ";
	cin >> type;

	name.concatEqual(' ');
	name.concatEqual("'s ");
	name.concatEqual(type);
	name.concatEqual(" Anniversary");

	int y;
	cout << "The Year of Wedding / Engagement / Death : ";
	cin >> y;
	cin.ignore();

	schedule.addTask(Date(runningDate.getDay(),runningDate.getMonth(),y),Time(0,0,0),name,1);
}

void Calendar ::insertType1AnnualDayTask()
{
	CString name;

	cout << "\n\t While entering the name of Annual Day, don't write Day with it\n\t Forexample; In Labour's Day, just write Labour, rest of the statement will be completed automatically\n\n";

	cout << "\nName of Day (don't write Day with it): ";
	cin >> name;

	if(!(name.isSubString(" Day") || name.isSubString(" day")))
	{
		name.concatEqual("'s Day");
	}

	schedule.addTask(Date(runningDate.getDay(),runningDate.getMonth(),runningDate.getYear()), Time(0,0,0), name, 1);
}

void Calendar :: insertType0ClassesTask()
{
	cout << "\n\t\tJust write name of Subject, in first field and minutes in second field\n";
	CString name;
	CString head("I've to take class of ");
	cout << '\n' << head;
	cin >> name;

	head.concatEqual(name);

	int h = runningDate.getHour(),
		m;

	cout << "at Hour " << h;
	cout << " at Minutes : ";
	cin  >> m;
	cin.ignore();

	schedule.addTask(Date(runningDate.getDay(),runningDate.getMonth(),runningDate.getYear()), Time(h,m,0), head, 0);
}

void Calendar :: insertType0MeetingTask()
{
	CString name;
	CString location;
	cout << '\n';
	CString head("I've to meet ");
	cout << head;
	cin >> name;

	cout << "Location of meeting : ";
	cin >> location;

	head.concatEqual(name);
	head.concatEqual(" at ");
	head.concatEqual(location);

	int h = runningDate.getHour()
		,m;

	cout << "at Hour " << h;
	cout << " at Minute : ";
	cin >> m;

	cin.ignore();

	schedule.addTask(Date(runningDate.getDay(),runningDate.getMonth(),runningDate.getYear()),Time(h,m,0), head, 0);
}

void Calendar :: insertType0Event()
{
	CString name;
	CString location;
	cout << "Event Name : ";
	cin >> name;
	cout << "Venue / Location : ";
	cin >> location;
	
	name.concatEqual(" placing at ");
	name.concatEqual(location);

	int h = runningDate.getHour(),
		m;

	cout << "at Hour " << h;
	cout << " at Minute : ";
	cin >> m;
	cin.ignore();
	schedule.addTask(Date(runningDate.getDay(),runningDate.getMonth(),runningDate.getYear()), Time(h,m,0), name, 0);
}

void Calendar :: displayClocke()
{
	refreshClock();

	displayClock.displayClock();
}

void Calendar :: addQuotation()
{
	displayClock.addQuotation();
}

void Calendar ::removeQuotation()
{
	displayClock.removeQuotation();
}

void Calendar :: removeQuotationStringWise()
{
	CString str;
	cout << "Enter Word : ";
	cin >> str;

	displayClock.removeQuotationStringWise(str);
}

Task & Calendar :: updateTask(const bool type,int & status)
{
	return schedule.editTaskType(type,status);
}

void Calendar :: updateTaskMessage(Task & st, CString & msg)
{
	st.updateMessage(msg);
}

void Calendar :: updateTaskDate(Task & t, Date & d)
{
	t.updateDate(d);
}

void Calendar :: updateTaskTime(Task & tsk, Time & t)
{
	tsk.updateTime(t);
}

void Calendar :: updateTaskType(Task & tsk, bool type)
{
	tsk.updateTaskType(type);
}

void Calendar :: deleteTask()
{
	schedule.removeTaskGenerally();
}

Task & Calendar :: editTaskAtRunningTimeAndHour(int & status)
{
	return schedule.editTaskAtParticularDateAndTime(runningDate.getDate(),runningDate.getHour(), status);
}