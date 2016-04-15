#include <iostream>
#include <cstdlib>
#include <cmath>
#include "file.h"
#include <assert.h>
char *itoa(int number, char *destination, int base) {
  int count = 0;
  do {
    int digit = number % base;
    destination[count++] = (digit > 9) ? digit - 10 +'A' : digit + '0';
  } while ((number /= base) != 0);
  destination[count] = '\0';
  int i;
  for (i = 0; i < count / 2; ++i) {
    char symbol = destination[i];
    destination[i] = destination[count - i - 1];
    destination[count - i - 1] = symbol;
  }
  return destination;
}
int ato(char s[])
{
    int i, n;
    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}
#define size_t 20000
#define LN(exp) root -> make_ln(exp)
#define R (*(root -> right))
#define L (*(root -> left))
#define d(exp)  *dif_start(&exp)
#define f_x_  root
#define COS(exp) exp -> do_cos(*exp) 
#define CH(exp) exp -> do_ch(*exp) 
#define SH(exp) exp -> do_sh(*exp) 
#define _SIN(exp) exp -> do_sin(*exp) 
#define d_arctan_(exp) exp -> do_arctan(*exp)
#define d_arcctg_(exp) exp -> do_arcctg(*exp)
#define d_arccos_(exp) exp -> do_arccos(*exp)
#define d_arcsin_(exp) exp -> do_arcsin(*exp)
#define EXP(exp) exp -> do_exp(*exp)
#define double_sqrt(exp) exp -> do_sqrt(*exp)
#define sqr_cos(exp) exp -> get_sqr_cos(*exp)
#define sqr_sin(exp) exp -> get_sqr_sin(*exp)
#define sqr_ch(exp) exp -> get_sqr_ch(*exp)
#define sqr_sh(exp) exp -> get_sqr_sh(*exp)
#define signum(exp) exp -> get_signum(*exp)


