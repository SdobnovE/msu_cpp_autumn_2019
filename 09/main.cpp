#include<stdio.h>
#include<iostream>
#include<fstream>
#include<queue>
#include<algorithm>
#include<thread>
#include<pthread.h>
#include<atomic>
#include<string>
#include<condition_variable>
#include<mutex>
#include<functional>
#include"sort.h"
using namespace std;



int main()
{
    
    uint64_t* memory1 = new uint64_t[LEN];
    uint64_t* memory2 = new uint64_t[LEN];
    mutex mut;
    ifstream File;
    
    size_t que = 0;
    size_t curr_que = 0, len1 = 0, len2 = 0;
    
    string Data_Name = "data";
    
    /*1*/auto time = std::chrono::high_resolution_clock::now();

    create_data(Data_Name);

    /*1*/auto T1 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - time ).count();
    
    cout << "WRITE\n";


    File.open(Data_Name, std::ios::binary);
    


    /*2*/time = std::chrono::high_resolution_clock::now(); 
    
    thread t1(bind(thread_func, data{memory1, memory2, len1, len2, mut, 0, File, que, curr_que}));
    thread t2(bind(thread_func, data{memory1, memory2, len1, len2, mut, 1, File, que, curr_que}));
    
    t1.join();
    t2.join();

    /*2*/auto T2 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - time ).count();
    
    
    
    
    File.close();
    


    /*3*/time = std::chrono::high_resolution_clock::now(); 

    if (!compare_files(Data_Name, "final"))
        cout << "WRONG SORT\n";

    else
        cout << "done\n";

    /*3*/auto T3 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - time ).count();



    cout << T1*1e-6 << " " << T2*1e-6 << " " << T3*1e-6 << endl;
    //4.88018 37.3277 12.9579
    delete[] memory1;
    delete[] memory2;
    
    return 0;
    
}

