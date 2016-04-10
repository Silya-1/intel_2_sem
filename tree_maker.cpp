#include <iostream>
#include <stdio.h>
#include  <string.h>
#include <stdlib.h>
#include <cmath>
#include "file.h"
#include <assert.h>
#define size_t 20000
class CCALC
{
private:
	 char *s, *k;
	struct Tree
	{
		char *val;
		struct Tree *left;
		struct Tree *right;
	};
    struct Tree *tree;
    void delete_tree(Tree *root);
public:
	CCALC(char *k, int size_of_array);
	~CCALC();
	char* skip_space();
	char* get_num();
	Tree* get_p();
	Tree* getexp();
	void getres();
	Tree* mul_div();
	void tree_print(struct Tree *root, CFILE &a);
	Tree* get_root()
    {
        return tree;
    };
};
void CCALC::delete_tree(Tree *node)
{
    if(node != NULL)
    {
        delete_tree(node -> left);
        delete_tree(node -> right);
        delete[] node -> val;
        delete node;
    }
}
void CCALC::tree_print(struct Tree *root, CFILE &a)
{
    if (tree)
    {
        if(root -> left)
        	tree_print(root -> left, a);
        std::cout<< root -> val<< std::endl;
        a.file_out(root -> val);
        if(root -> right)
            tree_print(root -> right, a);
    }
}

CCALC::CCALC(char *srs, int size_of_array)
{
	s = new char[size_of_array];
	strcpy(s, srs);
	k = s;
	tree = NULL;
};
CCALC::~CCALC()
{
	delete[] k;
	k = s = NULL;
	delete_tree(tree);
	tree = NULL;
}
int main()
{
	FILE*  file = fopen("calc.txt", "r");
	CFILE  out("res", "w");
	char *strt = new char[size_t]; 
	fgets(strt,size_t,file);
	CCALC calc(strt, size_t);
	calc.getres();
	calc.tree_print(calc.get_root(), out);
	fclose(file);
	delete[] strt;
	return 0;
}
char* CCALC::skip_space()
{
	while(*s == ' ' || *s == '\n')
		s++;
	return s;
}
char* CCALC::get_num()
{
	int i = 0;
	char *res= new char[10];
  	s = this -> skip_space();
  	if(*s == '-')
	{
  		i = 1;
  		res[0] = '-';
  		s++;
  	}
  	else 
  		i = 0;
	  s = this -> skip_space();
	  //double res = 0;
	  while(*s >= '0' && *s <= '9')
	  {
	  	res[i] = *s;
	  	i++;
	  	//std::cout<<*s<<" zv"<<std::endl;	
	  	s++;
	  }
	  res[i] = '\0';
	return res;
}
CCALC::Tree* CCALC::get_p()
{
	Tree* a  = NULL;
	s = this -> skip_space();
	//std::cout<<*s<< *(s+1)<<*(s+2)<<std::endl;
	if(*s == '(')
	{
		s++;
		a = this -> getexp();
		return a;
	}
	if(*s >= '0' && *s <= '9')
	{
		a = new Tree;
		a -> left = a -> right = NULL;
		a -> val = new char[12];
		char *res = this -> get_num();
		strcpy(a -> val, res);
		delete[]res;
		s = skip_space();
		//std::cout<<a<<std::endl;
	}
	else if(*s == 'x')
	{
		a = new Tree;
		a -> left = a -> right = NULL;
		a -> val = new char[2];
		strcpy(a -> val, "x");
		s++;
	}
	else 
	{	
		if (strncmp(s, "sin", 3) == 0)
		{
			s += 4;
			struct Tree * sin = new struct Tree;
			sin -> left = sin -> right = NULL;
			sin -> val = new char[strlen("sin") + 1];
			strcpy(sin -> val, "sin");
			sin -> left = a;
			sin -> right = this -> getexp();
			a = sin;
			return a;
		}
		if (strncmp(s, "cos", 3) == 0)
		{
			//a = new Tree;
			s += 4;
			struct Tree * cos = new struct Tree;
			cos -> left = cos -> right = NULL;
			cos -> val = new char[strlen("cos")+ 1];
			strcpy(cos -> val, "cos");
			cos -> left = a;
			cos -> right = this -> getexp();
			a = cos;
			return a;
		}
		if (strncmp(s, "sqrt", 4) == 0)
		{
			//a = new Tree;
			s += 5;
			struct Tree * sqrt = new struct Tree;
			sqrt -> left = sqrt -> right = NULL;
			sqrt -> val = new char[strlen("sqrt") + 1];
			strcpy(sqrt -> val, "sqrt");
			sqrt -> left = a;
			sqrt -> right = this -> getexp();
			a = sqrt;
			return a;
		}
	}
	return a;
}
CCALC::Tree*  CCALC::mul_div()
{
	s = this -> skip_space();
	struct Tree* a = this -> get_p();
	s = this -> skip_space();
	//s = this -> skip_space();
	if(*s == '*')
	{
		s++;
		struct Tree * mul = new struct Tree;
		mul -> left = mul -> right = NULL;
		mul -> val = new char[strlen("*") + 1];
		strcpy(mul -> val, "*");
		mul -> left = a;
		mul -> right = this -> get_p();
		a = mul;
		s++;
	}
	else if(*s == '/')
	{
		s++;
		struct Tree * div = new struct Tree;
		div -> left = div -> right = NULL;
		div -> val = new char[strlen("/") + 1];
		strcpy(div -> val, "/");
		div -> left = a;
		div -> right = this -> get_p();
		a = div;
		s++;
	}
	else if(*s == '^')
	{
		s++;
		struct Tree * degree = new struct Tree;
		degree -> left = degree -> right = NULL;
		degree -> val = new char[strlen("^") + 1];
		strcpy(degree -> val, "^");
		degree -> left = a;
		degree -> right = this -> get_p();
		a = degree;
		s++;
	}
	return a;
}
CCALC::Tree* CCALC::getexp()
{
	struct Tree* a = NULL; 
	a = this -> mul_div();
	s = this -> skip_space();
	if(*s == '+')
	{
		s++;
		struct Tree * plus = new struct Tree;
		plus -> left = plus -> right = NULL;
		plus -> val = new char[strlen("+") + 1];
		strcpy(plus -> val, "+");
		plus -> left = a;
		plus -> right = this -> mul_div();
		a = plus;
	}
	else if(*s == '-')
	{
		s++;
		struct Tree * minus = new struct Tree;
		minus -> left = minus -> right = NULL;
		minus -> val = new char[strlen("-") + 1];
		strcpy(minus -> val, "-");
		minus -> left = a;
		minus -> right = this -> mul_div();
		a = minus;
	}
	else if(*s == ')')
	{
		s++;	
		return a;
	}
	return a;
	s = skip_space();
}
void CCALC::getres()
{
	tree = this -> getexp();
	assert(tree);
}