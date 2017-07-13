#include<iostream>
#include"Task.h"
#include"Date.h"
#include"Time.h"
#include"CString.h"

Task ::  ~Task()
{
	taskMsg.~CString();
}

Task :: Task()
{
	taskDate.setDate(1,1,1900);
	taskTime.setTime(0,0,0);
	CString newString;
	taskType = 0;
}

void Task :: display()
{
	std :: cout << "Message : " << taskMsg << "\nDate : " << taskDate << "\nTime : " << taskTime << "\nTask Type : " << taskType << "\n" ;
}

std :: ostream & operator << (std :: ostream & os, Task & t)
{
	t.display();
	return os;
}

Task :: Task(const Date & d, const Time & t,const CString &m, bool type):taskDate(d) , taskTime(t), taskMsg(m), taskType(type)
{
}


void Task :: setTask(const Date & d, const Time & t, const CString & cs, bool type)
{
	this ->taskDate = d;
	this ->taskTime = t;
	this -> taskMsg = cs;
	taskType = type;
}

void Task :: updateDate(const Date & nd)
{
	taskDate.setDate(nd.getDay(), nd.getMonth(), nd.getYear());
}

void Task :: updateTime(const Time & nt)
{
	taskTime.setTime(nt.getHour(),nt.getMinute(),nt.getSecond());
}

void Task :: updateMessage(const CString &m)
{
	taskMsg = m;
}

void Task :: updateTaskType(const bool type)
{
	taskType = type;
}

Date Task :: getDate() const
{
	return taskDate;
}

Time Task :: getTime() const
{
	return taskTime;
}

CString Task :: getMessage() const
{
	return taskMsg;
}

bool Task :: getTaskType() const
{
	return taskType;
}

void Task ::  operator=(const Task & tsk)
{
	taskTime = tsk.taskTime;
	taskDate = tsk.taskDate;
	taskMsg = tsk.getMessage();
	taskType = tsk.getTaskType();
}