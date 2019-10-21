#include<iostream>
#include<stdlib.h>
#include"allocator.h"
using namespace std;

int main (int argc, char* argv[])
{
    size_t n;
    if (argc == 1)
        return -1;
    n = atoi(argv[1]);
    if (n == 0)
        return -1;
    cout << n << endl;
    LinearAllocator a(n);
    if (a.alloc(23) == nullptr)
        cout << "ERROR\n";
    cout << a.retMaxSize() << endl;

    return 0;
}