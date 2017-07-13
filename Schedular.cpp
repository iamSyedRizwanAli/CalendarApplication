#include"Schedular.h"
#include"Time.h"
#include"CString.h"
#include"Date.h"
#include<iostream>
#include<fstream>
using namespace std;

bool Schedular :: editCheck = 0;

Schedular :: Schedular(int not)
{
	if(not <=0 )
	{
		capacity = 0;
		noOfTasks = 0;
		taskList =0;
	}
	else
	{
		capacity = not;
		noOfTasks = 0;
		taskList = new Task[capacity];
	}
	defaultTask();
}

void Schedular :: downloadFile()
{
	std :: ofstream ofs("temp.txt");

	for(int i = 0 ; i < noOfTasks ; i++)
	{
		ofs << '\n' << taskList[i].getDate().dateToInteger() << " " << taskList[i].getTime().timeToInteger() << " " << taskList[i].getTaskType() <<  " " << taskList[i].getMessage().returnDataPointer();
	}

	ofs.close();
	remove("schedule.txt");
	rename("temp.txt","schedule.txt");
}

Time Schedular :: getTimeOfTaskAtIndex(int ind)
{
	if(ind >= 0 && ind < noOfTasks)
		return taskList[ind].getTime();
	exit(0);
}

int Schedular :: numberOfTasksOnDate(const Date & d)
{
	int j = 0;
	for(int i = 0 ; i < noOfTasks ; i++)
	{
		if(d == taskList[i].getDate() && taskList[i].getTaskType() == 0)
			j++;
		if(d.getDay() == taskList[i].getDate().getDay() && d.getMonth() == taskList[i].getDate().getMonth() && d.getYear() >= taskList[i].getDate().getYear() &&taskList[i].getTaskType() == 1)
			j++;
	}
	return j;
}

int Schedular :: numberOfType1TasksOnDate(const Date & d)
{
	int j = 0;
	for(int i = 0 ; i < noOfTasks ; i++)
	{
		if(d.getDay() == taskList[i].getDate().getDay() && d.getMonth() == taskList[i].getDate().getMonth() && d.getYear() >= taskList[i].getDate().getYear() &&taskList[i].getTaskType() == 1)
			j++;
	}
	return j;
}

int Schedular :: numberOfTasksOnDate(const Date & d, const Time & t)
{
	int j = 0;
	for(int i = 0 ; i < noOfTasks ; i++)
	{
		if(d == taskList[i].getDate())
		{
			if(t == taskList[i].getTime())
				j++;
		}
	}
	return j;
}

int Schedular :: numberOfType0TasksOnDateAndHour(const Date & d, const int hour)
{
	int j = 0;
	for(int i = 0 ; i < noOfTasks ; i++)
	{
		if(d == taskList[i].getDate() && taskList[i].getTime().getHour() == hour && taskList[i].getTaskType() == 0)
			j++;
	}
	return j;
}

CString Schedular :: getMessageOfTaskAtIndex(int i)
{
	if(!isValisdIndex(i))
		return "No Current Task";
	return taskList[i].getMessage();
}

int Schedular :: returnYearOfType1TaskAtIndex(int index)
{
	if(!isValisdIndex(index))
		return 2000;
	if(taskList[index].getTaskType() == 1)
		return taskList[index].getDate().getYear();
	return 2000;
}

int Schedular :: doesTaskExist(const Date & d)
{
	for(int i = 0 ; i < noOfTasks ; i++)
	{
		if(d == taskList[i].getDate() && taskList[i].getTaskType() == 0)
			return i;
		if(d.getDay() == taskList[i].getDate().getDay() && d.getMonth() == taskList[i].getDate().getMonth() && d.getYear() >= taskList[i].getDate().getYear() &&taskList[i].getTaskType() == 1)
			return i;
	}
	return -1;
}

int Schedular :: doesTaskExistOnDateAndTime(const Date & d, const Time & t)
{
	for(int i = 0 ; i < noOfTasks ; i++)
	{
		if(d == taskList[i].getDate() && t == taskList[i].getTime())
			return i;
	}
	return -1;
}

CString Schedular :: getFirstWordsOfTask(int index)
{
	if(isValisdIndex(index))
		return taskList[index].getMessage();
	return "**";
}

void Schedular :: defaultTask()
{
	ifstream ifs("schedule.txt");
	int i ;
	for(i = 0 ; i < capacity && !(ifs.eof()) ; i++)
	{
		uploadFile(ifs,i);
		noOfTasks++;
	}
	if(i == capacity&& !(ifs.eof()))
	{
		reSizeSchedule(capacity * 2);
		for(i; i < capacity && !(ifs.eof()) ; i++)
		{
			uploadFile(ifs,i);
			noOfTasks++;
		}
	}

	ifs.close();
}

