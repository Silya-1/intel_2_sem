#include <iostream>
#include <cstdio>
#include  <cstring>
#include <cmath>
#define size 2000
class CCALC
{
private:
	char *s;
public:
	CCALC(char *k);
	~CCALC();
	char* skip_space();
	double get_num();
	double get_p();
	double getexp();
	double getres();
	double mul_div();
};
CCALC::CCALC(char *srs)
{
	s = srs;
};
CCALC::~CCALC()
{
	s = NULL;
}
int main()
{
	FILE*  file = fopen("calc.txt", "r");
	char *strt = new char[size]; 
	fgets(strt,size,file);
	CCALC calc(strt);
	std::cout<< calc.getres()<<::std::endl;
	delete[] strt;
	return 0;
}

char* CCALC::skip_space()
{
	while(*s == ' ' || *s == '\n')
		s++;
	return s;
}
double CCALC::get_num()
{
	int show_ = 0;
  	s = this -> skip_space();
  	if(*s == '-')
	{
  		show_ = -1;
  		s++;
  	}
  	else 
  		show_ = 1;
	  s = this -> skip_space();
	  double res = 0;
	  while(*s >= '0' && *s <= '9')
	  {
	  	res = res * 10 + *s - '0';	
	  	s++;
	  }
	  return res * show_;
}

double CCALC::get_p()
{
	double a = 0;
	s = this -> skip_space();
	if(*s == '(')
	{
		s++;
		a = this -> getexp();
	}
	else if(*s >= '0' && *s <= '9')
	{
		a = this -> get_num();
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
double CCALC::mul_div()
{
	s = this -> skip_space();
	double a = this -> get_p();
	s = this -> skip_space();
	if(*s == '*')
	{
		s++;
		a *= this -> get_p();
		s++;
	}
	else if(*s == '/')
	{
		s++;
		a /= this -> get_p();
		s++;
	}
	else if(*s == '^')
	{
		s++;
		int i = this -> get_p();
		for (int j = 1; j < i; j++)
			a *= i;
		if(i == 0)
			a = 1;
	}
	return a;
}
double CCALC::getexp()
{
	double a = 0; 
	a = this -> mul_div();
	s = this -> skip_space();
	if(*s == '+')
	{
		s++;
		a += this -> mul_div();
	}
	else if(*s == '-')
	{
		s++;
		a -= this -> mul_div();
	}
	if(*s == ')')
		s++;	
	s = this -> skip_space();
	return a;
}
double CCALC::getres()
{
	double a = 0;
	while(*s != '\0')
		a += this -> getexp();
	return a;
}