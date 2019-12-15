#include<stdio.h>
#include<iostream>
#include<fstream>
#include<queue>
#include<algorithm>
#include<thread>
#include<string>
#include<condition_variable>
#include<mutex>
#include<functional>
using namespace std;
const size_t SIZE = 100000000;//Размер массива данных
const size_t LEN = 524288 / 2;//Размер одного из двух буферов, Уполовиним память т.к. q-sort с доп. памятью


struct data
{
    uint64_t* memory;//Выделенная память
    mutex& mut;
    size_t id;//id потока
    
    ifstream& FILE;//основной файл с данными
    size_t& que;//Номер последнего файла в очереди
    size_t& curr_in_que;//номер последнего прочитанного файла в очереди
};



void merge_files (string from1, string from2, string where, uint64_t* mem1, uint64_t* mem2);
bool create_data();
bool read_data (string name, vector<uint64_t>& vec);
void thread_func(data Dat);
bool compare_files(string file1, string file2);




bool create_data(string filename)
{
    std::ofstream FILE_WRITE;
    
    FILE_WRITE.open(filename, std::ios::binary);
    
    if (!FILE_WRITE.is_open())
        return false;
    
    
    for (size_t i = 0; i < SIZE; i++) 
    {
        size_t rnd = random() % 1000000;
        FILE_WRITE.write(reinterpret_cast<char*>( &rnd ), sizeof(uint64_t));

    }
    
    FILE_WRITE.close();
    return true;
}


bool read_data (string name, vector<uint64_t>& vec)
{
    std::ifstream FILE_READ;
    FILE_READ.open(name, std::ios::binary);
    
    if (!FILE_READ.is_open())
        return false;
    
    for (size_t i = 0; i < SIZE; i++) 
    {
        size_t rnd;
        FILE_READ.read(reinterpret_cast<char*>( &rnd ), sizeof(uint64_t));
        if (!FILE_READ)
            break;
        vec.push_back(rnd);
    }
    
    FILE_READ.close();
    return true;
}




void thread_func(data Dat)
{
    
    uint64_t* mem = nullptr;
    
    mem = Dat.memory;
    
    
    size_t len = 0;
    string name_file = "";
 
    while (true)
    {
        uint64_t val = 0;

        {
            unique_lock<mutex> lock(Dat.mut);
            len = 0;
            for (size_t i = 0; i < LEN; i++)
            {
                
                Dat.FILE.read(reinterpret_cast<char*>(&val), sizeof(uint64_t));
                
                if (!Dat.FILE)
                { 
                    break;
                }
                else
                {
                    mem[i] = val;
                    len++;

                }
            }   
        }
        if (len == 0)
            break;

        
        {
            unique_lock<mutex> lock(Dat.mut);
            name_file = to_string(Dat.que);
            Dat.que++;
        }
        
        ofstream curr_file;
        sort(mem, mem + len);
        curr_file.open (name_file, std::ios::binary);
        
        for (size_t i = 0; i < len; i++) 
        {
            curr_file.write(reinterpret_cast<char*>( &mem[i] ), sizeof(uint64_t));

        }
        curr_file.close();



    }

    string file1, file2, out;

    // НАДО БЫ pthread_barrier_wait...

    while (true)
    {
        {
            unique_lock<mutex> lock(Dat.mut);

            if (Dat.que - Dat.curr_in_que == 0)
                break;
                
            file1 = to_string(Dat.curr_in_que);
            file2 = to_string(Dat.curr_in_que + 1);

            if (Dat.curr_in_que + 2 - Dat.que == 0)
            {
                out = "final";
                Dat.curr_in_que += 2;
            }
            else
            {
                out = to_string(Dat.que);

                Dat.que++;
                Dat.curr_in_que += 2;
            }
            
            

        }

        merge_files (file1, file2, out, mem, mem + LEN / 2);


    }
    
    
}