void Schedular :: uploadFile(std :: ifstream & ifs, int index)
{
	char s;

	int date;
	int time;
	bool type;
	ifs >> date;
	
	ifs.clear();
	ifs.ignore();

	ifs >> time;

	ifs.clear();
	ifs.ignore();

	ifs >> type;
	CString something;

	taskList[index].updateDate(Date :: integerToDate(date));
	taskList[index].updateTime(Time :: integerToTime(time));	
	taskList[index].updateTaskType(type);

	ifs.clear();
	ifs.ignore();
	ifs >> noskipws >> s;

	while(s != '\n' && !(ifs.eof()))
	{
		something.concatEqual(s);
		ifs >> noskipws >> s;
	}
	taskList[index].updateMessage(something);
}

int Schedular :: doesTaskExistOnHour(const Date & d, int h)
{
	for(int i = 0 ; i < noOfTasks ; i++)
	{
		if(d == taskList[i].getDate())
		{
			if(h == taskList[i].getTime().getHour())
				return i;
		}
	}
	return -1;
}

int Schedular :: doesTaskExistOfType(const Date & d, int type)
{
	
	int i = 0;
	bool status = 1;
	if(type == 1)
	{
		while( i < noOfTasks && status)
		{
			if(d.getDay() == taskList[i].getDate().getDay() && d.getMonth() == taskList[i].getDate().getMonth() && taskList[i].getTaskType() == 1)
				return i;
			i++;
		}
	}
	else
	{
		while( i < noOfTasks && status)
		{
			if(d == taskList[i].getDate() && taskList[i].getTaskType() == 0)
				return i;
			i++;
		}
	}
	return -1;
}

void Schedular :: displayTask(const Task & m)
{
	std :: cout << "Date : ";
	m.getDate().printFormat2();
	std :: cout << std :: endl << "Time : ";
	m.getTime().printTwentyFourHourFormat();
	std :: cout << std :: endl << "Message : ";
	m.getMessage().display();
	std :: cout <<  std :: endl << "Task Type : ";
	std :: cout << m.getTaskType() << std :: endl;
}

bool Schedular :: addTask(const Date & d, const Time & t,  const CString & cs, bool taskType)
{
	if(noOfTasks == capacity)
	{
		int newSize = capacity * 2;
		reSizeSchedule(newSize);
	}
	
	Time tempTime = returnValidTimeToSetTask(d,t);

	taskList[noOfTasks++].setTask(d,tempTime,cs, taskType);
	editCheck = 1;
	return true;
}

bool Schedular :: isValisdIndex(int index)
{
	if(index >= 0 && index < noOfTasks)
		return 1;
	return 0;
}

Time Schedular :: returnValidTimeToSetTask(const Date & d, const Time & t)
{
	Time labMouse = t;
	int counter = 0;

	int loopCount1 = t.getSecond();
	int loopCount2 = 59 - t.getSecond();

	while(counter <= loopCount1)
	{
		if(doesTaskExistOnDateAndTime(d,labMouse) == -1)
			return labMouse;
		labMouse.incSec(-1);
		counter++;
	}

	labMouse = t;
	counter = 0;
	while(counter <= loopCount2)
	{
		if(doesTaskExistOnDateAndTime(d,labMouse) == -1)
			return labMouse;
		labMouse.incSec();
		counter++;
	}
	return t;
}

bool Schedular :: removeTask(const Date &d)
{
	int size = numberOfTasksOnDate(d);
	if(size == 0)
		return false;
	
	int * indxing = new int[size];

	int j = 0;

	for(int i = 0 ; i < noOfTasks ; i++)
	{
		if(taskList[i].getDate().getDay() == d.getDay() && taskList[i].getDate().getMonth() == d.getMonth() && taskList[i].getDate().getYear() == d.getYear())
		{
			std :: cout << "Task " << j+1 << std :: endl;
			indxing[j] = i;
			displayTask(taskList[i]);
			j++;
		}
	}

	int choice;
	std :: cin >> choice;

	std :: cin.ignore();

	if(choice <= 0 && choice > size)
		return false;

	taskList[indxing[choice - 1]] = taskList[noOfTasks -1];
	noOfTasks--;
	editCheck = 1;
	return true;
}

