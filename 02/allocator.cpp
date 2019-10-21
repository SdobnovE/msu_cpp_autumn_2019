#include<iostream>
#include<new>
#include"allocator.h"

LinearAllocator::LinearAllocator(size_t maxSize) : _maxSize(maxSize), _currSize(0)
{
    _memory = (char*)malloc(_maxSize * sizeof(char));
    
    if (_memory == nullptr)    
        throw std::bad_alloc();
        
}

char* LinearAllocator::alloc(size_t size)
{
    
    if (_currSize + size > _maxSize)
        return nullptr;
    else
    {
        _currSize += size;
        return _memory + _currSize;    
    }
    
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