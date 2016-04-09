#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define size_mas 8
#define max_stack 4
template < class T>
class CSTACK
{
    private:
    T *mas;
    int size;
    int max_size;
    static int number;
    public :
    CSTACK();
    ~CSTACK();
    int push_back(T val);
    void fprint();
    T pop_back();
};
template < class T> int CSTACK<T> :: number = 0;
template < class T> CSTACK<T>::CSTACK()
{
    if (this -> number < max_stack)
    {
        size = 0;
        this -> max_size = size_mas;
        mas = (T*)calloc(size_mas, sizeof(T));
        this -> number ++;
    }
    else
    {
        printf("PAY FOR NEW STACK");
        exit(228);
    }
}
template < class T> CSTACK<T>::~CSTACK()
{
    size = 0;
    int i;
    free (mas);
    this -> number = 0;
    this -> max_size = 0;
}
template < class T>void CSTACK<T>::fprint()
{
    std::cout< this -> size <<std::endl;
}
template < class T>int CSTACK<T>::push_back(T val)
{
    if (this -> size < this -> max_size)
    this -> mas[this -> size++] = val;
    else
    {
        this -> max_size *= 5;
        mas = (T*)realloc(mas, this -> max_size);
        this -> mas[this -> size++] = val;
    }
}
template < class T> T CSTACK<T>::pop_back()
{
    if (size > 0)
    return this -> mas[--this -> size];
    else exit(228);
}
int main()
{
 //   CSTACK *b1 = new CSTACK;
    CSTACK <char>f;
    f.push_back('a');
//    b1 -> push_back(10);
//    b1 -> fprint();
    //printf("%d",f.pop_back());
    std::cout<<f.pop_back()<<std::endl;
    return 0;
}