void merge_files (string from1, string from2, string where, uint64_t* mem1, uint64_t* mem2)
{
    ifstream FROM1, FROM2;
    ofstream WHERE;
    
    FROM1.open(from1, std::ios::binary);
    FROM2.open(from2, std::ios::binary);
    WHERE.open(where, std::ios::binary);
    
    size_t len_arr = LEN / 2;
    size_t curr_len1 = 0, curr_len2 = 0;
    size_t val;

    while (true)
    {
        for (size_t i = curr_len1; i < len_arr; i++)//Считываем из первого файла
        {
            FROM1.read(reinterpret_cast<char*>(&val), sizeof(uint64_t));
                
            if (!FROM1)
            { 
                break;
            }
            else
            {
                
                mem1[i] = val;
                curr_len1++;
            }
            
        }

        for (size_t i = curr_len2; i < len_arr; i++)//Считываем из второго файла
        {
            FROM2.read(reinterpret_cast<char*>(&val), sizeof(uint64_t));
                
            if (!FROM2)
            { 
                break;
            }
            else
            {
                
                mem2[i] = val;
                curr_len2++;
            }

        }

        if (curr_len1 == 0 && curr_len2 == 0)////Заходим, если вообще ничего не прочитали
            break;

        if (curr_len1 == 0)//Заходим, если вообще ничего не прочитали в первый массив
        {
            for (size_t i = 0; i < curr_len2; i++)
                WHERE.write(reinterpret_cast<char*>( mem2 + i ), sizeof(uint64_t));

            curr_len2 = 0;
            continue;
        }

        if (curr_len2 == 0)//Заходим, если вообще ничего не прочитали во второй массив
        {
            for (size_t i = 0; i < curr_len1; i++)
                WHERE.write(reinterpret_cast<char*>( mem1 + i ), sizeof(uint64_t));
            
            curr_len1 = 0;  
            continue;
        }

        size_t fir = 0, sec = 0;

        while ( !( (fir == curr_len1) || (sec == curr_len2) ) )//Сливаем в файл
        {
            if (mem1[fir] < mem2[sec])
            {
                WHERE.write(reinterpret_cast<char*>( mem1 + fir ), sizeof(uint64_t));
                fir++;
            }
            else
            {
                WHERE.write(reinterpret_cast<char*>( mem2 + sec ), sizeof(uint64_t));
                sec++;
            }
            
        }
        //НАДО СКОПИРОВАТЬ(СДВИНУТЬ МАССИВ НАЗАД, для добавления в него элементов)
        for (size_t i = 0; i < curr_len1 - fir; i++)
        {
            mem1[i] = mem1[fir + i];
        }

        for (size_t i = 0; i < curr_len2 - sec; i++)
        {
            mem2[i] = mem2[sec + i];
        }

        curr_len1 -= fir;
        curr_len2 -= sec;


    }
    WHERE.close();
    FROM1.close();
    FROM2.close();

}

bool compare_files(string file1, string file2)
{
    vector<uint64_t> fir, sec;

    read_data(file1, fir);
    read_data(file2, sec);
    
    if ( fir.size() != sec.size())
        return false;

    sort(fir.begin(), fir.end());


    for (size_t i = 0; i < fir.size(); i++)
    {
        if (fir[i] != sec[i])
            return false;
    }

    return true;
}


int main()
{
    
    uint64_t* memory1 = new uint64_t[LEN];
    uint64_t* memory2 = new uint64_t[LEN];
    mutex mut;
    ifstream FILE;
    
    size_t que = 0;
    size_t curr_que = 0;
    
    string DATA_NAME = "data";
    
    /*1*/auto time = std::chrono::high_resolution_clock::now();

    create_data(DATA_NAME);

    /*1*/auto T1 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - time ).count();
    



    FILE.open(DATA_NAME, std::ios::binary);
    


    /*2*/time = std::chrono::high_resolution_clock::now(); 
    
    thread t1(bind(thread_func, data{memory1, mut, 0, FILE, que, curr_que}));
    thread t2(bind(thread_func, data{memory2, mut, 1, FILE, que, curr_que}));
    
    t1.join();
    t2.join();

    /*2*/auto T2 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - time ).count();
    
    
    
    
    FILE.close();
    


    /*3*/time = std::chrono::high_resolution_clock::now(); 

    if (!compare_files(DATA_NAME, "final"))
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