bool Schedular :: removeTaskOnDateAndTimeOfType0(const Date &d, const int hour)
{
	int size = numberOfType0TasksOnDateAndHour(d,hour);
	if(size == 0)
		return false;
	
	int * indxing = new int[size];

	int j = 0;

	for(int i = 0 ; i < noOfTasks ; i++)
	{
		if(d == taskList[i].getDate() && hour == taskList[i].getTime().getHour() && taskList[i].getTaskType() == 0)
		{
			std :: cout << "Task " << j+1 << std :: endl;
			indxing[j] = i;
			displayTask(taskList[i]);
			j++;
		}
	}

	int choice;
	std :: cin >> choice;

	if(choice <= 0 && choice > size)
		return false;

	taskList[indxing[choice - 1]] = taskList[noOfTasks -1];
	noOfTasks--;
	std :: cin.ignore();
	editCheck = 1;

	return true;
}

bool Schedular :: removeTaskOnDateAndTimeOfType1(const Date &d)
{
	int size = numberOfType1TasksOnDate(d);
	if(size == 0)
		return false;
	
	int * indxing = new int[size];

	int j = 0;

	for(int i = 0 ; i < noOfTasks ; i++)
	{
		if(d.getDay() == taskList[i].getDate().getDay() && d.getMonth() == taskList[i].getDate().getMonth() && taskList[i].getTaskType() == 1)
		{
			std :: cout << "Task " << j+1 << std :: endl;
			indxing[j] = i;
			displayTask(taskList[i]);
			j++;
			std :: cout << std :: endl;
		}
	}

	int choice;
	std :: cin >> choice;
	std :: cin.ignore();
	if(choice <= 0 && choice > size)
		return false;

	taskList[indxing[choice - 1]] = taskList[noOfTasks -1];
	noOfTasks--;
	editCheck = 1;

	return true;
}
Task & Schedular :: editTaskType(const bool type,int & status)
{
	int size = totalNumberOfTypeTasks(type);

	if(size == 0)
	{
		status = 0;
		return Task();
	}

	int * idx = new int[size];
	int j = 0, choice;
	for(int i = 0 ; i < noOfTasks ; i++)
	{
		if(taskList[i].getTaskType() == type)
		{
			idx[j++] = i;
			cout << "\nTask # " << j << "\n" << taskList[i];
			cout << endl;
		}
	}
	cout << "The Task Number you want to Update : ";
	cin >> choice;

	if(!cin.good())
	{
		cin.clear();
		choice = 0;
	}
	cin.ignore();

	if(choice > 0 && choice <= j)
	{
		editCheck  = 1;
		status = 1;
		return taskList[idx[choice-1]];
	}
	return Task();
}

void Schedular :: removeTaskGenerally()
{
	int j = 0, choice;
	for(int i = 0 ; i < noOfTasks ; i++)
	{
			cout << "\nTask # " << j + 1 << "\n" << taskList[i];
			cout << endl;
			j++;
	}
	cout << "The Task Number you want to Update (If you do not want to update enter wrong value): ";
	cin >> choice;

	if(cin.badbit)
	{
		cin.clear();
	}
	cin.ignore();

	if(choice > 0 && choice <= j)
	{
		taskList[j - 1] =  taskList[noOfTasks -1];
		noOfTasks--;
		editCheck = 1;
	}
	return;

}

int Schedular :: totalNumberOfTypeTasks(bool taskType)
{	
	int i = 0 ;
	for(int j = 0 ; j < noOfTasks ; j++)
	{
		if(taskList[j].getTaskType() == taskType)
			i++;
	}
	return i;
}

bool Schedular :: displayTaskOnDate(const Date & d)
{
	int j = 0;
	for(int i = 0 ; i < noOfTasks ; i++)
	{
		if(taskList[i].getDate().getDay() == d.getDay() && taskList[i].getDate().getMonth() == d.getMonth() && taskList[i].getDate().getYear() == d.getYear())
		{
			std :: cout << "Task " << j+1 << std :: endl;
			displayTask(taskList[i]);
			j++;
		}
	}
	if(j > 0)
		return 1;
	else
		return 0;
}

bool Schedular :: displayType1TaskOnDate(const Date& d)
{
	int j = 0;
	for(int i = 0 ; i < noOfTasks ; i++)
	{
		if(d.getDay() == taskList[i].getDate().getDay() && d.getMonth() == taskList[i].getDate().getMonth() && d.getYear() >= taskList[i].getDate().getYear() && taskList[i].getTaskType() == 1)
		{
			std :: cout << "Task " << j+1 << std :: endl;
			displayTask(taskList[i]);
			j++;
		}
	}
	if(j > 1)
		return 1;
	return 0;
}

void Schedular :: displayTaskOnDateAndHour(const Date& d, int h)
{
	for(int i = 0 ; i < noOfTasks ;i++)
	{
		if(taskList[i].getDate() == d && taskList[i].getTime().getHour() == h)
		{
			displayTaskOnIndex(i);
			std :: cout << std :: endl;
		}
	}
}

