#include<iostream>

#ifndef ROW_H
#define ROW_H

class Row
{

    private:
        size_t _len;
        size_t* _row;

    public:
        Row(size_t len);
        Row();
        ~Row();
        size_t& operator[](size_t numCol);
        size_t operator[](size_t numCol) const;
        void print() const;
        void setRow(size_t len);

};
#endif