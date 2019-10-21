#include<iostream>
#include<stdlib.h>
#include"allocator.h"
using namespace std;

int main (int argc, char* argv[])
{
    size_t n;
    if (argc <= 1 || argc > 2)
        return 1;
    
    if ((n = atoi(argv[1])) == 0)
        return 1;

    try 
    {
        char* tmp = nullptr;
        LinearAllocator a(n);
        for (int i = 0; i < 15; i++)
        {
            tmp = a.alloc(2);
            if (tmp == nullptr)
                return 3;
        }
          
        for (int i = 0; i < 20; i++)
        {
            tmp = a.alloc(20);
            if (tmp == nullptr)
                return 4;    
        }

        a.reset();

        for (int i = 0; i < 5; i++)
        {
            tmp = a.alloc(200);
            if (tmp == nullptr)
                return 5;    
        }

    }
    catch (const bad_alloc& err)
    {
        return 2;
    }
    

    
    return 0;
}