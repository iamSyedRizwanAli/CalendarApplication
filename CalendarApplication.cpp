#include"CalendarApplication.h"
#include"Schedular.h"
#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<iostream>

Calendar CalendarApplication :: calendar;
bool CalendarApplication :: call = 0;
bool CalendarApplication :: option = 0;
int CalendarApplication :: option2 = 0;
SimpleClock CalendarApplication :: clockForInputFromUser;
char CalendarApplication :: inputTimeSlot = '1';
char CalendarApplication :: inputDateSlot = '1';
bool CalendarApplication :: inputTimeAmOrPm = 0;
char CalendarApplication :: functionF2selection = '1';
char CalendarApplication :: quoteRemovalSelection = '1';
char CalendarApplication :: functionF3selection = '1';
char CalendarApplication :: taskUpdationBeginningOptions = '1';
char CalendarApplication :: taskUpdationFinalOptions = '1';
bool CalendarApplication :: callForTimeAmOrPm = 1;

#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_ESCAPE 27
#define KB_ENTER 13
#define KB_BSPACE 8
#define KB_TAB 9
#define KB_HOME 71
#define KB_PGDOWN 81
#define KB_PGUP 73
#define KB_DEL 83
#define KB_INSERT 82
#define KB_F1 59
#define KB_F9 67
#define KB_F2 60
#define KB_F3 61
#define KB_SPACE 32

void CalendarApplication :: startCalendarApplication()
{
	wholeMonthlyCalendarFunction();
}

void CalendarApplication :: headOfFunctonF2()
{
	system("cls");

	std :: cout << "\n\tYou're in Quotations Editing window, select your option from below \n\n";

	if(functionF2selection == '1')
	{
		calendar.printColors("Add Quotation",9);
		std :: cout << "\nRemove Quotation\nReturn";
	}
	if(functionF2selection == '2')
	{
		std :: cout << "Add Quotation\n";
		calendar.printColors("Remove Quotation",9);
		std :: cout << "\nReturn";
	}
	if(functionF2selection == '3')
	{
		std :: cout << "Add Quotation\nRemove Quotation\n";
		calendar.printColors("Return",9);
	}
}

void CalendarApplication :: headForRemoveQuotation()
{
	system("cls");
	std :: cout << '\n';
	if(quoteRemovalSelection == '1')
	{
		calendar.printColors("Remove Quotation having a word",9);
		std :: cout << "\nRandomly remove quotation\nReturn";
	}
	if(quoteRemovalSelection == '2')
	{
		std :: cout << "Remove Quotation having a word\n";
		calendar.printColors("Randomly remove quotation",9);
		std :: cout << "\nReturn";
	}
	if(quoteRemovalSelection == '3')
	{
		std :: cout << "Remove Quotation having a word\nRandomly remove quotation\n";
		calendar.printColors("Return",9);
	}
}

void CalendarApplication :: removeQuotation()
{
	headForRemoveQuotation();

	int code = 0;

	while(code != KB_BSPACE)
	{
		if(_kbhit())
		{
			code = _getch();

			switch (code)
			{
			case KB_UP:
				{
					if(quoteRemovalSelection == '1')
						quoteRemovalSelection = '3';
					else
						quoteRemovalSelection -= 1;
					
					headForRemoveQuotation();
				}
				break;
			case KB_DOWN:
				{
					if(quoteRemovalSelection == '3')
						quoteRemovalSelection = '1';
					else
						quoteRemovalSelection += 1;

					headForRemoveQuotation();
				}
				break;
			case KB_ENTER:
				{
					std :: cout << std :: endl;
					switch(quoteRemovalSelection)
					{
					case '1':
						{
							calendar.removeQuotationStringWise();
							headForRemoveQuotation();
						}
						break;
					case '2':
						{
							calendar.removeQuotation();
							headForRemoveQuotation();
						}
						break;
					case '3':
						{
							code = KB_BSPACE;
							quoteRemovalSelection = '1';
						}
						break;
					}
				}
				break;
			case KB_BSPACE:
				quoteRemovalSelection = '1';
				break;
			}
		}
	}
}

void CalendarApplication :: functionF2()
{
	headOfFunctonF2();
	int code = 0;

	while(code != KB_BSPACE)
	{
		if(_kbhit())
		{
			code = _getch();

			switch(code)
			{
			case KB_UP:
				{
					if(functionF2selection == '1')
						functionF2selection = '3';
					else
						functionF2selection -= 1;
					headOfFunctonF2();
				}
				break;
			case KB_DOWN :
				{
					if(functionF2selection == '3')
						functionF2selection = '1';
					else
						functionF2selection += 1;
					headOfFunctonF2();
				}
				break;
			case KB_ENTER:
				{
					switch(functionF2selection)
					{
					case '1':
						calendar.addQuotation();
						break;
					case '2':
						removeQuotation();
						break;
					case '3':
						{
							code = KB_BSPACE;
							functionF2selection = '1';
						}
						break;
					}
					headOfFunctonF2();
				}
				break;
			case KB_BSPACE:
				functionF2selection = '1';
				break;
			}
		}
	}
}

