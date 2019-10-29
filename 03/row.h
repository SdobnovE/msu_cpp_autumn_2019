#include<iostream>

#ifndef ROW_H
#define ROW_H
//#include"matrix.h"
class Row
{
    //friend class Matrix;

    private:
        size_t _len;
        size_t* _row;

    public:
        Row(size_t len);
        Row();
        ~Row();
        size_t& operator[](size_t numCol);
        void print();
        void setRow(size_t len);

};
#endif