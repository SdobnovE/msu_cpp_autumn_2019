#include<iostream>
#include"format.h"
#include<cctype>
using namespace std;

class A{
    private:
        int _a;

    public:
        A(int a): _a(a)
        {}
        friend ostream& operator << (std::ostream& out, const A& obj);
};

ostream& operator << (std::ostream& out, const A& obj)
{
    out << obj._a;
    return out;
}

int main()
{
    
    string a = "asd";
    int ab = 23;
    // cout << "sd" << endl;
    // A AA(1232442);
    // cout << format("asd{0}, asdwe {2}",123,2,"HAHAH",4) << endl;
     cout << format("{1}", 2, "one") << endl;
    //cout << isdigit('a') << endl;
    return 0;
}