void CalendarApplication :: wholeDayCalendarFunction()
{
	calendar.showWholeDailyCalendar();
	int KB_code = 0;
	while(KB_code != KB_BSPACE && KB_code != KB_ESCAPE)
	{
		if(_kbhit())
		{
			KB_code = _getch();
							
			switch(KB_code)
			{
			case KB_UP:
				{
					calendar.decrementHour();
					calendar.showWholeDailyCalendar();
				}
				break;
			case KB_DOWN:
				{
					calendar.incrementHour();
					calendar.showWholeDailyCalendar();
				}
				break;
			case KB_F2:
				{
					functionF2();
					calendar.showWholeDailyCalendar();
				}
				break;
			case KB_F3:
				{
					updateTaskAtDateAndHour();
					calendar.showWholeDailyCalendar();
				}
				break;
			case KB_RIGHT:
				{
					calendar.incrementDay();
					calendar.showWholeDailyCalendar();
				}
				break;
			case KB_LEFT:
				{
					calendar.incrementDay(-1);
					calendar.showWholeDailyCalendar();
				}
				break;
			case KB_BSPACE:
				{
					wholeWeekCalendarFunction();
				}
				break;
			case KB_ENTER:
				{
					taskDisplayAndEditingFunction();
					calendar.showWholeDailyCalendar();
				}
				break;
			case KB_F1:
				{
					functionF1();
					calendar.showWholeDailyCalendar();
				}
				break;
			case KB_F9:
				{
					functionF9();
					calendar.showWholeDailyCalendar();
				}
				break;
			case KB_INSERT:
				{
					insertTask();
					calendar.showWholeDailyCalendar();
				}
				break;
			}
		}
	}
	return;
}

void CalendarApplication :: optionsPrintingForInsert()
{
	if(option2 == 0)
	{
		calendar.printColors("Birthday",9);
		std :: cout << "\nAnniversary\nAnnual Day\nClasses\nMeeting\nEvent\n";
	}
	if(option2 == 1)
	{
		std :: cout << "Birthday\n";
		calendar.printColors("Anniversary",9);
		std :: cout << "\nAnnual Day\nClasses\nMeeting\nEvent\n";
	}
	if(option2 == 2)
	{
		std :: cout << "Birthday\nAnniversary\n";
		calendar.printColors("Annual Day",9);
		std :: cout << "\nClasses\nMeeting\nEvent\n";
	}
	if(option2 == 3)
	{
		std :: cout << "Birthday\nAnniversary\nAnnual Day\n";
		calendar.printColors("Classes",9);
		std :: cout << "\nMeeting\nEvent\n";
	}
	if(option2 == 4)
	{
		std :: cout << "Birthday\nAnniversary\nAnnual Day\nClasses\n";
		calendar.printColors("Meeting",9);
		std :: cout << "\nEvent\n";
	}
	if(option2 == 5)
	{
		std :: cout << "Birthday\nAnniversary\nAnnual Day\nClasses\nMeeting\n";
		calendar.printColors("Event",9);
		std :: cout << std :: endl;
	}
}

void CalendarApplication ::  headForInsertTask()
{
	system("mode 158");
	system("color F0");
	
	calendar.displayClocke();

	std :: cout << "\n\n\t\tINSERT TASK MENU\n\t\tSelect the desired type of from options Below\n\n";

	optionsPrintingForInsert();
}

void CalendarApplication :: insertTask()
{
	int KB_code = 0;

	headForInsertTask();

	while(KB_code != KB_BSPACE && KB_code != KB_ESCAPE)
	{
		if(_kbhit())
		{
			KB_code = _getch();

			switch (KB_code)
			{
			case KB_UP:
				{
					option2--;
					if(option2 == -1)
						option2 = 5;
					headForInsertTask();
				}
				break;
			case KB_DOWN:
				{
					option2++ ;
					if(option2 == 6)
						option2 = 0;
					headForInsertTask();
				}
				break;
			case KB_ENTER:
				{
					switch(option2)
					{
					case 0:
						{
							calendar.insertType1BirthdayTask();
							headForInsertTask();
						}
						break;
					case 1:
						{
							calendar.insertType1AnniversaryTask();
							headForInsertTask();
						}
						break;
					case 2:
						{
							calendar.insertType1AnnualDayTask();
							headForInsertTask();
						}
						break;
					case 3:
						{
							calendar.insertType0ClassesTask();
							headForInsertTask();
						}
						break;
					case 4:
						{
							calendar.insertType0MeetingTask();
							headForInsertTask();
						}
						break;
					case 5:
						{
							calendar.insertType0Event();
							headForInsertTask();
						}
						break;
					}
				}
				break;
			}
		}
	}
	return;
}