class DIF
{
private:
	 char *s, *k;
	struct Tree
	{
		char *val;
		struct Tree *left;
		struct Tree *right;
		Tree* operator + (Tree val);
		Tree* operator - (Tree val);
		Tree& operator *(Tree val);
		Tree* operator /(Tree val);
		Tree&  do_cos(Tree val);
		Tree&  do_sin(Tree val);
		Tree&  do_sh(Tree val);
		Tree&  do_ch(Tree val);
		Tree&  do_arctan(Tree val);
		Tree&  do_arcctg(Tree val);
		Tree&  do_arccos(Tree val);
		Tree&  do_arcsin(Tree val);
		Tree&  do_exp(Tree val);
		Tree&  make_ln(Tree val);
		Tree&  do_sqrt(Tree val);
		Tree&  get_sqr_cos(Tree val);
		Tree&  get_sqr_sin(Tree val);
		Tree&  get_sqr_ch(Tree val);
		Tree&  get_sqr_sh(Tree val);
		Tree&  get_signum(Tree val);
		Tree* copy_tree(Tree *node);
        Tree(char* elem)
        {
            this -> val = new char[size];
            strcpy(val, elem);
            left = right = NULL;
        }
        Tree()
        {
        	val = NULL;
        	left = right = NULL;	
        }
        ~Tree()
        {
        	if(val == NULL)
        	delete[] val;
        	left = right = NULL;
        }
	};
    Tree *tree;
    void delete_tree(Tree *root);
    Tree* dif_start(struct Tree *root);
public:
	DIF(char *k, int size_of_array);
	~DIF();
	char* skip_space();
	char* get_num();
	Tree* get_p();
	Tree* getexp();
	void getres();
	Tree* mul_div();
	void dif();
	void tree_print(struct Tree *root, CFILE &a);
	Tree* get_root()
    {
        return tree;
    };
};
void DIF::dif()
{
	Tree *res;
	res = dif_start(tree);
	delete_tree(tree);
	tree = res;
}
DIF::Tree* DIF::Tree::operator +(Tree val)
{
	Tree *res = new Tree("+");
	
	std::cout<<res -> val<<std::endl;
	res -> right = this;
	std::cout<<res -> val<<std::endl;
	res -> left =  copy_tree(&val);
	return res;
}
DIF::Tree& DIF::Tree::operator *(Tree val)
{
	Tree *res = new Tree("*");
	std::cout<<res -> val<<std::endl;
	res -> right = this;
	std::cout<<res -> val<<std::endl;
	res -> left =  copy_tree(&val);
	return *res;
}
DIF::Tree* DIF::Tree::operator /(Tree val)
{
	Tree *res = new Tree("/");
	std::cout<<res -> val<<std::endl;
	res -> left = this;
	std::cout<<res -> val<<std::endl;
	res -> right =  copy_tree(&val);
	return res;
}
DIF::Tree* DIF::Tree::operator -(Tree val)
{
	Tree *res = new Tree("-");
	
	std::cout<<res -> val<<std::endl;
	res -> right = this;
	std::cout<<res -> val<<std::endl;
	res -> left =  copy_tree(&val);
	return res;
}
DIF::Tree&  DIF::Tree::do_cos(Tree val)
{
	Tree *res = new Tree("cos");
	res -> right = copy_tree((val.right));
	return *res;
}
DIF::Tree&  DIF::Tree::do_sin(Tree val)
{
	Tree *res = new Tree("*");
	res -> left = new Tree("-1");
	res -> right = new Tree("sin");
	res ->right -> right = copy_tree((val.right));
	return *res;
}
DIF::Tree&  DIF::Tree::do_arctan(Tree val)
{
	Tree *res = new Tree("+");
	res -> left = new Tree("1");
	res -> right = new Tree("^");
	res ->right -> right = new Tree ("2");
	res ->right -> left = copy_tree((val.right));
	return *res;
}
DIF::Tree&  DIF::Tree::do_arcctg(Tree val)
{
	Tree *answ = new Tree("*");
	answ -> left = new Tree("-1");
	Tree *res = new Tree("+");
	res -> left = new Tree("1");
	res -> right = new Tree("^");
	res ->right -> right = new Tree ("2");
	res ->right -> left = copy_tree((val.right));
	answ -> right = res;
	return *answ;
}
DIF::Tree&  DIF::Tree::do_arccos(Tree val)
{
	Tree *answ = new Tree("sqrt");
	answ -> right = new Tree("-");
	answ -> right -> left = new Tree("1");
	Tree *res = new Tree("^");
	res -> left = copy_tree((val.right));
	res -> right = new Tree("2");
	answ -> right -> right = res;
	return *answ;
}
DIF::Tree&  DIF::Tree::do_arcsin(Tree val)
{
	Tree *answ = new Tree("sqrt");
	answ -> right = new Tree("+");
	answ -> right -> left = new Tree("1");
	Tree *res = new Tree("^");
	res -> left = copy_tree((val.right));
	res -> right = new Tree("2");
	answ -> right -> right = res;
	return *answ;
}
DIF::Tree& DIF::Tree::do_exp(Tree val)
{
	Tree *res = new Tree("^");
	res -> left = new Tree("e");
	res -> right = new Tree("*");
	res -> right -> left = new Tree("ln");
	res -> right -> left ->right = copy_tree(val.left);
	res -> right -> right = copy_tree(val.right);
	return *res;
}
DIF::Tree& DIF::Tree::make_ln(Tree val)
{
	Tree *res = new Tree("ln");
	res -> right = copy_tree(&val);
	return *res;
}
DIF::Tree& DIF::Tree::do_sqrt(Tree val)
{
	Tree *res = new Tree("*");
	res -> left = new Tree("2");
	res -> right = copy_tree(&val);
	return *res;
}
DIF::Tree& DIF::Tree::get_sqr_sin(Tree val)
{
	Tree *res = new Tree("*");
	res -> left = new Tree("-1");
	res -> right = new Tree("^");
	res -> right -> right = new Tree("2");
	res -> right -> left = new Tree("sin");
	res -> right -> left -> right = copy_tree(val.right);
	return *res;
}
DIF::Tree& DIF::Tree::get_sqr_cos(Tree val)
{
	Tree *res = new Tree("^");
	res -> right = new Tree("2");
	res -> left = new Tree("cos");
	res -> left -> right = copy_tree(val.right);
	return *res;
}
DIF::Tree& DIF::Tree::get_sqr_ch(Tree val)
{
	Tree *res = new Tree("^");
	res -> right = new Tree("2");
	res -> left = new Tree("ch");
	res -> left -> right = copy_tree(val.right);
	return *res;
}
DIF::Tree& DIF::Tree::get_sqr_sh(Tree val)
{
	Tree *res = new Tree("*");
	res -> left = new Tree("-1");
	res -> right = new Tree("^");
	res -> right -> right = new Tree("2");
	res -> right -> left = new Tree("sh");
	res -> right -> left -> right = copy_tree(val.right);
	return *res;
}
DIF::Tree&  DIF::Tree::do_ch(Tree val)
{
	Tree *res = new Tree("ch");
	res -> right = copy_tree((val.right));
	return *res;
}
DIF::Tree&  DIF::Tree::do_sh(Tree val)
{
	Tree *res = new Tree("sh");
	res -> right = copy_tree((val.right));
	return *res;
}
DIF::Tree&  DIF::Tree::get_signum(Tree val)
{
	Tree *res = new Tree("signum");
	res -> right = copy_tree((val.right));
	return *res;
}
DIF::Tree* DIF::dif_start(struct Tree* root)
{
	if(root == NULL)
		return NULL;
	if(strcmp(root -> val, "+") == 0)
	{
		struct Tree *res =  d(R) + d(L);
		return res;
	}
	else if(strcmp(root -> val, "tan") == 0)
	{
		struct Tree *res = d(R) /(sqr_cos(root));
		return res;
	}
	else if(strcmp(root -> val, "ch") == 0)
	{
		struct Tree *res = &(SH(f_x_) * d(R));
		return res;
	}
	else if(strcmp(root -> val, "sh") == 0)
	{
		struct Tree *res =&(CH(f_x_) * d(R));
		return res;
	}
	else if(strcmp(root -> val, "ctg") == 0)
	{
		struct Tree *res = d(R) /(sqr_sin(root));
		return res;
	}
	else if (root -> val[0] >= '0' && root -> val[0] <= '9' || 
				root -> val[1] >= '0' && root -> val[1] <= '9' ||
				root -> val[0] == 'e'||
				(strncmp(root -> val, "pi", 2) == 0))
	{
		Tree *res = new Tree ("0");
		return res;
	}
	else if(strcmp(root -> val, "ln") == 0)
	{
		struct Tree *res =  d(R) / R;
		return res;
	}
	else if(strcmp(root -> val, "th") == 0)
	{
		struct Tree *res = d(R) /(sqr_ch(root));
		return res;
	}
	else if(strcmp(root -> val, "cth") == 0)
	{
		struct Tree *res = d(R) /(sqr_sh(root));
		return res;
	}
	else if (strcmp(root -> val, "-") == 0)
	{
		struct Tree *res =  d(R) - d(L);
		return res;
	}
	else if (strcmp(root -> val, "arctan") == 0)
	{
		struct Tree *res =  d(R) / (d_arctan_(f_x_));
		return res;
	}
	else if (strcmp(root -> val, "arcctg") == 0)
	{
		struct Tree *res =  d(R) / (d_arcctg_(f_x_));
		return res;
	}
	else if (strcmp(root -> val, "arcsin") == 0)
	{
		struct Tree *res =  d(R) / (d_arcsin_(f_x_));
		return res;
	}
	else if (strcmp(root -> val, "arccos") == 0)
	{
		struct Tree *res =  d(R) / (d_arccos_(f_x_));
		return res;
	}
	else if(strcmp(root -> val, "*") == 0)
	{
		struct Tree *res =  d(L) * R + d(R) * L;// dv * u
		return res;
	}
	else if(strcmp(root -> val, "abs") == 0)
	{
		struct Tree *res = &(d(R) * signum(f_x_));// dv * u
		return res;
	}
	else if(strcmp(root -> val, "/") == 0)
	{
		struct Tree *res =  *(d(L) * R + d(R) * L) / (R * R);
		return res;
	}
	else if(strcmp(root -> val, "^") == 0)
	{
		struct Tree *res =  &( EXP(root) * *( d(R) * LN(L) + R * *(d(L) / L)));
		return res;
	}
	else if(strcmp(root -> val, "sin") == 0)
	{
		struct Tree* res = &(COS(f_x_) * d(R));
		return res;
	}
	else if(strcmp(root -> val, "sqrt") == 0)
	{
		struct Tree* res = d(R) / (double_sqrt(root)) ;
		return res;
	}
	else if(strcmp(root -> val, "cos") == 0)
	{
		struct Tree *res = 	&(_SIN(f_x_)* d(R));
		return res;
	}
	else if (strcmp(root -> val, "x")== 0)
	{

		Tree *res = new Tree ("1");
		return res;
	}
		delete_tree(root);

};
void DIF::delete_tree(Tree *node)
{
    if(node != NULL)
    {
        delete_tree(node -> left);
        delete_tree(node -> right);
        delete[] node -> val;
        delete node;
    }
}
void DIF::tree_print(struct Tree *root, CFILE &a)
{
    if (tree)
    {
    	if ((root -> val[0] > '9' || root -> val[0] < '0') 	
    			&& root -> val[0] != 'x')
    	a.file_out("(");	
        if(root -> left)
        	tree_print(root -> left, a);
        std::cout<< root -> val<< std::endl;
        a.file_out(root -> val);
        if(root -> right)
            tree_print(root -> right, a);
        if ((root -> val[0] > '9' || root -> val[0] < '0') 	
        		&& root -> val[0] != 'x')
    	a.file_out(")");
    }
}

