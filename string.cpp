#include <iostream>
#include <assert.h>
#include <string.h>
#include <cstdlib>
#include <cstdio>
class CSTRING
{
private:
	char *str;
	unsigned int size;
public:
	CSTRING();
	~CSTRING();
	CSTRING(const CSTRING& ita);
	CSTRING& operator +=(const CSTRING & it);
	CSTRING& operator =(const CSTRING & it);
	int		 operator >(const CSTRING & it);
	int		 operator <(const CSTRING & it);
	int		 operator==(const CSTRING & it);
	CSTRING& operator -=(const CSTRING & it);
	void move(char *start,int mis);
	void scan();
	void print();
	char* find(char *s);
	void increase(int sz);
};
void CSTRING:: move(char *start,int mis)
{
	unsigned int i;
	for(i = start - str;i < strlen(str) - mis; i++)
	{
		str[i] = str[i + mis];
	}
	for(; i < strlen(str); i++)
	{
		str[i] = '\0';
	}
};
void CSTRING::increase(int sz)
{
	char *str1;
	str1 = new char[size];
	memcpy(str1, str, strlen(str));
	delete[] str;
	str = str1;
};
int CSTRING:: operator >(const CSTRING & it)
{
	return (strlen(str) > strlen(it.str))? 1: 0;
};
int CSTRING:: operator <(const CSTRING & it)
{
	return (strlen(str) < strlen(it.str))? 1: 0;
};
int CSTRING:: operator ==(const CSTRING & it)
{
	return (strcmp(str, it.str));
};
CSTRING& CSTRING:: operator -=(const CSTRING & it)
{
	char *helper;
	helper = strstr(str, it.str);
	int a = strlen(it.str);	
	while(helper != NULL)
	{
		this -> move(helper, a);
		helper += a;
		helper = strstr(helper, it.str);
	}
	return *this;
};
CSTRING& CSTRING:: operator =(const CSTRING & it)
{
	if(strlen(str) < strlen(it.str))
	{	
		this -> size *= strlen(it.str);
		char *a = new char [this -> size];
		delete[] str;
		this -> str = a;
		//str = (char*)realloc(str, this -> size * sizeof(char));
	}
	unsigned int size1;
	for (size1 = 0; size1 < strlen(it.str); size1++)
		this -> str[size1] = it.str[size1];
	this -> str[size1 + 1] = it.str[size1 +1];
	return *this;
};
char* CSTRING::find(char *s)
{
	return strstr(str,s);
}; 
void CSTRING::print()
{
	std::cout << str << std::endl;
}; 
void CSTRING::scan()
{	
	std::cin >> str;
};
CSTRING::CSTRING()
{
	size = 20;
	str = new char [20];
	std::cout<< "C" << std::endl;
};
CSTRING& CSTRING::operator +=(const CSTRING &it)
{ 
	unsigned int a , b;
	a = strlen(str);
	b = strlen(it.str);
	if((a + b) > this -> size)
	{	
		size *= strlen(it.str);
		increase(size);
	}
	memcpy(str + a, it.str, b + 1);
	return *this;
};
 CSTRING operator + (const CSTRING &s, const CSTRING &b)
 {
 	CSTRING a;
 	a += s;
 	a += b;
 	a.print();
 	return a;
 }
CSTRING::~CSTRING()
{
	delete [] str;
	size = 0;
	std::cout<< "D" << std::endl;
};

int main()
{
	CSTRING str1, str2, str3,  str4;
	str1.scan();
	str2.scan();
	//str3.scan();
	str3 = str1  + str2;
	//str1 += str2;

	//str1.print();
	//str2.print();
	str3.print();
	std::cout<<(str3 == str2)<<std::endl;
	//str1 = str1 + str2;
	return 0;
}
