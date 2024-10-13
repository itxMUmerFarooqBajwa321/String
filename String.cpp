#include "String.h"
String::String()
{
	data = nullptr;
	size = 0;
}
String::String(const char c) :String()
{
	if (!c)
	{
		size = 1;
		data = new char{ '\0' };   // same as data=new char [1] {'\0'};
		return;
	}
	size = 2;
	data = new char[size] {c, '\0'};
}
String::String(const char* ch) : String()
{
	if (ch)
	{
		size = getStrLen(ch) + 1;
		data = new char[size];
		copyCharArray(ch, data);
	}
}
String::String(const String& ref) :String()
{
	if (!ref.data || ref.size == 0)
	{
		return;
	}
	size = ref.size;
	data = new char[size];
	copyCharArray(ref.data, data);
}
String::String(String&& ref) : String()
{
	if (this == &ref || !ref)   //to save from s1 = (move)s1; ie. movement of resources in itself as below used destructor will make dangle data (a data member ) of ref obj which is also calling obj coz both obj are same.
	{
		return;
	}
	size = ref.size;
	data = ref.data;   // now data member data of both Strings now  point the same char array.
	ref.size = 0;
	ref.data = nullptr;   // Now break the connection of char array with data member data 0of old String by making it nullptr.
	// in this way now that array is pointed by data ( a data member) of only new String. Connection with old String is break down .
	// And so resource i.e. heap memory array is moved / shifted from one String to other.
}
int String::getLength() const
{
	return (getStrLen(data));
}
bool String::isValidIndex(const int index) const
{
	if (data && (index >= 0) && (index < getLength()))
	{
		return true;
	}
	return false;
}
bool String::isStringASignedNumber() const
{
	return (data[0] == '-' || data[0] == '+');
}
bool String::isStringANegativeNumber() const
{
	if (!isStringAFloatNumber())   // yani pehly dekh lein k String aik number b  ya nhi h?
	{
		exit(0);
	}
	return (data[0] == '-');
}
bool String::isStringAFloatNumber() const
{
	if (!*this)
	{
		return false;
	}
	bool floatStatus = true;
	int length = getLength();
	int i = 0;
	bool decimalPointStatus = false;
	if (isStringASignedNumber())
	{
		i++;
	}
	while (i < length && floatStatus)
	{
		if (data[i] == '.' && !decimalPointStatus)
		{
			decimalPointStatus = true;
		}
		else if (data[i] >= '0' && data[i] <= '9')
		{
			i++;    // this increment in i is necessary here coz due to continue statement control will not go to i++; which after else statement. instead it will go for a new loop/cycle.
			continue;
		}
		else
		{
			floatStatus = false;
		}
		i++;
	}
	return floatStatus;
}
bool String::isStringAnIntegralNumber() const
{
	if (!data)
	{
		return false;
	}
	int i = 0;
	if ( !(data[i] >= '0' && data[i] <= '9') && !( isStringASignedNumber() ) )   //to check 1st character. it may be sign ie + or -.
	{
		return false;
	}
	i++;
	while (data[i])
	{
		if (!(data[i] >= '0' && data[i] <= '9'))
		{
			return false;
		}
		i++;
	}
	return true;
}
int String::getStrLen(const char* ch)
{
	int i = 0;
	while (ch[i])
	{
		i++;
	}
	return i;
}
void String::copyCharArray(const char* src, char* dest)
{
	int i = 0;
	if (!src)
	{
		dest[0] = '\0';
		return;
	}
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
void String::swapCharacters(char& a, char& b)
{
	a = a + b;
	b = a - b;
	a = a - b;
}
void String::myMemMove(void* src, void* dest, int byteCount)
{
	const char* s = (const char*)src;
	char* d = (char*)dest;
	for (int i = byteCount - 1; i >= 0; i--)
	{
		d[i] = s[i];
	}
}
void String::input()
{
	if ( ! (*this) )
	{
		reSize(10);
	}
	char temp;
	int i = 0;
	while (cin.get(temp) && temp != '\n')
	{
		if (i == (size - 1))
		{
			reSize(size + 10);
		}
		data[i] = temp;
		i++;
	}
	data[i] = '\0';
	shrink();
}
void String::display() const
{
	if (*this)
	{
		cout << data;
	}
}
char& String::operator [](const int index)
{
	if (! isValidIndex(index))
	{
		exit(0);
	}
	return data[index];
	//the function with return type const is to use as a setter 
	//so i should be allowed to place a char within size anywhere ie within length or out the length both.
	// like String s1{"Ali"}; 
	// s1.reSize(5);
	//s1.at(3)='z';
	//s1.at(4)='\0';
	// so in this case index of at(3) and at(4) ie 3 & 4 is outside length
	// so bound checking will be with size , not with length otherwise at() will not work.
	// bound checking with length will be in const char & at(int) const where i just want to access the char 
}
const char& String::operator [](const int index) const
{
	if (!isValidIndex(index))
	{
		exit(0);
	}
	return data[index];
}
bool String::operator !() const
{
	if ((!data) || (!getLength()))
	{
		return true;
	}
	return false;
}
int String::getSize() const
{
	return size;
}
void String::reSize(int newSize)
{
	if (newSize <= 0)
	{
		this->~String();
		return;
	}
	char* temp = new char[newSize];
	copyCharArray(data, temp);
	this->~String();
	size = newSize;
	data = temp;
}
int String::findNoOfOccurences(String subStr, const int start) const   //it will tell the no. of occuerneces of substr in String
{
	int count = 0, startingIndex = start;
	int strLen = getLength();
	int subStrLen = subStr.getLength();
	bool equalStatus = false;
	while (startingIndex < strLen)
	{
		int j = 0;
		do
		{
			if (data[startingIndex] == subStr.data[j])
			{
				equalStatus = true;
				j++;
			}
			else
			{
				equalStatus = false;
			}
			startingIndex++;
		} 
		while ((j < subStrLen) && (equalStatus));
		if ((j == subStrLen) && (equalStatus))
		{
			count++;
		}
	}
	return count;
}
int String::find(const String& subStr, const int start ) const
{
	int index = -1;
	int strLen = getLength();
	int subStrLen = subStr.getLength();
	bool equalStatus = false;
	int counter = 0;
	for (int i = start; i < strLen; )
	{
		i = i - counter;
		int j = 0;
		do
		{
			if (data[i] == subStr.data[j])
			{
				equalStatus = true;
				j++;
			}
			else
			{
				equalStatus = false;
			}
			i++;
		} 
		while ((j < subStrLen) && (equalStatus));
		if ((j == subStrLen) && (equalStatus))
		{
			return (i - j);
		}
		counter++;
	}
	return -1;
}
void String::remove(const int index, const int count)
{
	int strLen = getLength();
	if ((index + count) > strLen)
	{
		return;
	}
	int i = index;
	while ((i < (index + count)) && (data[i + count]))
	{
		data[i] = data[i + count];
		i++;
	}
	while (i < (strLen - count))
	{
		data[i] = data[i + count];
		i++;
	}
	data[i] = '\0';
	//i can use copyCharArray() here in place of last loop
	shrink();
}
void String::insert(const int index, const String& subStr)
{
	if ((!subStr) || (index >= getSize()))
	{
		return;
	}
	int subStrLen = subStr.getLength();
	int strLen = getLength();
	if (getSize() < (strLen + subStrLen + 1))
	{
		reSize(strLen + subStrLen + 1);
	}
	myMemMove(&(data[index]), &(data[index + subStrLen]), strLen - index);
	myMemMove(subStr.data, &(data[index]), subStrLen);
	data[strLen + subStrLen] = '\0';
	shrink();
}
int String::replace(const String& old, const String& newSubStr)
{
	int strLen = getLength();
	int replaceCount = 0;   //replaceCount means no. of replacements of old String
	for (int i = 0; i < strLen; i++)
	{
		int index = find(old);
		if (index >= 0)
		{
			remove(index, old.getLength());
			insert(index, newSubStr);
			i = i + newSubStr.getLength() - 1; // subtract 1 coz after this block i++ of for loop will also execute.
			replaceCount++;
		}
		strLen = getLength();    //strLen is also changing due to removing and inserting characters in array of calling String.
	}
	return replaceCount;
}
int String::operator == (const String& s2) const
{
	int strLenA = getLength(), strLenB = s2.getLength();
	if (strLenA != strLenB)
	{
		return (strLenA > strLenB) ? 1 : -1;
	}
	int i = 0;
	while (i < strLenA)
	{
		if (data[i] != s2.data[i])
		{
			return (data[i] > s2.data[i]) ? 1 : -1;
		}
		i++;
	}
	return 0;
}
bool String::operator > (const String& s2)const
{
	return ((*this == s2) > 0);
}
bool String::operator < (const String& s2)const
{
	return ((*this == s2) < 0);
}
bool String::operator >= (const String& s2)const
{
	return ((*this == s2) >= 0);
}
bool String::operator <= (const String& s2)const
{
	return ((*this == s2) <= 0);
}
bool String::operator != (const String& s2) const
{
	return !((*this == s2)==0);
}
void String::makeUpper()
{
	if (!(*this))
	{
		return;
	}
	int strLen = getStrLen(data);
	for (int i = 0; i < strLen; i++)
	{
		if (data[i] >= 'a' && data[i] <= 'z')
		{
			data[i] = data[i] - ('a' - 'A');
		}
	}
}
void String::makeLower()
{
	if (!(*this))
	{
		return;
	}
	int strLen = getStrLen(data);
	for (int i = 0; i < strLen; i++)
	{
		if (data[i] >= 'A' && data[i] <= 'Z')
		{
			data[i] = data[i] + ('a' - 'A');
		}
	}
}
void String::reverse()
{
	int strLen = getLength();
	for (int i = 0; i < (strLen / 2); i++)
	{
		swapCharacters(data[i], data[strLen - i - 1]);
	}
}
void String::trimRight()
{
	int i = getLength() - 1;
	while (data[i] == ' ' || data[i] == '\n' || data[i] == '\t')
	{
		i--;
	}
	i = i + 1;
	data[i] = '\0';
	shrink();
}
void String::trimLeft()
{
	int i = 0;
	while (data[i] == ' ' || data[i] == '\n' || data[i] == '\t')
	{
		i++;
	}
	remove(0, i);
}
void String::trim()
{
	trimLeft();
	trimRight();
}
void String::shrink()
{
	reSize(getLength() + 1);
}
String String::left(const int count)   // why didn't we make this function const?
{
	if (!(data && isValidIndex(count)))   // >= with 0 so that left(0) will not execute exit(0). instead it will return empty String.
	{
		exit(0);
	}
	String st{ *this };
	st.data[count] = '\0';
	st.shrink();
	return st;
}
String String::right(const int count)
{
	if (!(data && (count >= 0 && count <= getLength())))  // >= with 0 coz we do not want to execute exit(0) at right(0). that's why....
	{
		exit(0);
	}
	String st{ "" };
	st.reSize(count + 1);
	copyCharArray(&(data[getLength() - count]), st.data);
	return st;
}
String::operator long long int () const
{
	if (!isStringAFloatNumber())
	{
		exit(0);
	}
	int i = 0;
	if (isStringASignedNumber())  // skip sign character while concatinating number
	{
		i++;
	}
	long long int num = 0;
	while (data[i] && data[i]!='.')
	{
		num = num * 10 + data[i] - '0';
		i++;
	}
	return (isStringANegativeNumber()) ? (-1) * num : num;
}
String::operator double() const
{
	if (!isStringAFloatNumber())
	{
		exit(0);
	}
	double num = 0;
	int i = 0, length = getLength();
	i = (isStringASignedNumber()) ? i + 1 : i;   // if number has + or - at 1st charcter , skip it while concatinating the number.
	while (i < length && data[i] != '.')     //concatination of integral part i.e. number before decimal point
	{
		num = num * 10 + (data[i] - '0');
		i++;
	}
	if (i == length)
	{
		return (isStringANegativeNumber()) ? num * (-1) : num;
	}
	i++;   //to skip decimal point (.) for concatination of number.
	float multiple = 0.1;
	while (i < length)
	{
		num = num + ((data[i] - '0') * multiple);
		multiple = multiple / 10.0;
		i++;
	}
	return (isStringANegativeNumber()) ? (-1) * num : num;
}
String::operator bool() const
{
	return !(!*this);
}
String String::operator +(const String& s2) const
{
	if ((!data) || (!s2.data))
	{
		exit(0);
	}
	if (s2.getLength() == 0)
	{
		return *this;
	}
	String str{ *this };
	str.reSize(getLength() + s2.getLength() + 1);
	copyCharArray(s2.data, &((str.data)[getLength()]));
	return str;
}
void String::operator += (const String& s2)
{
	if (!data || !s2)
	{
		return;
	}
	if (size < (getLength() + s2.getLength() + 1))
	{
		reSize(getLength() + s2.getLength() + 1);
	}
	copyCharArray(s2.data, &(data[getLength()]));
}
bool String::operator && (const String& s2) const
{
	return ((bool)(*this) && (bool)s2);
}
bool String::operator || (const String& s2) const
{
	return ((bool)*this || (bool)s2);
}
String & String::operator =(const long long int num)
{
	if (!data)
	{
		size = 10;
		data = new char[size];
	}
	long long int temp = num;
	if (num < 0)
	{
		temp = -1 * temp;
	}
	int i = 0;
	while (temp)
	{
		if (!(i < size))
		{
			reSize(size + 10);
		}
		data[i] = (temp % 10) + '0';
		temp = temp / 10;
		i++;
	}
	if (num < 0)
	{
		data[i] = '-';
		i++;
	}
	if (num == 0)
	{
		data[i] = '0';
		i++;
	}
	data[i] = '\0';
	shrink();
	reverse();
	return *this;
}
String& String::operator = (const String& ref)
{
	if (this == &ref)
	{
		return *this;
	}
	if (!ref.data || ref.size == 0)
	{
		exit(0);
	}
	this -> ~String();
	size = ref.size;
	data = new char[size];
	copyCharArray(ref.data, data);
	return *this;
}
String& String::operator =(String&& ref)
{
	if (this == &ref)   //to save from s1 = (move)s1; ie. movement of resources in itself as below used destructor will make dangle data (a data member ) of ref obj which is also calling obj coz both obj are same.
	{
		return *this;
	}
	if (!ref.data)
	{
		exit(0);
	}
	this->~String();
	size = ref.size;
	data = ref.data;	 // now data member data of both Strings now  point the same char array.
	ref.size = 0;
	ref.data = nullptr;
	return *this;
}
String String::operator () (const String& delim)
{
	int i = 0;
	int strLen = getLength();
	while (i < strLen && (delim.find(data[i]) >= 0) )
	{
		i++;
	}
	if (i);
	exit(0);
}
String::~String()
{
	if (!data)
	{
		return;
	}
	delete[] data;
	data = nullptr;
	size = 0;
}
ostream& operator << (ostream& out, const String& str)
{
	str.display();
	return out;   //also can return cout coz out and cout are two dif names of same object of ostream class
}
istream& operator >> (istream& in,  String& str)
{
	str.input();
	return in;   //also can return cin as like in >> operator overloading.
}