DIF::DIF(char *srs, int size_of_array)
{
	s = new char[size_of_array];
	strcpy(s, srs);
	k = s;
	tree = NULL;
};
DIF::Tree* DIF::Tree::copy_tree(Tree* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    char *mas = new char[20];
    strcpy(mas, node -> val);
    Tree *new_tree =  new Tree(mas);
    delete[] mas;
    new_tree -> left = copy_tree(node -> left);
    new_tree -> right = copy_tree(node -> right);
    return new_tree;
}
DIF::~DIF()
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
	DIF calc(strt, size_t);
	calc.getres();
	//calc.tree_print(calc.get_root(), out);
	calc.dif();
	//calc.optimize();
	std::cout<<"RRRdddddddddRRRRR"<<std::endl;
	calc.tree_print(calc.get_root(), out);
	fclose(file);
	delete[] strt;
	return 0;
}


char* DIF::skip_space()
{
	while(*s == ' ' || *s == '\n')
		s++;
	return s;
}
char* DIF::get_num()
{
	int i = 0;
	char *res= new char[10];
  	s = this -> skip_space();
  	if(*s == '-')
	{
  		i = 1;
  		res[0] = '-';
  		s++;
  		std::cout<<res[0]<<std::endl;
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
DIF::Tree* DIF::get_p()
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
	if(*s >= '0' && *s <= '9' ||	
	 *(s + 1) >= '0' && *(s + 1) <= '9')
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
	else if(*s == 'e')
	{
		a = new Tree;
		a -> left = a -> right = NULL;
		a -> val = new char[2];
		strcpy(a -> val, "e");
		s++;
	}
	else if(*s == 'p' && *(s +1) =='i')
	{
		a = new Tree;
		a -> left = a -> right = NULL;
		a -> val = new char[3];
		strcpy(a -> val, "pi");
		s += 2;
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
		if (strncmp(s, "ln", 2) == 0)
		{
			s += 3;
			struct Tree * log = new struct Tree;
			log -> left = log -> right = NULL;
			log -> val = new char[strlen("ln") + 1];
			strcpy(log -> val, "ln");
			log -> left = a;
			log -> right = this -> getexp();
			a = log;
			return a;
		}
		if (strncmp(s, "cos", 3) == 0)
		{
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
		if (strncmp(s, "arctan", 6) == 0)
		{
			s += 7;
			struct Tree * atan = new struct Tree;
			atan -> left = atan -> right = NULL;
			atan -> val = new char[strlen("arctan")+ 1];
			strcpy(atan -> val, "arctan");
			atan -> left = a;
			atan -> right = this -> getexp();
			a = atan;
			return a;
		}
		if (strncmp(s, "arcctg", 6) == 0)
		{
			s += 7;
			struct Tree * arcctg = new struct Tree;
			arcctg -> left = arcctg -> right = NULL;
			arcctg -> val = new char[strlen("arcctg")+ 1];
			strcpy(arcctg -> val, "arcctg");
			arcctg -> left = a;
			arcctg -> right = this -> getexp();
			a = arcctg;
			return a;
		}
		if(strncmp(s, "tan", 3) == 0)
		{
			s += 4;
			struct Tree * tan = new struct Tree;
			tan -> left = tan -> right = NULL;
			tan -> val = new char[strlen("tan")+ 1];
			strcpy(tan -> val, "tan");
			tan -> left = a;
			tan -> right = this -> getexp();
			a = tan;
			return a;
		}
		if(strncmp(s, "ctg", 3) == 0)
		{
			s += 4;
			struct Tree * ctg = new struct Tree;
			ctg -> left = ctg -> right = NULL;
			ctg -> val = new char[strlen("ctg")+ 1];
			strcpy(ctg -> val, "ctg");
			ctg -> left = a;
			ctg -> right = this -> getexp();
			a = ctg;
			return a;
		}
		if(strncmp(s, "arcsin", 6) == 0)
		{
			s += 7;
			struct Tree * arcsin = new struct Tree;
			arcsin -> left = arcsin -> right = NULL;
			arcsin -> val = new char[strlen("arcsin")+ 1];
			strcpy(arcsin -> val, "arcsin");
			arcsin -> left = a;
			arcsin -> right = this -> getexp();
			a = arcsin;
			return a;
		}
		if(strncmp(s, "arccos", 6) == 0)
		{
			s += 7;
			struct Tree * arccos = new struct Tree;
			arccos -> left = arccos -> right = NULL;
			arccos -> val = new char[strlen("arccos")+ 1];
			strcpy(arccos -> val, "arccos");
			arccos -> left = a;
			arccos -> right = this -> getexp();
			a = arccos;
			return a;
		}
		if(strncmp(s, "ch", 2) == 0)
		{
			s += 3;
			struct Tree * ch = new struct Tree;
			ch -> left = ch -> right = NULL;
			ch -> val = new char[strlen("ch")+ 1];
			strcpy(ch -> val, "ch");
			ch -> left = a;
			ch -> right = this -> getexp();
			a = ch;
			return a;
		}
		if(strncmp(s, "sh", 2) == 0)
		{
			s += 3;
			struct Tree * sh = new struct Tree;
			sh -> left = sh -> right = NULL;
			sh -> val = new char[strlen("sh")+ 1];
			strcpy(sh -> val, "sh");
			sh -> left = a;
			sh -> right = this -> getexp();
			a = sh;
			return a;
		}
		if(strncmp(s, "th", 2) == 0)
		{
			s += 3;
			struct Tree * th = new struct Tree;
			th -> left = th -> right = NULL;
			th -> val = new char[strlen("th")+ 1];
			strcpy(th -> val, "th");
			th -> left = a;
			th -> right = this -> getexp();
			a = th;
			return a;
		}
		if(strncmp(s, "cth", 3) == 0)
		{
			s += 4;
			struct Tree * cth = new struct Tree;
			cth -> left = cth -> right = NULL;
			cth -> val = new char[strlen("cth")+ 1];
			strcpy(cth -> val, "cth");
			cth -> left = a;
			cth -> right = this -> getexp();
			a = cth;
			return a;
		}
		if(strncmp(s, "abs", 3) == 0)
		{
			s += 4;
			struct Tree * abs = new struct Tree;
			abs -> left = abs -> right = NULL;
			abs -> val = new char[strlen("abs")+ 1];
			strcpy(abs -> val, "abs");
			abs -> left = a;
			abs -> right = this -> getexp();
			a = abs;
			return a;
		}
		if (strncmp(s, "sqrt", 4) == 0)
		{
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
DIF::Tree*  DIF::mul_div()
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
		return a;
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
		//s++;
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
	}
	return a;
}
DIF::Tree* DIF::getexp()
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
	 if(*s == ')')
	{
		s++;	
		return a;
	}
	s = skip_space();
	return a;
}
void DIF::getres()
{
	tree = this -> getexp();
	while(*s != '\0')
	{
		if (*s != '\0')
		{
			struct Tree* a = NULL; 
			a = this -> getexp();
			a -> left = tree;
			tree = a;
		}
	}
	assert(tree);
}