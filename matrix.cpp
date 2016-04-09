
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
        T& operator[](int index) 
        {
            assert(0 <= index && index < size_);
            return data[index];
        };
        CVECTOR();
        ~CVECTOR();
        //void fprint()const;
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
        class CVECTOR<T> &operator[](int index) const
        {
            assert(0 <= index && index < size_);
            return mas[index];
        }
};
template < class T>
Matrix<T>::Matrix()
{
    this -> sizev = size_;
    this -> mas = new CVECTOR<T>[this -> sizev];//(class CVECTOR*)malloc(this -> sizev * sizeof(class CVECTOR));
}
template < class T>
Matrix<T>::~Matrix()
{
    this -> sizev = 0;
    //free(this -> mas);
    delete [] this -> mas;
}
template < class T> CVECTOR<T>::CVECTOR()
{
    this -> size = size_;
    this -> data = new T [this -> size];//(int*)calloc(this -> size, sizeof(int));
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

int main()
{
    CVECTOR <int>a;
    int i;
    //a[0] = 5;
    fprint(a);
    //Matrix as;
    //as[0] = a;
    i = a[0];
    a[0] = 10;
    //a[0] = i + 1;
    std::cout<< a[0] << std::endl;
    return 0;
}
