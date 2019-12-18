#include<iostream>
#include<vector>
#include"vector.h"
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
            // static size_t cnt = 0;
            // cout << cnt << endl;
            // cnt++;

            for (size_t i = 0; i < _size; i++)
                _ar[i] = 0;
        }


        ~My()
        {
            static size_t cnt = 0;
            // cnt++;
            // cout << cnt << endl;
            
            if (_ar != nullptr)
            {
                cout << cnt << endl;
                delete[] _ar;
            }
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
            //cout << "AAA\n";
            _size = obj._size;
            _ar = new double[_size];
            for (size_t i = 0; i < _size; i++)
                _ar[i] = obj._ar[i];
        }

        My( My&& obj)
        {
            //cout << "AAA\n";
            _size = obj._size;
            _ar = obj._ar;
            obj._ar = nullptr;
        }
        
        My ret()
        {
            return *this;
        }
        friend ostream& operator<<(ostream& out, My& obj);
        friend ostream& operator<<(ostream& out, My&& obj);
};
ostream& operator<<(ostream& out, My& obj)
{
    out << "HAHA " << obj._ar[0];
    return out;
}
ostream& operator<<(ostream& out, My&& obj)
{
    out << "HAHA " << obj._ar[0];
    return out;
}

int main()
{
    vector<My> aa;
    My a3(10);
    My a2(a3);
    a2 = a3;
    Vector<My> a(2);
    
    
    a.push_back(a2);
    cout << "HAHA\n";
    cout << a2 << endl;

    a.push_back(a2);
    a.push_back(a2);
    
    a.push_back(a2);
    a.push_back(a2.ret());
    a.push_back(a2);
    a.pop_back();
    a.pop_back();
    a.pop_back();
    a.push_back(a2);
    
    a.push_back(a2);
    a.push_back(a2.ret());
    a.push_back(a2);
    a.clear();
    a.push_back(a2);
    
    a.push_back(a2);
    a.push_back(a2.ret());
    a.push_back(a2);
    cout << a.size() << endl;
    
    a.resize(1020);
    cout << a.capacity() << endl;
    a.push_back(a2);
    a.resize(1);
    cout << a.capacity() << endl;
    
    //a.resize(16);
    auto it = a.begin();
    it++;
    cout << a.capacity() << endl;

    int cnt = 0;
    cout << a.size() << " Size\n";
    for (auto i = a.begin(); i != a.end(); i++)
    {
        cout << *i << endl;
        cout << "CNT " << cnt << endl;
        cnt++;
    }
    
    return 0;
}