#include<iostream>

#ifndef LinearAllocator_H
#define LinearAllocator_H

class LinearAllocator
{
    private:
        char* _memory;
        size_t _maxSize;
        size_t _currSize;


    public:
        LinearAllocator(size_t maxSize);
        ~LinearAllocator();
        char* alloc(size_t size);
        void reset();
        size_t retMaxSize();
};

#endif
