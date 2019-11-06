#include<iostream>
#include"row.h"
//#include"matrix.h"

Row::Row(size_t len): _len(len)
{
    _row = new uint64_t[_len];
    
    if (_row == nullptr)
        throw std::bad_alloc();
    
    for (size_t i = 0; i < _len; i++)
        _row[i] = 0;
}

Row::~Row()
{
    if (_row != nullptr)
        delete[] _row;
}

uint64_t Row::operator[](size_t numCol) const
{
    if (numCol < _len)
        return _row[numCol];
    else
        throw std::out_of_range("");
}

uint64_t& Row::operator[](size_t numCol)
{
    if (numCol < _len)
        return _row[numCol];
    else
        throw std::out_of_range("");
}

void Row::print() const
{
    for (size_t i = 0; i < _len; i++)
        std::cout << _row[i] << std::endl;
}

void Row::setRow(size_t len)
{
    _len = len;
    if (_row != nullptr)
        delete[] _row;
    
    _row = new size_t[len];
    
    if (_row == nullptr)
        throw std::bad_alloc();

    for (size_t i = 0; i < _len; i++)
        _row[i] = 0;
}

Row::Row(): _len(0), _row(nullptr){}