void CalendarApplication :: headOfTaskDisplayAndEditing()
{
	system("mode 158");
	system("color F0");
	
	calendar.displayClocke();

	calendar.openDayTaskAtRunningHour();
}

void CalendarApplication :: taskDisplayAndEditingFunction()
{
	
	headOfTaskDisplayAndEditing();

	int KB_code = 0;
	while(KB_code != KB_BSPACE && KB_code != KB_ESCAPE)
	{
		if(_kbhit())
		{
			KB_code = _getch();
						
			switch(KB_code)
			{
			case KB_INSERT:
				{
					insertTask();
					headOfTaskDisplayAndEditing();
				}
				break;
			case KB_DEL:
				{
					calendar.deleteDayTaskAtRunningHour();
					headOfTaskDisplayAndEditing();
				}
				break;
			case KB_F1:
				functionF1();
				break;
			case KB_F9:
				functionF9();
				break;
			}
				
		}
	}
	return;
}

void CalendarApplication :: wholeWeekCalendarFunction()
{
	int KB_code = 0;
	calendar.showWholeWeeklyCalendar();
	while(KB_code != KB_BSPACE && KB_code != KB_ENTER  && KB_code != KB_ESCAPE)
	{
		if(_kbhit())
		{
			KB_code = _getch();

			switch(KB_code)
			{
			case KB_F9:
				{
					functionF9();
					calendar.showWholeWeeklyCalendar();
				}
				break;
			case KB_UP:
				{
					calendar.decrementHour();
					calendar.showWholeWeeklyCalendar();
				}
				break;
			case KB_DOWN:
				{
					calendar.incrementHour();
					calendar.showWholeWeeklyCalendar();
				}
				break;
			case KB_LEFT:
				{
					calendar.incrementDay(-1);
					calendar.showWholeWeeklyCalendar();
				}
				break;
			case KB_RIGHT:
				{
					calendar.incrementDay(1);
					calendar.showWholeWeeklyCalendar();
				}
				break;
			case KB_TAB:
				{
					calendar.incrementWeek(1);
					calendar.showWholeWeeklyCalendar();
				}
				break;
			case KB_SPACE:
				{
					calendar.incrementWeek(-1);
					calendar.showWholeWeeklyCalendar();
				}
				break;
			case KB_PGDOWN:
				{
					calendar.incrementWeek(1);
					calendar.showWholeWeeklyCalendar();
				}
				break;
			case KB_PGUP:
				{
					calendar.incrementWeek(-1);
					calendar.showWholeWeeklyCalendar();
				}
				break;
			case KB_ENTER:
				{
					calendar.showWholeDailyCalendar();
				}
				break;
			case KB_BSPACE:
				{
					calendar.showWholeMonthlyCalendar();
				}
				break;
			case KB_F1:
				{
					functionF1();
					calendar.showWholeWeeklyCalendar();
				}
				break;
			case KB_F2:
				{
					functionF2();
					calendar.showWholeWeeklyCalendar();
				}
				break;
			case KB_F3:
				{
					updateTaskAtDateAndHour();
					calendar.showWholeWeeklyCalendar();
				}
				break;
			}
		}
	}
	return;
}

void CalendarApplication :: wholeYearCalendarFunction()
{
	calendar.showWholeYearCalendar();
	int KB_code = 0;
	while(KB_code != KB_ENTER  && KB_code != KB_ESCAPE)
	{
		if(_kbhit())
		{
			KB_code = _getch();
			
			switch(KB_code)
			{
			case KB_TAB:
				{
					calendar.incrementYear(1);
					calendar.showWholeYearCalendar();
				}
				break;
			case KB_F1:
				{
					functionF1();
					calendar.showWholeYearCalendar();
				}
				break;
			case KB_F2:
				{
					functionF2();
					calendar.showWholeYearCalendar();
				}
				break;
			case KB_F3:
				{
					functionF3();
					calendar.showWholeYearCalendar();
				}
				break;
			case KB_F9:
				{
					functionF9();
					calendar.showWholeYearCalendar();
				}
				break;
			case KB_SPACE:
				{
					calendar.incrementYear(-1);
					calendar.showWholeYearCalendar();
				}
				break;
			case KB_PGDOWN:
				{
					calendar.incrementYear(1);
					calendar.showWholeYearCalendar();
				}
				break;
			case KB_PGUP:
				{
					calendar.incrementYear(-1);
					calendar.showWholeYearCalendar();
				}
				break;
			case KB_ENTER:
					calendar.showWholeMonthlyCalendar();
				break;
			case KB_UP:
				{
					calendar.incrementWeek(-1);
					calendar.showWholeYearCalendar();
				}
				break;
			case KB_DOWN:
				{
					calendar.incrementWeek(1);
					calendar.showWholeYearCalendar();
				}
				break;
			case KB_RIGHT:
				{
					calendar.incrementDay(1);
					calendar.showWholeYearCalendar();
				}
				break;
			case KB_LEFT:
				{
					calendar.incrementDay(-1);
					calendar.showWholeYearCalendar();
				}
				break;
			}
		}
	}
	return;
}

