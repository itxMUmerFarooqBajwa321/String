#ifndef STRING_H
#define STRING_H
#include<iostream>
using namespace std;
class Date;
class String
{
	char* data;
	int size;
	bool isValidIndex(const int index) const;
	bool isStringASignedNumber() const;
	bool isStringANegativeNumber() const;
	bool isStringAFloatNumber() const;
	bool isStringAnIntegralNumber() const;
	int findNoOfOccurences(String subStr, const int start = 0) const;
	static int getStrLen(const char* ch);
	static void copyCharArray(const char* src, char* dest);
	static void swapCharacters(char& a, char& b);
	static void myMemMove(void* src, void* dest, int byteCount);
	bool operator && (const String& s2) const;
	bool operator || (const String& s2)const;
public:
	String();
	String(const char c) ;
	String(const char* ch) ;
	String(const String& ref);
	String(String&& ref);
	int getLength() const;
	void input();
	void display() const;
	char& operator [](const int index);
	const char& operator [](const int index) const;
	bool operator !() const; 
	int operator == (const String& s2) const;
	bool operator > (const String& s2)const;
	bool operator < (const String& s2) const;
	bool operator >= (const String& s2) const;
	bool operator <= (const String& s2) const;
	bool operator != (const String& s2) const;
	int getSize() const;
	void reSize(int newSize);
	int find(const String& subStr, const int start = 0) const;
	void remove(const int index, const int count = 1);
	void insert(const int index, const String& subStr);
	int replace(const String & old, const String & newSubStr);
	void makeUpper();
	void makeLower();
	void reverse();
	void trimRight();
	void trimLeft();
	void trim();
	void shrink();
	String left(const int count);
	String right(const int count);
	explicit operator long long int () const;
	explicit operator double() const;
	explicit operator bool() const;
	String operator +(const String& s2) const;
	void operator += (const String& s2);
	String& operator = (const String& ref);   // deep copy assignment
	String& operator =(String&& ref);    // assignment which moves resources
	String & operator =(const long long int num);
	String operator () (const String& delim);
	//String& operator = (const double num);
	~String();
};
ostream& operator << (ostream& out, const String& str);
istream& operator >> (istream& in , const String& str);
#endif