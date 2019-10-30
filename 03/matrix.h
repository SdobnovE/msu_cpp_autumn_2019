#include<iostream>

#ifndef MATRIX_H
#define MATRIX_H
#include"row.h"
class Matrix
{
    
    private:
        size_t _numRows;
        size_t _numColumns;
        Row* _rows;

    public:
        Matrix(size_t rows, size_t columns);
        ~Matrix();
        bool operator==(const Matrix& other) const;
        bool operator!=(const Matrix& other) const;
        Row& operator[](size_t numRow);
        const Row& operator[](size_t numRow) const;
        void operator*=(size_t l);
        void print() const;

};

#endif