void CalendarApplication :: functionF1()
{
	calendar.functionF1();
	int KB_code = 0;

	while(KB_code != KB_BSPACE)
	{
		if(_kbhit())
		{
			KB_code = _getch();
		}
	}
}

void CalendarApplication :: wholeMonthlyCalendarFunction()
{
	
	calendar.showWholeMonthlyCalendar();
	int KB_code = 0;
	while(KB_code != KB_ESCAPE)
	{
		if(_kbhit())
		{
			KB_code = _getch();

			switch(KB_code)
			{
			case KB_UP:
				{
					calendar.incrementDay(-7);
					calendar.showWholeMonthlyCalendar();
				}
				break;
			case KB_DOWN:
				{
					calendar.incrementDay(7);
					calendar.showWholeMonthlyCalendar();
				}
				break;
			case KB_RIGHT:
				{
					calendar.incrementDay();
					calendar.showWholeMonthlyCalendar();
				}
				break;
			case KB_LEFT:
				{
					calendar.incrementDay(-1);
					calendar.showWholeMonthlyCalendar();
				}
				break;
			case KB_F9:
				{
					functionF9();
					calendar.showWholeMonthlyCalendar();
				}
				break;
			case KB_F1:
				{
					functionF1();
					calendar.showWholeMonthlyCalendar();
				}
				break;
			case KB_F2:
				{
					functionF2();
					calendar.showWholeMonthlyCalendar();
				}
				break;
			case KB_PGDOWN:
				{
					calendar.incrementMonth(1);
					calendar.showWholeMonthlyCalendar();
				}
				break;
			case KB_PGUP:
				{
					calendar.incrementMonth(-1);
					calendar.showWholeMonthlyCalendar();
				}
				break;
			case KB_TAB:
				{
					calendar.incrementMonth(1);
					calendar.showWholeMonthlyCalendar();
				}
				break;
			case KB_SPACE:
				{
					calendar.incrementMonth(-1);
					calendar.showWholeMonthlyCalendar();
				}
				break;
			case KB_BSPACE:
				{
					wholeYearCalendarFunction();
				}
				break;
			case KB_ENTER:
				{
					wholeDayCalendarFunction();	
				}
				break;
			case KB_F3:
				{
					functionF3();
					calendar.showWholeMonthlyCalendar();
				}
				break;
			}
		}
	}
	return;
}


void CalendarApplication :: upperPartOfFunctionF9()
{
	system("mode 158");
	system("color F0");

	std :: cout << "\n\t\t\t\tClock Setup";
	if(call == 0)
	{
		std :: cout << "\n\n\t\t Current Time and Date are according to your system.";
		call = 1;
	}
	else
		std :: cout << "\n\n\t\t Current Time and Date are set according to you.";

	std :: cout << "\n\t\tCalendars current Time is\n\n\t\t In 12Hr Format : ";
	calendar.getTime().printTwelveHourFormat();
	std :: cout << "\n\t\t In 24Hr Fomrat : ";
	calendar.getTime().printTwentyFourHourFormat();
	std :: cout << "\n\n\t\t And Date is : ";
	calendar.getDate().getDateInFormat2().display();

	std :: cout << "\n\t\tYou've to select any of them for changing Time or Date\n\t\t and Backspace for returning\n\n";


	if(option == 0)
	{
		calendar.printColors("Edit Date",9);
		std :: cout << "\nEdit Time";
	}
	if(option == 1)
	{
		std :: cout << "Edit Date\n";
		calendar.printColors("Edit Time",9);
	}
}

void CalendarApplication :: functionF9()
{
	int KB_code = 0;

	upperPartOfFunctionF9();

	while(KB_code != KB_BSPACE && KB_code != KB_ESCAPE)
	{
		if(_kbhit())
		{
			KB_code = _getch();

			switch(KB_code)
			{
			case KB_TAB:
				{
					getDateFromUser();
					upperPartOfFunctionF9();
				}
				break;
			case KB_PGDOWN:
				{
					getTimeFromUser();
					upperPartOfFunctionF9();
				}
				break;
			case KB_ENTER:
				{
					if(option == 0)
						getDateFromUser();
					if(option == 1)
						getTimeFromUser();
					upperPartOfFunctionF9();
				}
				break;
			case KB_UP:
				{
					option = !option;
					upperPartOfFunctionF9();
				}
				break;
			case KB_DOWN:
				{
					option = !(option);
					upperPartOfFunctionF9();
				}
				break;
			case KB_RIGHT:
				{
					if(option == 0)
						getDateFromUser();
					if(option == 1)
						getTimeFromUser();
					upperPartOfFunctionF9();
				}
				break;
			}
		}
	}
	return;
}

