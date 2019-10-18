#include<stdio.h>
#include<string.h>
#include<iostream>
#include<stack>
#include"first.h"

using namespace std;


void delete_spaces(char* str, char* argv)
{
    int len = strlen(argv);
    int t = 0;
    for (int i = 0; i < len; i++)
    {
        if (argv[i] == ' ')
            continue;
        else 
        {
            str[t] = argv[i];
            t++;   
        }
    }
    str[t] = '\0';
    
}

int get_stacks(char* beg, stack<int>& numbers, stack<char>& signs)
{
    int t_i;
    bool action = 0;
    
    
    while (beg[0] != '\0')
    {
        //printf ("%s\n", beg);
        if (sscanf (beg, "%d", &t_i) != 1) 
        {
            
            return ERR;
        }
        numbers.push (t_i);
        
        
        string s = to_string(t_i);
        
        
        if (action == 1)
        {
            double a = numbers.top();
            numbers.pop();
            double b = numbers.top();
            numbers.pop();
            
            switch (signs.top())
            {
                case '*':
                    numbers.push(a * b);
                    break;
                
                case '/':
                    if (a == 0)
                        return ERR;
                     numbers.push(b / a);
                     break;
            }
            signs.pop();
            action = 0;
        }
        
        beg += s.length();
        

        
        
        if (beg[0] == '\0')
            break;
        
        
        if (beg[0] != '+' && beg[0] != '-' 
            && beg[0] != '/' && beg[0] != '*')//Check sign
        {
            return ERR;
        }
        
        signs.push (beg[0]);
        beg++;

        while (beg[0] == ' ')
            beg++;

        if (!signs.empty() && (signs.top() == '/' || signs.top() == '*'))
            action = 1;
        
    }
    return 0;

}

int get_result(int& res, stack<int>& numbers, stack<char>&signs)
{
    stack<int> numbers_temp;
    stack<char> signs_temp;
    int num_len = 0;
    for (auto i = 0; !numbers.empty(); i++ )
    {
        num_len++;
        numbers_temp.push(numbers.top());
        numbers.pop();
    }
    int sig_len = 0;
    for (auto i = 0; !signs.empty(); i++ )
    {
        sig_len++;
        signs_temp.push(signs.top());
        signs.pop();
    }
    if (num_len - sig_len != 1)
    {
        return ERR;
    }
    
    int result = numbers_temp.top();
    numbers_temp.pop();
    
    for (auto i = 0; !numbers_temp.empty(); i++ )
    {
        
        switch (signs_temp.top())
        {
            
            case '+':
                result += numbers_temp.top();
                break;
            case '-':
                result -= numbers_temp.top();
                break;
        }
        numbers_temp.pop();
        signs_temp.pop();
    }
    res = result;
    return 0;

}
int calculator (int& value, char* argv[])
{
    int len_argv = strlen (argv[1]);
    if (len_argv == 0)
        return ERR;

    char *str = new char[len_argv];
    
    delete_spaces (str, argv[1]);

    char *beg = str;


    stack<int> numbers;
    stack<char> signs;
    
    if (get_stacks(beg, numbers, signs) != 0)
    {
        delete[] str;
        return ERR;
    }
    int result;
    if (get_result(result, numbers, signs) != 0)
    {
        delete[] str;
        return ERR;
    }
    

    value = result;
    
    delete[] str;
    return 0;
}

int main(int argc, char* argv[])
{
    
    if (argc != 2) 
        return ERR;
    int val = 0;

    if (calculator (val, argv) != 0)
        return ERR;
    cout <<  val << endl;    

    return 0;
}