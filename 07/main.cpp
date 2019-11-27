#include<iostream>
#include<vector>
#include"task.h"
using namespace std;

class My
{
    private:
        double* _ar;
        size_t _size;
    public:
        My(size_t size): _size(size), _ar(new double[size])
        {
            for (size_t i = 0; i < _size; i++)
                _ar[i] = 0;

        }
        
        My():_size(10), _ar(new double[10])
        {
            for (size_t i = 0; i < _size; i++)
                _ar[i] = 0;
        }


        ~My()
        {
            if (_ar != nullptr)
                delete[] _ar;
        }

        My& operator=(const My& obj)
        {
            if (&obj == this)
                return *this;
            delete[] _ar;
            _ar = new double[obj._size];
            for (size_t i = 0; i < _size; i++)
                _ar[i] = obj._ar[i];
            _size = obj._size;
            return *this;

        }

        My(const My& obj)
        {
            _size = obj._size;
            _ar = new double[_size];
            for (size_t i = 0; i < _size; i++)
                _ar[i] = obj._ar[i];
        }
        
        My& ret()
        {
            return *this;
        }
        friend ostream& operator<<(ostream& out, My& obj);
};
ostream& operator<<(ostream& out, My& obj)
{
    out << "HAHA " << obj._ar[0];
    return out;
}

int main()
{
    vector<My> aa;
    My a3(23);
    My a2(a3);
    a2 = a3;
    Vector<My> a(2);
    
    
    a.push_back(a2);
    
    a.push_back(a2);

    a.push_back(a2);
    a.push_back(a2);
    
    a.push_back(a2);
    a.push_back(a2);
    a.push_back(a2);
    
    a.resize(1020);
    cout << a.capacity() << endl;
    a.push_back(a2);
    a.resize(1);
    cout << a.capacity() << endl;
    
    a.resize(16);
    auto it = a.begin();
    it++;
    cout << a.capacity() << endl;
    for (auto i = a.begin(); i != a.end(); i++)
    {
        cout << *i << endl;
    }
    
    return 0;
}