void CalendarApplication ::  headForGetTimeFromUser()
{
	if(calendar.getTime().getHour() >= 12 && callForTimeAmOrPm)
	{
		inputTimeAmOrPm = 1;
		callForTimeAmOrPm = 0;
	}

	system("cls");

	
	int h = clockForInputFromUser.getHour() % 12;
	if(h == 0)
		h = 12;

	std :: cout << "\n\t < > Arrows Keys for selection of Hour, Minute, Second & AM/PM ^ v Arrow Keys for changing them\n\n\t\t\t\t\t";

	if(inputTimeSlot == '1')
	{
		calendar.printColors(CString :: toCString(h));
		std :: cout << " : " << clockForInputFromUser.getMinute() << " : " <<clockForInputFromUser.getSecond();

		if(inputTimeAmOrPm)
			std :: cout << " PM";
		else
			std :: cout << " AM";
	}
	if(inputTimeSlot == '2')
	{
		std :: cout << h << " : ";
		if(clockForInputFromUser.getMinute() == 0)
			calendar.printColors("0");
		else
			calendar.printColors(CString :: toCString(clockForInputFromUser.getMinute()));
		std :: cout << " : " << clockForInputFromUser.getSecond();

		if(inputTimeAmOrPm)
			std :: cout << " PM";
		else
			std :: cout << " AM";
	}
	if(inputTimeSlot == '3')
	{
		std :: cout << h << " : " << clockForInputFromUser.getMinute() << " : ";
		if(clockForInputFromUser.getSecond() == 0)
			calendar.printColors("0");
		else
			calendar.printColors(CString :: toCString(clockForInputFromUser.getSecond()));

		if(inputTimeAmOrPm)
			std :: cout << " PM";
		else
			std :: cout << " AM";
	}
	if(inputTimeSlot == '4')
	{
		std :: cout << h << " : " << clockForInputFromUser.getMinute() << " : " << clockForInputFromUser.getSecond();
		
		if(inputTimeAmOrPm)
			calendar.printColors(" PM");
		else
			calendar.printColors(" AM");
	}
}

void CalendarApplication :: getTimeFromUser()
{
	clockForInputFromUser.refresh();
	headForGetTimeFromUser();

	int code = 0;

	while(code != KB_BSPACE)
	{
		if(_kbhit())
		{
			code = _getch();

			switch(code)
			{
			case KB_RIGHT:
				{
					if(inputTimeSlot == '4')
						inputTimeSlot = '1';
					else
						inputTimeSlot += 1;
					
					headForGetTimeFromUser();
				}
				break;
			case KB_LEFT:
				{
					if(inputTimeSlot == '1')
						inputTimeSlot = '4';
					else
						inputTimeSlot -= 1;
					
					headForGetTimeFromUser();
				}
				break;
			case KB_UP:
				{
					switch(inputTimeSlot)
					{
					case '1':
						clockForInputFromUser.decHour(-1);
						break;
					case '2':
						clockForInputFromUser.decMin(-1);
						break;
					case '3':
						clockForInputFromUser.decSec(-1);
						break;
					case '4':
						inputTimeAmOrPm = !inputTimeAmOrPm;
						break;
					}
					headForGetTimeFromUser();
				}
				break;
			case KB_DOWN:
				{
					switch(inputTimeSlot)
					{
					case '1':
						clockForInputFromUser.incHour();
						break;
					case '2':
						clockForInputFromUser.incMin();
						break;
					case '3':
						clockForInputFromUser.incSec();
						break;
					case '4':
						inputTimeAmOrPm = !inputTimeAmOrPm;
						break;
					}
					headForGetTimeFromUser();
				}
				break;
			case KB_BSPACE:
				{
					calendar.setTime(actualHourToInsertInPresentTime(),clockForInputFromUser.getMinute(), clockForInputFromUser.getSecond());
					inputTimeSlot = '1';
				}
				break;
			case KB_ENTER:
				{
					calendar.setTime(actualHourToInsertInPresentTime(),clockForInputFromUser.getMinute(), clockForInputFromUser.getSecond());
					inputTimeSlot = '1';
					code = KB_BSPACE;
				}
				break;
			}
		}
	}
	return;
}

int CalendarApplication :: actualHourToInsertInPresentTime()
{
	int h = clockForInputFromUser.getHour() % 12;
	if(h == 0 && !inputTimeAmOrPm)
		return 0;
	if(h == 0 && inputTimeAmOrPm)
		return 12;
	if(h != 0 && !inputTimeAmOrPm)
		return h;
	if(h != 0 && inputTimeAmOrPm)
		return h + 12;

	return h;
}

