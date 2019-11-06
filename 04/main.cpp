#include <iostream>
#include <stdio.h>

#include <new>
 
using std::cout;
 
 
int main(){
   int *a = malloc(sizeof(int) * 10);             //нашли блок памяти в куче и направили туда указатель а
   int* ptr = new (a) int[10];     //использован placement new      (если в круглых скобках указать &a, то происходит сбой)
 
   for (int i=0; i<10; i++) ptr[i] = i;             //посредством указателя заполнили массив а
   for (int i=0; i<10; i++) cout << a[i] << '\t';   //вывели массив а на экран
   delete []a;      //то, что было выделено new[] чистим delete
 
}