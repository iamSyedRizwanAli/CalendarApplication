#include"QoutationList.h"
#include"CString.h"
#include<iomanip>
#include<iostream>
#include<fstream>
using namespace std;

bool QuotationList :: editCheck = 0;

QuotationList :: QuotationList()
{
	quote = new CString[45];
	author = new CString[45];
	check = new int[30];
	numOfQuotations = 0;
	capacity = 45;
	checkCount = 0;
	QuotationFile();
}

QuotationList :: QuotationList(int cap)
{
	if(cap <= 45)
		QuotationList();
	else
	{
		quote = new CString[cap];
		author = new CString[cap];
		capacity = cap;
		numOfQuotations = 0;
		checkCount = 0;
	}
}

QuotationList :: QuotationList(const QuotationList & list)
{
	numOfQuotations = list.numOfQuotations;
	capacity = list.capacity;
	quote = new CString[capacity];
	author = new CString[capacity];
	for(int i = 0 ; i < list.numOfQuotations ; i++)
	{
		quote[i] = list.quote[i];
		author[i] = list.quote[i];
	}
}

void QuotationList :: addQuotation(const CString & qoute, const CString & authr)
{
	if(numOfQuotations == capacity)
		reSizeList(capacity * 2);
	quote[numOfQuotations] = qoute;
	author[numOfQuotations] = authr;
	numOfQuotations++;
	editCheck = 1;
}

bool QuotationList :: isValidIndex(int i)
{
	if(i >= 0 && i < numOfQuotations)
		return 1;
	return 0;
}

bool QuotationList :: displayQuotation(int i)
{
	if(!isValidIndex(i))
		return false;

	quote[i].display();
	cout << " - " ;
	author[i].display();
	return true;
}

int QuotationList :: getRandomQuotationFromTheListToDisplayOnClock()
{
	srand(time(0));
	int index = rand() % capacity;

	if(checkCount == 30)
		checkCount = 0;

	for(int i = 0 ; i < checkCount ; i++)
	{
		if(check[i] == index)
			index = rand() % 50;
	}

	check[checkCount] = index;
	checkCount++;
	return index;
}

void QuotationList :: QuotationFile()
{
	ifstream ifs("qoutes.txt");

	for(int i = 0 ; i  < capacity && !ifs.eof() ; i++)
	{
		inputFromFile(ifs,i);
		numOfQuotations++;
	}
	ifs.close();
}

void QuotationList :: inputFromFile(std :: ifstream & ifs, int i)
{
		char s;
		ifs >> noskipws >> s;
	
		while(s == '\n')
			ifs >> noskipws >> s;
		
		while(s != '-')
		{
			quote[i].concatEqual(s);
			ifs >> noskipws >> s;
		}
		ifs.clear();
		ifs >> noskipws >> s;
		while(s != '\n' && !(ifs.eof()))
		{
			author[i].concatEqual(s);
			ifs >> noskipws >> s;
		}
}

void QuotationList :: operator= (const QuotationList & list)
{
	if(this == &list)
		return;
	if(author && quote)
		this -> ~QuotationList();

	numOfQuotations = list.numOfQuotations;
	capacity = list.capacity;
	quote = new CString[capacity];
	author = new CString[capacity];
	for(int i = 0 ; i < list.numOfQuotations ; i++)
	{
		quote[i] = list.quote[i];
		author[i] = list.quote[i];
	}
}

void QuotationList :: updateQuotaionFile()
{
	ofstream ofs("temp.txt", ios :: app);
	for(int i = 0 ; i < numOfQuotations ; i++)
	{
		ofs << '\n';
		ofs << quote[i].returnDataPointer();
		ofs << "-" ;
		ofs << author[i].returnDataPointer();
	}
	ofs.close();
	remove("qoutes.txt");
	rename("temp.txt","qoutes.txt");
}

QuotationList :: ~QuotationList()
{
	if(editCheck)
		updateQuotaionFile();

	for(int i = 0 ; i < numOfQuotations ; i++)
	{
		quote[i].~CString();
		author[i].~CString();
	}
	delete [] quote;
	delete [] author;
	quote = 0;
	author = 0;
	numOfQuotations = 0;
	capacity = 0;
}

void QuotationList :: reSizeList(int newSize)
{
	QuotationList qls(newSize);
	for(int i = 0 ; i < capacity ; i++)
	{
		qls.author[i] = author[i];
		qls.quote[i] = quote[i];
	}
	qls.numOfQuotations = numOfQuotations;
	this -> ~QuotationList();
	*this = qls;
	editCheck = 1;
}

int QuotationList :: countAlikeStrings(const CString & data ,const CString & string)
{
	int str2Size = string.getLength();
	int count = 0, count2 = 0, j = 0, k, l = 0;
	int i = 0;
	int size = data.getLength();

	while(i < size)
	{
		if(data.at(i) == string.at(j))
		{
			while(data.at(i) == string.at(j))
			{
				k = i;
				while(l < str2Size && data.at(i)==string.at(j))
				{
					count++;
					j++;
					i++;
					l++;
				}
				if(count == str2Size)
				{
					count2++;
				}
				j = 0;
				l = 0;
				count = 0;
			}
		}
		i++;
	}
	return count2;
}

void QuotationList :: displayAuthorWise(const CString & authr)
{
	int * index = new int [numOfQuotations];
	int j = 0;
	for(int i = 0 ; i < numOfQuotations ; i++)
	{
		if(countAlikeStrings(author[i],authr) > 0)
		{
			index[j++] = i;
			cout << "Quotation number " << j << " ";
			quote[i].display();
			cout << "-";
			author[i].display();
			cout << endl;
		}
	}
}

void QuotationList :: displayQuotation(const CString & qote)
{
	int * index = new int [numOfQuotations];
	int j = 0;
	for(int i = 0 ; i < numOfQuotations ; i++)
	{
		if(countAlikeStrings(quote[i],qote) > 0)
		{
			index[j++] = i;
			cout << "Quotation number " << j << " ";
			quote[i].display();
			cout << "-";
			author[i].display();
			cout << endl;
		}
	}
}

void QuotationList :: removeQuotation(const CString & qote)
{
	int * index = new int [numOfQuotations];
	int j = 0, choice;
	for(int i = 0 ; i < numOfQuotations ; i++)
	{
		if(countAlikeStrings(quote[i],qote) > 0)
		{
			index[j++] = i;
			cout << "Quotation # " << j << " ";
			quote[i].display();
			cout << endl;
		}
	}
	cout << "The Quotation Number you want to Remove : ";
	cin >> choice;
	if(choice > 0 && choice <= j)
	{
		quote[index[choice-1]] = quote[numOfQuotations-1];
		author[index[choice-1]] = author[numOfQuotations-1];
		numOfQuotations--;
		editCheck = 1;
	}
	if(cin.badbit)
		cin.clear();
	cin.ignore();
}

void QuotationList :: removeQuotation()
{
	int choice, i;
	for(i = 0 ; i < numOfQuotations ; i++)
	{
		cout << "Quotation # " << i + 1 << " \n";
		cout << quote[i] << endl << "  ~"<< author[i] << "\n\n";
 	}
	cout << "The Quotation Number you want to Remove : ";
	cin >> choice;
	if(choice > 0 && choice <= i)
	{
		quote[choice-1] = quote[numOfQuotations-1];
		author[choice-1] = author[numOfQuotations-1];
		numOfQuotations--;
		editCheck = 1;
	}
	if(cin.badbit)
		cin.clear();

	cin.ignore();
}