void Schedular :: reSizeSchedule(int newSize)
{
	int count = 0;
	Task * newTaskList = new Task [newSize];
	for(int i = 0 ; i < newSize && i < noOfTasks ; i++)
	{
		newTaskList[i] = taskList[i];
		taskList[i].~Task();
		count++;
	}

	noOfTasks = count;
	delete [] taskList;
	taskList = 0;
	taskList = newTaskList;
	capacity = newSize;

	newTaskList = 0;
}

void Schedular ::  displayAllTasks()
{
	for(int i = 0 ; i < noOfTasks ; i++)
	{
		std :: cout << "Task " << i+1 << std :: endl;
		displayTask(taskList[i]);
	}
}

void Schedular :: displayTaskOnIndex(int index)
{
	if(!isValisdIndex(index))
		return;
	taskList[index].getDate().printFormat1();
	std :: cout << std :: endl;
	taskList[index].getTime().printTwentyFourHourFormat();
	std :: cout << std :: endl;
	taskList[index].getMessage().display();
	std :: cout << std :: endl;
}

int Schedular :: returnIndexOfSecondType1TaskOnDay(const Date & d)
{
	int i = 0;
	int x = 0;
	for( i ; i < noOfTasks && x < 2 ; i++)
	{
		if(d == taskList[i].getDate() && taskList[i].getTaskType() == 1)
			x++;
		else if(d.getDay() == taskList[i].getDate().getDay() && d.getMonth() == taskList[i].getDate().getMonth() && d.getYear() >= taskList[i].getDate().getYear() && taskList[i].getTaskType() == 1)
			x++;
	}
	if(x == 2)
		return i - 1;
	else
		return -1;
}

int Schedular :: returnIndexOfSecondType0TaskOnDay(const Date & d)
{
	int i = 0 ;
	int x = 0;
	for( i ; i < noOfTasks && x < 2 ; i++)
	{
		if(d == taskList[i].getDate() && taskList[i].getTaskType() == 0)
			x++;
	}
	if(x == 2)
		return i - 1 ;
	else
		return -1;
}

int Schedular :: returnIndexOfSecondType0TaskOnDayAndHour(const Date & d, const int hour)
{
	int i = 0 ;
	int x = 0;
	for( i ; i < noOfTasks && x < 2 ; i++)
	{
		if(d == taskList[i].getDate() && taskList[i].getTaskType() == 0)
		{
			if(hour == taskList[i].getTime().getHour())
				x++;
		}
	}
	if(x == 2)
		return i - 1 ;
	else
		return -1;
}

Schedular :: ~Schedular()
{
	if(editCheck)
		downloadFile();

	for(int i = 0 ; i < noOfTasks ; i++)
		taskList[i].~Task();

	delete [] taskList;
}

bool Schedular :: isTaskNull(const Task & t)
{
	if(t.getDate().getDay() == 1 && t.getDate().getMonth() == 1 && t.getDate().getYear() == 1900)
	{
		if(!t.getMessage().returnDataPointer())
			return 1;
		return 0;
	}
	return 1;
}

int Schedular :: totalNumberOfTaskOnDateAndHour(const Date & d, const int hour)
{
	int i = 0;
	for(int p = 0 ; p < noOfTasks ; p++)
	{
		if(d.getDay() == taskList[p].getDate().getDay() && d.getMonth() == taskList[p].getDate().getMonth() && taskList[p].getTime().getHour() == hour)
			i++;
	}
	return i;
}

Task & Schedular :: editTaskAtParticularDateAndTime(Date & d, int h,int & status)
{
	if(h < 0)
		h = 0;

	int size = totalNumberOfTaskOnDateAndHour(d,h);

	if(size == 0)
	{
		status = 0;
		return Task();
	}
	system("cls");
	int * idx = new int[size];

	int i = 0, choice;
	for(int p = 0 ; p < noOfTasks ; p++)
	{
		if(d.getDay() == taskList[p].getDate().getDay() && d.getMonth()== taskList[p].getDate().getMonth() && taskList[p].getTime().getHour() == h)
		{
			idx[i] = p;
			std :: cout << "Task # " << i+1 << '\n' << taskList[p];
			i++;
		}
	}

	cout << "The Task number want to update : ";
	cin >> choice;

	if(!cin.good())
		cin.clear();
	cin.ignore();


	if(choice > 0 && choice <= i)
	{
		status = 1;
		editCheck = 1;
		return taskList[idx[i - 1]];
	}
	return Task();
}