#include<stack>
using namespace std;

const int ERR = 1;
void delete_spaces(char* str, char* argv);
int get_stacks(char* beg, stack<int>& numbers, stack<char>& signs);
int get_result(int& res, stack<int>& numbers, stack<char>&signs);
int calculator (int& value, char* argv[]);