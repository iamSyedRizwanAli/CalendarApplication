#ifndef TASK_H
#define TASK_H
#include"Date.h"
#include"Time.h"
#include"CString.h"
class Task
{
	Date taskDate;
	Time taskTime;
	CString taskMsg;
	bool taskType;
	Task(Task &t);
public:
	Task();
	Task(const Date & d, const Time & t,const CString &m, bool taskType = 0);
	void setTask(const Date & d, const Time & t,const CString &m, bool taskType = 0);
	void updateDate(const Date & nd);
	void updateTime(const Time & nt);
	void updateMessage(const CString &m);
	void updateTaskType(const bool type);
	Date getDate() const;
	Time getTime() const;
	CString getMessage() const;
	bool getTaskType() const;
	~Task();
	void operator=(const Task & tsk);
	void display();
};
std :: ostream & operator << (std :: ostream & os, Task & t);
#endif