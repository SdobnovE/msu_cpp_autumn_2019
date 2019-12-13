#include<iostream>
#include"thread_pool.h"

using namespace std;

int first(int t)
{
    cout << "ONE " << t << "\n\n";
    return 1;
}

int second(double a, double b)
{

    cout << "TWO" << a + b << "\n\n";
    return 2;
}

int main()
{
    ThreadPool pool(5);
    pool.exec(first, 200);
    pool.exec(first, 20);
    pool.exec(first, 2000);
    pool.exec(second, 2000., 123);
    pool.exec(first, 200);
    pool.exec(first, 20);
    pool.exec(first, 2000);
    pool.exec(second, 2000., 123);
    pool.exec(first, 200);
    pool.exec(first, 20);
    pool.exec(first, 2000);
    pool.exec(second, 2000., 123);
    pool.exec(first, 200);
    pool.exec(first, 20);
    pool.exec(first, 2000);
    pool.exec(second, 2000., 123);
    pool.exec(first, 200);
    pool.exec(first, 20);
    pool.exec(first, 2000);
    pool.exec(second, 2000., 123);
    pool.exec(first, 200);
    pool.exec(first, 20);
    pool.exec(first, 2000);
    pool.exec(second, 2000., 123);
    pool.exec(first, 200);
    pool.exec(first, 20);
    pool.exec(first, 2000);
    pool.exec(second, 2000., 123);
    


    return 0;
}