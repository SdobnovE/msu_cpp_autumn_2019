#include<iostream>
#include"row.h"
#include"matrix.h"

Matrix::Matrix(size_t rows, size_t columns): _numRows(rows), _numColumns(columns)
{
    _rows = new Row[_numRows];
    
    if (_rows == nullptr)
        throw std::bad_alloc();

    for (auto i = 0; i < _numRows; i++)
        _rows[i].setRow(_numColumns);
    
    _rows[0].print();

}

Row& Matrix::operator[](size_t numRow)
{
    
    if (numRow >=0 && numRow <= _numRows)
        return _rows[numRow];
    else
        throw std::bad_alloc();
}

Matrix::~Matrix()
{
    
    if (_rows != nullptr)
        delete[] _rows;
}

bool Matrix::operator==(const Matrix& other) const
{
    if (this->_numColumns != other._numColumns
        && this->_numRows != other._numRows)
        return false;
    
    for (auto i = 0; i < _numRows; i++)
        for (auto j = 0; j < _numColumns; j++)
            if (_rows[i][j] != other._rows[i][j])
                return false;

    return true;
}

bool Matrix::operator!=(const Matrix& other) const
{
    return !(*this == other);
}

void Matrix::operator*=(size_t l)
{
    for (auto i = 0; i < _numRows; i++)
        for (auto j = 0; j < _numColumns; j++)
            _rows[i][j] *= l;
    
}

void Matrix::print()
{
    for (auto i = 0; i < _numRows; i++)
    {
        for (auto j = 0; j < _numColumns; j++)
        {
            std::cout << _rows[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