void CalendarApplication ::  headForGetDateFromUser()
{
	system("cls");

	std :: cout << "\n\t < > Arrows Keys for selection of Day, Month and Year, ^ v Arrow Keys for changing them\n\n\t\t\t\t\t";

	if(inputDateSlot == '1')
	{
		calendar.printColors(CString :: toCString(clockForInputFromUser.getDay()));
		std :: cout << " - " << clockForInputFromUser.getMonth() << " - " <<clockForInputFromUser.getYear();
	}
	if(inputDateSlot == '2')
	{
		std :: cout << clockForInputFromUser.getDay() << " - ";
		calendar.printColors(CString :: toCString(clockForInputFromUser.getMonth()));
		std :: cout << " - " << clockForInputFromUser.getYear();
	}
	if(inputDateSlot == '3')
	{
		std :: cout << clockForInputFromUser.getDay() << " - " << clockForInputFromUser.getMonth() << " - ";
		calendar.printColors(CString :: toCString(clockForInputFromUser.getYear()));
	}
}

void CalendarApplication :: getDateFromUser()
{
	headForGetDateFromUser();

	int KB_code = 0;
	while(KB_code != KB_BSPACE)
	{
		if(_kbhit())
		{
			KB_code = _getch();

			switch(KB_code)
			{
			case KB_DOWN:
				{
					switch(inputDateSlot)
					{
					case '1':
						clockForInputFromUser.incDay();
						break;
					case '2':
						clockForInputFromUser.incMonth();
						break;
					case '3':
						clockForInputFromUser.incYear();
						break;
					}
					headForGetDateFromUser();
				}
				break;
			case KB_UP:
				{
					switch (inputDateSlot)
					{
					case '1':
						clockForInputFromUser.incDay(-1);
						break;
					case '2':
						clockForInputFromUser.incMonth(-1);
						break;
					case '3':
						clockForInputFromUser.incYear(-1);
						break;
					}
					headForGetDateFromUser();
				}
				break;
			case KB_RIGHT:
				{
					if(inputDateSlot == '3')
						inputDateSlot = '1';
					else
						inputDateSlot += 1;
					
					headForGetDateFromUser();
				}
				break;
			case KB_LEFT:
				{
					if(inputDateSlot == '1')
						inputDateSlot = '3';
					else
						inputDateSlot -= 1;
					
					headForGetDateFromUser();
				}
				break;
			case KB_BSPACE:
				{
					calendar.setDate(clockForInputFromUser.getDay(), clockForInputFromUser.getMonth(), clockForInputFromUser.getYear());
					inputDateSlot = '1';
				}
				break;
			case KB_ENTER:
				{
					calendar.setDate(clockForInputFromUser.getDay(), clockForInputFromUser.getMonth(), clockForInputFromUser.getYear());
					inputDateSlot = '1';
					KB_code = KB_BSPACE;
				}
				break;
			}
		}
	}
	return;
}

void CalendarApplication :: headForFunctionF3()
{
	system("cls");

	std :: cout << "\n\tYou've entered in Task Updation & Deletion Window, select your option\n\n";

	if(functionF3selection == '1')
	{
		calendar.printColors("Update Task",9);
		std :: cout << "\nDelete Task\nReturn";
	}
	if(functionF3selection == '2')
	{
		std :: cout << "Update Task\n";
		calendar.printColors("Delete Task",9);
		std :: cout << "\nReturn";
	}
	if(functionF3selection == '3')
	{
		std :: cout << "Update Task\nDelete Task\n";
		calendar.printColors("Return",9);
	}
}

void CalendarApplication :: functionF3()
{
	headForFunctionF3();

	int code = 0;
	
	while(code != KB_BSPACE)
	{
		if(_kbhit())
		{
			code = _getch();

			switch(code)
			{
			case KB_UP:
				{
					if(functionF3selection == '1')
						functionF3selection = '3';
					else
						functionF3selection -= 1;

					headForFunctionF3();
				}
				break;
			case KB_DOWN:
				{
					if(functionF3selection == '3')
						functionF3selection = '1';
					else
						functionF3selection += 1;

					headForFunctionF3();
				}
				break;
			case KB_ENTER :
				{
					switch(functionF3selection)
					{
					case '1':
						{
							taskUpdation();
							headForFunctionF3();
						}
						break;
					case '2':
						{
							calendar.deleteTask();
							headForFunctionF3();
						}
						break;
					case '3':
						{
							code = KB_BSPACE;
							functionF3selection = '1';
						}
						break;
					}
				}
				break;
			case KB_BSPACE:
				{
					functionF3selection = '1';
				}
				break;
			}
		}
	}
}

