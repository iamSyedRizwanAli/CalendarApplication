#ifndef CALENDAR_H	
#define CALENDAR_H
#include"SimpleClock.h"
#include"Clock.h"
#include"CString.h"
#include"Schedular.h"
#include"Date.h"
class Calendar
{
	Clock displayClock;
	SimpleClock runningDate;
	SimpleClock clockForComparison;
	Schedular schedule;
	int decade;

	static const int _REFERNCE_TO_2000[12];
	static const int _REFERNCE_TO_1900[12];
	
	void refreshClock();
	void refreshDate(int , int , int);
	void refreshTime(int , int , int);
	int getDecade();
	int getFirstDayOfMonth(int month);
	int firstDayOfMonthForDecade2000(int month);
	int firstDayOfMonthForDecade1900(int month);
	int helperForDecadeAndYear2000(int month);
	int helperForDecade2000(int month);
	int helperForDecade1900(int month);
	int helperForDecadeAndYear1900(int month);
	bool isLeapYear(int year);
	int previousMonthDay(int month, int &);
	void getFirstWordsOfTaskOnDate(Date & d);
	void getFirstWordsOfTask1OnDateOnHourForDailyCalendar(Date & d, int hour);
	void getFirstWordsOfTask2OnDateOnHourForDailyCalendar(Date & d, int hour);
	void getFirstWordsOfTaskOnDateOnHour(Date & d, int hour);
	void getSecondTaskNotificationOnDate(Date & d);
	void getSecondTaskNotificationOnDate(Date & d, Time & t);
	void getFirstWordsOfAllDayTask(Date & d);
	void getFirstWordsOfTask2OfAllDayTask(Date & d);
	void displaySmallString(int );
	void displayLargeString(int );
	CString returnWeekDay(int dayNumber);
	int colorForTheDay(int day, int month,int year);
	int colorForTheDayInWeek(int i, int month, int year);
	bool addTask(Date d, Time t, CString message, bool taskType);
	void displayRunningActivity();
	CString prepareDisplayForRunningTask(int index, bool type);
	CString prepareBirthdayDisplay(CString & tsk, int index);
	CString prepareAnniversaryDisplay(CString & tsk, int index);
	CString prepareAnnualDayDisplay(CString & tsk, int index);

	void checkIncomingYear(int year);
	int displayFirstWeekOfMothInYearlyCalendar(int month, int control = 0);
	int displaySecondWeekOfMothInYearlyCalendar(int day, int month);
	int displayThirdWeekOfMothInYearlyCalendar(int day, int month);
	int displayForthWeekOfMothInYearlyCalendar(int day, int month);
	int displayFifthWeekOfMothInYearlyCalendar(int day, int month);
	int displaySixthWeekOfMothInYearlyCalendar(int day, int month);
	void displaying1stWeekofConsecutive3Months(int i, bool doJob, int* temp);
	void displaying2ndWeekofConsecutive3Months(int i, bool doJob, int* temp);
	void displaying3rdWeekofConsecutive3Months(int i, bool doJob, int* temp);
	void displaying4thWeekofConsecutive3Months(int i, bool doJob, int* temp);
	void displaying5thWeekofConsecutive3Months(int i, bool doJob, int* temp);
	void displaying6thWeekofConsecutive3Months(int i, bool doJob, int* temp);
	void printDecorateiveSpacesForWeek();
	void printDaysForWeekInMonthlyCalendar(int sday, int month);
	void sketchBottomLineForMonthlyCalendar();
	void printFirWordsOfTaskNotificationsForWeek(int sday, int mon, int year);
	void printSecondTaskNotificationsForWeek(int sday, int mon, int year);
	void displayingMonthsInParticularYear(int month, bool status, int * temp);

