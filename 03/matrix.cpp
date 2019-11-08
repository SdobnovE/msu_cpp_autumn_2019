#include<iostream>
#include"row.h"
#include"matrix.h"
using std::cout;
using std::endl;

Matrix::Matrix(size_t rows, size_t columns): _numRows(rows), _numColumns(columns)
{
    
    if (_numRows == 0)
    {
        _rows = nullptr;
        return;
    }

    auto temp = static_cast<Row*>(operator new(sizeof(Row) * _numRows));
    
    if (temp == nullptr)
        throw std::bad_alloc();
    

    _rows = new (temp) Row(_numColumns);
    
    for (size_t i = 1; i < _numRows; i++)
        new (temp + i) Row(_numColumns);
    
}

const Row& Matrix::operator[](size_t numRow) const
{
    if (numRow < _numRows)
        return _rows[numRow];
    else
        throw std::out_of_range("");
}

Row& Matrix::operator[](size_t numRow)
{
    
    if (numRow < _numRows)
        return _rows[numRow];
    else
        throw std::out_of_range("");
}

Matrix::~Matrix()
{
    for (size_t i = 0; i < _numRows; i++)
        _rows[i].~Row();
        
    if (_rows != nullptr)
        operator delete (_rows);
}

bool Matrix::operator==(const Matrix& other) const
{
    if (this->_numColumns != other._numColumns
        && this->_numRows != other._numRows)
        return false;
    
    for (size_t i = 0; i < _numRows; i++)
        for (size_t j = 0; j < _numColumns; j++)
            if (_rows[i][j] != other._rows[i][j])
                return false;

    return true;
}

bool Matrix::operator!=(const Matrix& other) const
{
    return !(*this == other);
}

Matrix& Matrix::operator*=(uint64_t l)
{
    for (size_t i = 0; i < _numRows; i++)
        for (size_t j = 0; j < _numColumns; j++)
            _rows[i][j] *= l;
    return *this;
    
}

void Matrix::print() const
{
    for (size_t i = 0; i < _numRows; i++)
    {
        for (size_t j = 0; j < _numColumns; j++)
        {
            std::cout << _rows[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
