#include<iostream>
#include<map>
#include<vector>
#include<utility>
#include<algorithm>
#include<fstream>

using namespace std;

const size_t NUM = 5;

int read_dict(map<string, uint64_t>& dict, const string& filename)
{
    fstream file;
    file.open(filename, std::fstream::in);
    if (!file.is_open())
        return -1;

    string str;
    size_t error = -1;
    

    while ( !file.eof() )
    {
        if (!(file >> str))
            break;
        

        size_t pos = str.find("http://", 0);
        
        if ( pos != error )
        {
            string NEW = str.substr(pos);
            dict[NEW]++;
        }

    }
    
    return 0;
}


void push_highest (vector<pair<string, uint64_t>>& vec, const pair<string, uint64_t>& elem)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (vec[i].second < elem.second)
        {
            vec[i] = elem;
            break;
        }
    }
}

int main()
{

    
    map<string, uint64_t> dict;
    if (read_dict(dict, "FILE.txt") < 0)
        return -1;

    for (auto i = dict.begin(); i != dict.end(); i++)
    {
        cout << i->first << " " << i->second << endl;
    }
    cout << endl;



    if (dict.size() < 5)
    {
        for (auto i = dict.begin(); i != dict.end(); i++)
        {
            cout << i->first << " " << i->second << endl;
        }
    }
    else
    {
        vector<pair<string, uint64_t>> part_max;
        auto it = dict.begin();
        
        for (size_t i = 0; i < 5; i++)
        {
            part_max.push_back(pair<string, uint64_t>{it->first, it->second});
            it++;
        }

        pair<string, uint64_t> p;
        for (auto i = it; i != dict.end(); i++)
        {
            p = {i->first, i->second};
            push_highest(part_max, p);
        }

        for (const auto& i: part_max)
            cout << i.first << " " <<  i.second << endl;
        
    }
 
    return 0;
}
