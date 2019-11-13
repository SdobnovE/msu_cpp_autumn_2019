#include <iostream>
#include <stdio.h>
#include "bigint.h"
#include <new>
 
using std::cout;

 
int main(){
   BigInt a = 9223372036854775807, b = 86;
   //99 - 100
   //100 - 100
   cout << a  + b + a + b - a - a - b - b + a + a + a + a - a - a - a - a<< std::endl;
   
}