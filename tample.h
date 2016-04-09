#include <iostream>
#include <assert.h>
#include <stdlib.h>

#define size_ 10
template < class T>
class CVECTOR
{
    private:
        int size;
        T *data;
    public:
        const T& operator[](int index) const
        {
            assert(0 <= index && index < size_);
            return data[index];
        };
        T& operator[]( const int index) 
        {
            assert(0 <= index && index < size_);
            return data[index];
        };
        CVECTOR();
        ~CVECTOR();
};
template < class T>
void fprint(const CVECTOR<T>& a);
template < class T>
class Matrix
{
    private:
        int sizev;
        class CVECTOR<T> *mas;
    public:
        Matrix();
        ~Matrix();
        class CVECTOR<T> &operator[](const int index) const
        {
            assert(0 <= index && index < size_);
            return mas[index];
        }
};
template < class T>
Matrix<T>::Matrix()
{
    this -> sizev = size_;
    this -> mas = new CVECTOR<T>[this -> sizev];
}
template < class T>
Matrix<T>::~Matrix()
{
    this -> sizev = 0;
    delete [] this -> mas;
}
template < class T> CVECTOR<T>::CVECTOR()
{
    this -> size = size_;
    this -> data = new T [this -> size];
}
template < class T>CVECTOR<T>::~CVECTOR()
{
    this -> size = 0;
    delete [] this -> data;
}
template < class T>
void fprint(const CVECTOR<T>& a)
{
    int i;
    for(i = 0; i < size_; i++)
    std::cout<<  a[i] << std::endl;
    std::cout<< "\n" <<std::endl;
}
struct Bitres
{
    long long int *firt_part;
    int place;
    int shift;
    void operator =(int a)
    {
        if (a == 1)
            firt_part[shift] = ((firt_part[shift]) | (1 << place));
        else
            firt_part[shift] =  ((firt_part[shift]) & (~(1 << place)));
    }
    operator int ()
    {
        return ((firt_part[shift] >> place) & 1);
    }
};
typedef struct Bitres bitres;
template <> 
class CVECTOR <bool>
{
    public:
    long long int *arg;
    int size;
    CVECTOR(int SIZE);
    ~CVECTOR();
    void print();
    bitres operator[](const int index);
};
CVECTOR<bool>::CVECTOR(int SIZE)
{
    arg = new long long [SIZE];
    for(int i = 0; i < SIZE; i++)
        arg[i] = 0;
    size = SIZE;
}
CVECTOR<bool>::~CVECTOR()
{
    delete[] arg;
}
void CVECTOR<bool>::print()
{
    for(int i = 0; i < size; i++)
        std::cout<< arg[i]<< " ";
    std::cout<<std::endl;

}
 bitres CVECTOR<bool>::operator[](int index)
{
    bitres res;
    res.firt_part =  arg;
    res.shift = index / 64;
    res.place = index % 64;
    return res;
}
