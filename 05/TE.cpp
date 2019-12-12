#include<iostream>
#include<string>
#include<sstream>
#include <type_traits>

using namespace std;






int main()
{
    stringstream a("HAHAHA HUHUHU HIHIHI");
    string b;
    a >> b;
    cout << b << endl;
    a >> b;
    cout << b << endl;
    a >> b;
    cout << b << endl;
    a >> b;
    cout << b << endl;
    a >> b;
    cout << b << endl;
    
    return 0;
}

