#include<iostream>

#ifndef ROW_H
#define ROW_H

class Row
{

    private:
        size_t _len;
        uint64_t* _row;

    public:
        Row(size_t len);
        Row();
        ~Row();
        uint64_t& operator[](size_t numCol);
        uint64_t operator[](size_t numCol) const;
        void print() const;

};
#endif