	void checkIncomingMonth(int & month);
	int displayFirstWeekOfMothInMonthlyCalendar(int month);
	int displaySecondWeekToThirdOfMothInMonthlyCalendar(int day, int month);
	int displayFifthAndSixthWeekOfMothInMonthlyCalendar(int day, int month);
	void helperOfFifthAndSixthWeekFirstTaskDisplayInMonthlyCalendar(int day, int month, int year, int extraDay);
	void helperOfFifthAndSixthWeekDAYDisplayInMonthlyCalendar(int day, int month, int year, int extraDay);
	void helperOfFifthAndSixthWeekSecondTaskNotificationDisplayInMonthlyCalendar(int & day, int & month, int & year, int & extraDay);
	void helperForDisplayingDaysInFirstWeekOfMonthlyCalendar(int previousMonthDay, int presentMonth, int year);
	void helperForDisplayingFirstTaskInFirstWeekInMonthOfMonthlyCalendar(int previousMonthDays, int month, int year);
	int helperForDisplayingSecondtTaskNotificationInFirstWeekInMonthOfMonthlyCalendar(int previousMonthDays, int month, int year);

	int getStartingDayOfWeek();
	void checkTheStartingDate(int & sDay, int month);
	void displayWeekHeading(int startingDay, int month);
	void printWeekForStartingDateGreaterThanPresentDate(int sDay, int month);
	void printWeekForStartingDateGreaterThan25(int sDay, int month);
	void printSimpleWeek(int sDay, int month);
	void displayTasksForWeek(int sDay, int mon);
	void printTasksForWeekWhenStartingDateGreaterThanPresentDate(int sDay, int month, int year);
	void printTasksForWeekWhenStartingDateGreaterThan25(int sDay, int month, int year);
	void printTasksForSimpleWeek(int sDay, int month, int year);
	void checkMonthLimitMonthAndYearForDateGreaterThan25(int presentMonth, int presentYear, int & monthLimit, int & nextMonth, int & yearOfNextMonth);
	void checkMonthLimitMonthAndYearForDateGreaterThanPresentDate(int mon, int year, int & monthLimit, int & prevMonth, int & yearOfPreviousMonth);
	void printSideTimeBar(int hourCount);
	void getFirstWordsOfAllDayTaskForWeeklyCalendar(Date & d);
	int printWeeklySegments(int temp, int weekNumber, int month);
	CString returnClassOrMeetingDisplay(CString & cs, int ind);
	CString returnEvent(CString cs, int ind);

	void displayDayTaskinDailyCalendar(Date & d);
	int displayingWeekDays(int sday, int daysLimit, int month);
	void printCursorOrRunningDateFor1stWeek(int day, int month, int year);
	void printCursorOrRunningDate(int day, int month, int year);
public:
	Calendar();
	void printColors(CString msg, int type = 0);
	void showWholeYearCalendar(int year = 0);
	void showWholeMonthlyCalendar(int mon = 0);
	void showWholeWeeklyCalendar();
	void showWholeDailyCalendar();
	void incrementHour(int hour = 1);
	void incrementDay(int day = 1);
	void decrementHour();
	void openDayTaskAtRunningHour();
	void incrementYear(int val);
	void incrementMonth(int val);
	void incrementWeek(int val);
	void functionF1();
	void setTime(int hr, int min, int sec);
	void setDate(int day, int month, int year);
	Date getDate();
	Time getTime();
	void insertType1BirthdayTask();
	void insertType1AnniversaryTask();
	void insertType1AnnualDayTask();
	void insertType0ClassesTask();
	void insertType0MeetingTask();
	void insertType0Event();
	void displayClocke();
	void deleteDayTaskAtRunningHour();
	CString returnFullWeekDay(int dayNumber);
	void addQuotation();
	void removeQuotation();
	void removeQuotationStringWise();
	Task & updateTask(const bool type,int & status);
	void updateTaskTime(Task &, Time &);
	void updateTaskType(Task &, bool);
	void updateTaskMessage(Task &, CString &);
	void updateTaskDate(Task &, Date &);
	void deleteTask();
	Task & editTaskAtRunningTimeAndHour(int & status);
};
#endif