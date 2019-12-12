#include<iostream>

using namespace std;

int main()
{
    size_t n = -1;
    auto ptr = operator new (n);
    if (!ptr)
        cout << "HAHA\n\n";
    return 0;
}