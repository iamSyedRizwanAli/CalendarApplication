#ifndef CALENDARAPPLICATION_H
#define CALENDARAPPLICATION_H
#include"Calendar.h"
class CalendarApplication
{
	static bool call;
	static bool option;
	static int option2;
	static SimpleClock clockForInputFromUser;
	static Calendar calendar;
	static char inputTimeSlot;
	static char inputDateSlot;
	static bool inputTimeAmOrPm;
	static bool callForTimeAmOrPm;
	static char functionF2selection;
	static char quoteRemovalSelection;
	static char functionF3selection;
	static char taskUpdationBeginningOptions;
	static char taskUpdationFinalOptions;

	static void wholeYearCalendarFunction();
	static void wholeWeekCalendarFunction();
	static void wholeDayCalendarFunction();
	static void wholeMonthlyCalendarFunction();
	static void taskDisplayAndEditingFunction();
	static void headOfTaskDisplayAndEditing();
	static void functionF9();
	static void functionF1();
	static void functionF2();
	static void removeQuotation();
	static void getDateFromUser();
	static void getTimeFromUser();
	static void insertTask();
	static void headForInsertTask();
	static void optionsPrintingForInsert();
	static void upperPartOfFunctionF9();

	static void headForGetDateFromUser();
	static void headForGetTimeFromUser();
	static int actualHourToInsertInPresentTime();
	static void headOfFunctonF2();
	static void headForRemoveQuotation();
	static void functionF3();
	static void headForFunctionF3();
	static void taskUpdation();
	static void headForTaskUpdation();
	static void updateType0Task();
	static void updateType1Task();
	static void optionsForUpdation(Task * t);
	static void headForOptionsForUpdation(Task * t);
	static void getDateFromUserForUpdationOfTask(Task * t);
	static void getTimeFromUserForUpdationOfTask(Task * t);
	static void getMessageFromUserToUpdate(Task * t);
	static void getTypeForTaskUpdation(Task * t);
	static void updateTaskAtDateAndHour();
public:
	static void startCalendarApplication();
};
#endif