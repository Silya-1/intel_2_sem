#include <iostream>
#include <cstdio>
#include  <cstring>
#include <cmath>
#define size 2000
double get_num();
char* skip_space();
double get_num();
double get_p();
double getexp();
double getres();
char *s;
int main()
{
	FILE*  file = fopen("calc.txt", "r");
	char *strt = new char[size]; 
	fgets(strt,size,file);
	s = strt;
	std::cout<< getres()<<::std::endl;
	delete[] strt;
	return 0;
}

char* skip_space()
{
	while(*s == ' ' || *s == '\n')
		s++;
	return s;
}
double get_num()
{
	int show_ = 0;
  	s = skip_space();
  	if(*s == '-')
	{
  		show_ = -1;
  		s++;
  	}
  	else 
  		show_ = 1;
	  s = skip_space();
	  double res = 0;
	  while(*s >= '0' && *s <= '9')
	  {
	  	res = res * 10 + *s - '0';	
	  	s++;
	  }
	  return res * show_;
}

double get_p()
{
	double a = 0;
	s = skip_space();
	if(*s == '(')
	{
		s++;
		a = getexp();
	}
	else if(*s >= '0' && *s <= '9')
	{
		a = get_num();
		std::cout<<a<<std::endl;
	}
	else 
	{
		if (strncmp(s, "sin", 3) == 0)
		{
			s += 3;
			a = sin(getexp());
			return a;
		}
		if (strncmp(s, "cos", 3) == 0)
		{
			s += 3;
			a = cos(getexp());
			return a;
		}
		if (strncmp(s, "sqrt", 4) == 0)
		{
			s += 3;
			a = sqrt(getexp());
			return a;
		}
	}
	return a;
}
double mul_div()
{
	s = skip_space();
	double a = get_p();
	s = skip_space();
	if(*s == '*')
	{
		s++;
		a *= get_p();
		s++;
	}
	else if(*s == '/')
	{
		s++;
		a /= get_p();
		s++;
	}
	else if(*s == '^')
	{
		s++;
		int i = get_p();
		std::cout << i<< " " << a<< " this is i and a"<<std::endl;
		for (int j = 1; j < i; j++)
			a *= i;
		if(i == 0)
			a = 1;
		std::cout << i<< " " << a<< " this is i and a"<<std::endl;
	}
	return a;
}
double getexp()
{
	double a = 0; 
	a = mul_div();
	s = skip_space();
	if(*s == '+')
	{
		s++;
		a += mul_div();
	}
	else if(*s == '-')
	{
		s++;
		a -= mul_div();
	}
	if(*s == ')')
		s++;	
	s = skip_space();
	return a;
}
double getres()
{
	double a = 0;
	while(*s != '\0')
		a += getexp();
	return a;
}