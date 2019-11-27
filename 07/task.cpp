#include"task.h"
#include"iostream"
Allocator::Allocator(u_int size = 1024): _max_size(size * 2), _current_size(size)
{
    
}