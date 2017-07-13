#ifndef CSTRING_H
#define CSTRING_H
#include<iostream>
class CString
{
	char * data;
	int size;

	int getSize(const char * c);
	int getSize(const char * c) const;
	void copyString(char * const dest, const char * const source);
	void copyStringToNull(char * const dest, const char * const source);
	int countAlike(const char ch);
	int countAlikeStrings(const char * const oldChar);
	int countTheCharB4anyDelim(const CString & c, const char * const delim);
	void deleteStr(char * str);
public :

	CString();
	CString(const char c);
    CString(const char * const c);
	int getLength();
	int getLength() const;
	void display() const;
	int find(const char * const subStr, int start = 0);
	int find(const char ch, int start = 0);
	int isEmpty();
	void input();
	const char &at(int index)const;
	char &at(int index);
	~CString();
	int insert(const int index, const char ch);
	int insert(const int index, const char * const subStr);
	int remove(const int index, int count = 1);
	int remove(const char ch);
	void replace(const char ch);
	int replace(const char oldChar, const char newChar);
	int replace(const char * const oldChar, const char * const newChar);
	void trim();
	void trimRight();
	void trimLeft();
	void makeUpper();
	static CString toCString(int num);
	void makeLower();
	void reverse();
	void reSize(int add);
	void concatEqual(char * s2);
	void concatEqual(const CString & s);
	int isEqual(const char * const c);
	int IsEqual(const CString & str);
	CString substring(int start, int size);
	CString(const CString & c2);
	CString left(int count);
	CString right(int count);
	CString concat(const CString & c2);
	CString concat(const char * c2);
	CString tokenize(const char * delim);
	void operator=(const CString & cs);
	bool isSubString(CString & );
	bool isSubString(char * );
	char * returnDataPointer();
};
std :: ostream & operator<<(std :: ostream & os, const CString & cs);
std :: istream & operator >>(std :: istream & is, CString & cs);
#endif