void CalendarApplication :: headForTaskUpdation()
{
	system ("cls");
	std :: cout << "Select Task Category \n\n";
	if(taskUpdationBeginningOptions == '1')
	{
		calendar.printColors("Birthdays/Anniversary/Annual Day",9);
		std :: cout << "\nClasses/Meetings/Events\nReturn";
	}
	if(taskUpdationBeginningOptions == '2')
	{
		std :: cout << "Birthdays/Anniversary/Annual Day\n";
		calendar.printColors("Classes/Meetings/Events",9);
		std :: cout << "\nReturn";
	}
	if(taskUpdationBeginningOptions == '3')
	{
		std :: cout << "Birthdays/Anniversary/Annual Day\nClasses/Meetings/Events\n";
		calendar.printColors("Return",9);
	}
}

void CalendarApplication :: taskUpdation()
{
	headForTaskUpdation();

	int code = 0;

	while(code != KB_BSPACE)
	{
		if(_kbhit())
		{

			code = _getch();

			switch(code)
			{
			case KB_UP:
				{
					if(taskUpdationBeginningOptions == '1')
						taskUpdationBeginningOptions = '3';
					else
						taskUpdationBeginningOptions -= 1;

					headForTaskUpdation();
				}
				break;
			case KB_DOWN :
				{
					if(taskUpdationBeginningOptions == '3')
						taskUpdationBeginningOptions = '1';
					else
						taskUpdationBeginningOptions += 1;

					headForTaskUpdation();
				}
				break;
			case KB_ENTER:
				{
					switch(taskUpdationBeginningOptions)
					{
					case '1':
						{
							updateType1Task();
							headForTaskUpdation();
						}
						break;
					case '2':
						{
							updateType0Task();
							headForTaskUpdation();
						}
						break;
					case '3':
						{
							code = KB_BSPACE;
							taskUpdationBeginningOptions = '1';
						}
						break;
					}
				}
				break;
			case KB_BSPACE:
				{
					taskUpdationBeginningOptions = '1';
				}
				break;
			}
		}
	}
}

void CalendarApplication ::headForOptionsForUpdation(Task * t)
{
	system("cls");
	std :: cout << (*t);

	clockForInputFromUser.setDate(t -> getDate().getDay(), t->getDate().getMonth(),t->getDate().getYear());
	clockForInputFromUser.setTime(t->getTime().getHour(), t->getTime().getMinute(), t->getTime().getSecond());

	std :: cout << "\n\tSelect options from below;\n\n";

	if(taskUpdationFinalOptions == '1')
	{
		calendar.printColors("Update Time",9);
		std :: cout << "\nUpdate Date\nUpdate Message\nReturn";
	}
	if(taskUpdationFinalOptions == '2')
	{
		std :: cout << "Update Time\n";
		calendar.printColors("Update Date",9);
		std :: cout << "\nUpdate Message\nReturn";
	}
	if(taskUpdationFinalOptions == '3')
	{
		std :: cout << "Update Time\nUpdate Date\n";
		calendar.printColors("Update Message",9);
		std :: cout << "\nReturn";
	}
	if(taskUpdationFinalOptions == '4')
	{
		std :: cout << "Update Time\nUpdate Date\nUpdate Message\n";
		calendar.printColors("Return");
	}
}

void CalendarApplication :: optionsForUpdation(Task * t)
{
	headForOptionsForUpdation(t);

	int code = 0;

	while(code != KB_BSPACE)
	{
		if(_kbhit())
		{
			code = _getch();

			switch(code)
			{
			case KB_UP:
				{
					if(taskUpdationFinalOptions == '1')
						taskUpdationFinalOptions = '4';
					else
						taskUpdationFinalOptions -= 1;

					headForOptionsForUpdation(t);
				}
				break;
			case KB_DOWN:
				{
					if(taskUpdationFinalOptions == '4')
						taskUpdationFinalOptions = '1';
					else
						taskUpdationFinalOptions += 1;

					headForOptionsForUpdation(t);
				}
				break;
			case KB_ENTER :
				{
					switch(taskUpdationFinalOptions)
					{
					case '1':
						{
							getTimeFromUserForUpdationOfTask(t);
							headForOptionsForUpdation(t);
						}
						break;
					case '2':
						{
							getDateFromUserForUpdationOfTask(t);
							headForOptionsForUpdation(t);
						}
						break;
					case '3':
						{
							getMessageFromUserToUpdate(t);
							headForOptionsForUpdation(t);
						}
						break;
					case '4':
						{
							code = KB_BSPACE;
							taskUpdationFinalOptions = '1';
						}
						break;
					}
				}
			case KB_BSPACE:
				{
					taskUpdationFinalOptions = '1';
				}
				break;
			}
		}
	}
}

void CalendarApplication :: updateType0Task()
{
	int status = 0;
	Task * t = &(calendar.updateTask(0,status));
	
	if(status == 1)
		optionsForUpdation(t);
	return;
}

