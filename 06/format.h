#include<iostream>
#include<string>
#include<stdio.h>
#include<sstream>
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
    parse(vec, others...);
}




template<class... Args>
std::string format(const std::string& str, Args&&... args)
{
    std::vector<std::string> string_args; 
    parse(string_args, args...);
    
    size_t i = 0;
    std::stringstream result;
    
    while (str[i] != '\0')
    {
        if (str[i] == '}')
            throw std::runtime_error("}m");
        
        if(str[i] == '{')
        {
            i++;
            std::string number = "";

            while (isdigit (str[i]))// \0 не цифра, так что ок
            {
                number += str[i];
                i++;
            }
            
            if (str[i] != '}')
                throw std::runtime_error("no } symbol");
            
            size_t index = std::stoi(number);

            if (string_args.size() > index)
                result << string_args[index];
            else
                throw std::runtime_error("no argument for index");
        }
        else
            result << str[i];
        i++;
    }
    
    return result.str();
}
