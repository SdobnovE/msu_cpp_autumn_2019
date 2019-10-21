#include<iostream>
#include<stdlib.h>
#include"allocator.h"
using namespace std;

int main (int argc, char* argv[])
{
    size_t n;
    if (argc == 1)
        return -1;
    
    if ((n = atoi(argv[1])) <= 0)
        return -1;
    

    try 
    {
        LinearAllocator a(n);
        clock_t mallocTime = clock();
        for (auto i = 0; i < n; i++)
        {
            char* a1 = (char*)malloc(sizeof(char));
            free(a1);
        }

        clock_t linAll = clock();
        cout << (linAll - mallocTime) / 1000000. << endl;

        
        for (auto i = 0; i < n; i++)
        {
            char* a1 = a.alloc(1);
            a.reset();
        }
        cout << (clock() - linAll) / 1000000. << endl;
        

    }
    catch (const bad_alloc& err)
    {
        cout << err.what() << endl;
        return -2;
    }
    

    
    return 0;
}