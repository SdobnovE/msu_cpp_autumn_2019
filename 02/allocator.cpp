#include<iostream>
#include"allocator.h"

LinearAllocator::LinearAllocator(size_t maxSize) : _maxSize(maxSize), _currSize(0)
{
    _memory = (char*)malloc(_maxSize * sizeof(char));
    
    if (_memory == nullptr)
        _maxSize = 0;
        
}

char* LinearAllocator::alloc(size_t size)
{
    if (_currSize + size > _maxSize)
        return nullptr;
    else
        return _memory + _currSize + 2 * size;
    
}

void LinearAllocator::reset ()
{
    _currSize = 0;
} 
size_t LinearAllocator::retMaxSize()
{
    return _maxSize;
}

LinearAllocator::~LinearAllocator()
{
    free(_memory);
}