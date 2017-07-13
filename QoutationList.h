#ifndef QUOTATIONLIST_H
#define QUOTATIONLIST_H
#include"CString.h"
class QuotationList
{
	CString * quote;
	CString * author;
	int * check;
	int checkCount;
	int numOfQuotations;
	int capacity;
	static bool editCheck;

	void reSizeList(int newSize);
	int countAlikeStrings(const CString & quoteOrAuthor, const CString & string);
	int findTheStringHavingTheString(const CString & cs);
	void displayAuthorWise(const CString & author);
	void displayQuotation(const CString & quote);
	QuotationList(const QuotationList & quotlist);
	void operator= (const QuotationList & quotlist);
	void QuotationFile();
	bool isValidIndex(int index);
	
	void updateQuotaionFile();
	void inputFromFile(std :: ifstream & ifs, int num);
public:
	QuotationList();
	QuotationList(int cap);
	bool displayQuotation(int index);
	int getRandomQuotationFromTheListToDisplayOnClock();
	void addQuotation(const CString & qoute, const CString & author = "Anonymous");
	void removeQuotation();
	void removeQuotation(const CString & quote);
	~QuotationList();
};
#endif