void CalendarApplication :: updateType1Task()
{
	int status = 0 ;
	Task *t = &(calendar.updateTask(1,status));
	
	if(status == 1)
		optionsForUpdation(t);
	return;
}

void CalendarApplication :: updateTaskAtDateAndHour()
{
	int status = 0;
	Task * t = &(calendar.editTaskAtRunningTimeAndHour(status));

	if(status == 1)
		optionsForUpdation(t);
	return;
}

void CalendarApplication :: getDateFromUserForUpdationOfTask(Task * t)
{
	headForGetDateFromUser();

	int KB_code = 0;
	while(KB_code != KB_BSPACE)
	{
		if(_kbhit())
		{
			KB_code = _getch();

			switch(KB_code)
			{
			case KB_DOWN:
				{
					switch(inputDateSlot)
					{
					case '1':
						clockForInputFromUser.incDay();
						break;
					case '2':
						clockForInputFromUser.incMonth();
						break;
					case '3':
						clockForInputFromUser.incYear();
						break;
					}
					headForGetDateFromUser();
				}
				break;
			case KB_UP:
				{
					switch (inputDateSlot)
					{
					case '1':
						clockForInputFromUser.incDay(-1);
						break;
					case '2':
						clockForInputFromUser.incMonth(-1);
						break;
					case '3':
						clockForInputFromUser.incYear(-1);
						break;
					}
					headForGetDateFromUser();
				}
				break;
			case KB_RIGHT:
				{
					if(inputDateSlot == '3')
						inputDateSlot = '1';
					else
						inputDateSlot += 1;
					
					headForGetDateFromUser();
				}
				break;
			case KB_LEFT:
				{
					if(inputDateSlot == '1')
						inputDateSlot = '3';
					else
						inputDateSlot -= 1;
					
					headForGetDateFromUser();
				}
				break;
			case KB_BSPACE:
				{
					calendar.updateTaskDate(*t,Date(clockForInputFromUser.getDay(), clockForInputFromUser.getMonth(), clockForInputFromUser.getYear()));
					inputDateSlot = '1';
				}
				break;
			case KB_ENTER:
				{
					calendar.updateTaskDate(*t,Date(clockForInputFromUser.getDay(), clockForInputFromUser.getMonth(), clockForInputFromUser.getYear()));
					inputDateSlot = '1';
					KB_code = KB_BSPACE;
				}
				break;
			}
		}
	}
	return;
}

void CalendarApplication :: getTimeFromUserForUpdationOfTask(Task * t)
{
	headForGetTimeFromUser();

	int code = 0;

	while(code != KB_BSPACE)
	{
		if(_kbhit())
		{
			code = _getch();

			switch(code)
			{
			case KB_RIGHT:
				{
					if(inputTimeSlot == '4')
						inputTimeSlot = '1';
					else
						inputTimeSlot += 1;
					
					headForGetTimeFromUser();
				}
				break;
			case KB_LEFT:
				{
					if(inputTimeSlot == '1')
						inputTimeSlot = '4';
					else
						inputTimeSlot -= 1;
					
					headForGetTimeFromUser();
				}
				break;
			case KB_UP:
				{
					switch(inputTimeSlot)
					{
					case '1':
						clockForInputFromUser.decHour(-1);
						break;
					case '2':
						clockForInputFromUser.decMin(-1);
						break;
					case '3':
						clockForInputFromUser.decSec(-1);
						break;
					case '4':
						inputTimeAmOrPm = !inputTimeAmOrPm;
						break;
					}
					headForGetTimeFromUser();
				}
				break;
			case KB_DOWN:
				{
					switch(inputTimeSlot)
					{
					case '1':
						clockForInputFromUser.incHour();
						break;
					case '2':
						clockForInputFromUser.incMin();
						break;
					case '3':
						clockForInputFromUser.incSec();
						break;
					case '4':
						inputTimeAmOrPm = !inputTimeAmOrPm;
						break;
					}
					headForGetTimeFromUser();
				}
				break;
			case KB_BSPACE:
				{
					calendar.updateTaskTime(*t,Time(actualHourToInsertInPresentTime(),clockForInputFromUser.getMinute(), clockForInputFromUser.getSecond()));
					inputTimeSlot = '1';
				}
				break;
			case KB_ENTER:
				{
					calendar.updateTaskTime(*t,Time(actualHourToInsertInPresentTime(),clockForInputFromUser.getMinute(), clockForInputFromUser.getSecond()));
					inputTimeSlot = '1';
					code = KB_BSPACE;
				}
				break;
			}
		}
	}
	return;
}

void CalendarApplication :: getMessageFromUserToUpdate(Task * t)
{
	CString newMessage;

	std :: cout << "\n\tNew Message : ";
	std :: cin >> newMessage;

	calendar.updateTaskMessage(*t,newMessage);
}