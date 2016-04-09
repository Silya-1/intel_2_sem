#include "tample.h"

int main()
{
	CVECTOR <bool> a(10);
	a.print();
	int aza;
	aza = a[0];
	a[0] = 1;
	aza = a[0];
	std::cout << aza <<std::endl;
	return 0;
}
