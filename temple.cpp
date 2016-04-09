#include "tample.h"
int main()
{
    CVECTOR <int>a;
    int i;
    fprint(a);
    i = a[0];
    a[0] = 10;
    std::cout<< a[0] << std::endl;
    return 0;
}
