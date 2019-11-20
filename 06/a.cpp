#include<string>
#include<iostream>
using namespace std;

int main()
{
    string str = "abacaba";
    for (auto i = str.begin(); i != str.end(); i++)
        cout << *i << endl;

    return 0;
}