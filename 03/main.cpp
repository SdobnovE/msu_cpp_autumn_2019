#include<iostream>
#include<stdlib.h>
#include"row.h"
#include"matrix.h"
using namespace std;

int main (int argc, char* argv[])
{
    // Row a(22);
    // a[m12] = 40;
    // int t = a[3];
    // t++;
    // a.print();
    Matrix a(12,12);
    a.print();
    a[2][2] = 1234;
    cout << endl;
    a.print();
    return 0;
}