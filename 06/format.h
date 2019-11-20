#include<iostream>
#include<string>
#include<stdio.h>
#include<sstream>
#include<utility>
#include<vector>
#include<cctype>

using std::cout;
using std::endl;


void parse(std::vector<std::string>& vec)
{
    
} 

template<class T, class... Args>
void parse(std::vector<std::string>& vec, T&& first, Args&&... others)
{
    std::stringstream str;
    str << first;
    vec.push_back(str.str());
    parse(vec, std::forward<Args>(others)...);
}




template<class... Args>
std::string format(const std::string& str, Args&&... args)
{
    std::vector<std::string> string_args; 
    parse(string_args, std::forward<Args>(args)...);
    
    size_t i = 0;
    std::stringstream result;
    for (auto i = str.begin(); i != str.end(); ++i)
    {
        
        if (*i == '}')
            throw std::runtime_error("}");
        
        if (*i == '{')
        {
            i++;
            std::string number = "";

            while (i != str.end() && isdigit (*i))// \0 не цифра, так что ок
            {
                
                number += *i;
                i++;
            }
            
            if (i == str.end() || *i != '}')
                throw std::runtime_error("no } symbol");
            
            size_t index = std::stoi(number);

            if (string_args.size() > index)
                result << string_args[index];
            else
                throw std::runtime_error("no argument for index");
        }
        else
            result << *i;
        
    }
    
    return result.str();
}
