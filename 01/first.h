#include<stack>
using namespace std;
const int ERR = 1;
void delete_spaces(char* str, char* argv);
bool get_stacks(char* beg, stack<int>& numbers, stack<char>& signs);
bool get_result(int& res, stack<int>& numbers, stack<char>&signs);
bool calculator (int& value, char* argv[]);
