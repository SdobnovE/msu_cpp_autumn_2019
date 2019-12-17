#pragma once

#include<thread>
#include<string>
#include<condition_variable>
#include<mutex>
#include<fstream>
#include<string>
#include<vector>

#include<functional>


const size_t SIZE = 100000000;//Размер массива данных
const size_t LEN = 524288;//Размер одного из двух буферов, Уполовиним память т.к. q-sort с доп. памятью

struct data
{
    uint64_t* memory1;//Выделенная память
    uint64_t* memory2;
    size_t& len1;
    size_t& len2;

    std::mutex& mut;
    size_t id;//id потока
    
    std::ifstream& File;//основной файл с данными
    size_t& que;//Номер последнего файла в очереди
    size_t& curr_in_que;//номер последнего прочитанного файла в очереди
};

void merge_files (const std::string& from1_, const std::string& from2_, const std::string& where_, uint64_t* mem1, uint64_t* mem2);
bool create_data(const std::string& filename);
bool read_data (const std::string& name, std::vector<uint64_t>& vec);
void thread_func(data Dat);
bool compare_files(const std::string& file1, const std::string& file2);
void barrier_wait(size_t total_threads);