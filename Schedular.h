#ifndef SCHEDULAR_H
#define SCHEDULAR_H
#include"Task.h"
#include"CString.h"
class Schedular
{
	Task * taskList;
	int noOfTasks;
	int capacity;
	static bool editCheck;

	void displayTask(const Task & m);
	void defaultTask();
	Time returnValidTimeToSetTask(const Date & d, const Time & t);
	bool isValisdIndex(int index);
	void downloadFile();
	void uploadFile(std :: ifstream & ifs, int index);
	int totalNumberOfTypeTasks(bool taskType);
public:
	Schedular(int not=5);
	bool addTask(const Date & d, const Time & t,  const CString & cs, bool taskType = 0);
	bool removeTask(const Date &d=Date(0,0,0));
	void removeTaskGenerally();
	bool removeTaskOnDateAndTimeOfType0(const Date &d, const int h);
	bool removeTaskOnDateAndTimeOfType1(const Date & d = Date(0,0,0));
	int doesTaskExist(const Date & d);
	int doesTaskExistOnDateAndTime(const Date & d, const Time & t);
	void displayAllTasks();
	bool displayTaskOnDate(const Date& d);
	void displayTaskOnDateAndHour(const Date& d, int h);
	bool displayType1TaskOnDate(const Date& d);
	void displayTaskOnIndex(int index);
	int doesTaskExistOnHour(const Date & d, int hour);
	int doesTaskExistOfType(const Date & d, int taskType = 0);
	void reSizeSchedule(int newSize);
	int numberOfTasksOnDate(const Date & d);
	int numberOfType1TasksOnDate(const Date & d);
	int numberOfType0TasksOnDateAndHour(const Date & d, const int hour);
	int totalNumberOfTaskOnDateAndHour(const Date & d, const int hour);
	int numberOfTasksOnDate(const Date & d, const Time & t);
	CString getFirstWordsOfTask(int index);
	CString getMessageOfTaskAtIndex(int index);
	int returnIndexOfSecondType1TaskOnDay(const Date & d);
	int returnIndexOfSecondType0TaskOnDay(const Date & d);
	int returnIndexOfSecondType0TaskOnDayAndHour(const Date & d, const int hour);
	int returnYearOfType1TaskAtIndex(int index);
	Time getTimeOfTaskAtIndex(int index);
	~Schedular();
	Task & editTaskType(const bool taskType,int & status);
	static bool isTaskNull(const Task &);
	Task & editTaskAtParticularDateAndTime(Date &, int hour, int & status);
};
#endif