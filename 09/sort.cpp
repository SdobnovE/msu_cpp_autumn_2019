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

void barrier_wait(size_t total_threads)
{
    static std::mutex mut;
    static std::condition_variable condvar_in;
    static std::condition_variable condvar_out;
    static size_t threads_in = 0;
    static size_t threads_out = 0;
    std::unique_lock<std::mutex> lock(mut);////////////////
    threads_in++;
    
    if (threads_in >= total_threads)
    { 
        
        //Текущий поток пришёл последним, устанавливаем начальное значение для threads_out
        threads_out = 0;

        //Запускаем остальные
        condvar_in.notify_all();
    }
    else
    {
        //Есть не пришедшие ещё
        
        while (threads_in < total_threads)
            condvar_in.wait(lock);
    }
    
    threads_out++;

    if (threads_out >= total_threads)
    {
        //Текущий пришёл последним
        threads_in = 0;
        condvar_out.notify_all();
    }
    else
    {
        //Есть ещё 
        while (threads_out < total_threads)
            condvar_out.wait(lock);
    }
    
    
}



bool create_data(const string& filename)
{
    std::ofstream file_write;
    
    file_write.open(filename, std::ios::binary);
    
    if (!file_write.is_open())
        return false;
    
    for (size_t i = 0; i < SIZE; i++) 
    {
        size_t rnd = random() % 1000000;
        file_write.write(reinterpret_cast<char*>( &rnd ), sizeof(uint64_t));
    }
    
    file_write.close();
    return true;
}



bool read_data (const string& name, vector<uint64_t>& vec)
{
    std::ifstream file_read;
    file_read.open(name, std::ios::binary);
    
    if (!file_read.is_open())
        return false;
    
    for (size_t i = 0; i < SIZE; i++) 
    {
        size_t rnd;
        file_read.read(reinterpret_cast<char*>( &rnd ), sizeof(uint64_t));
        if (!file_read)
            break;
        vec.push_back(rnd);
    }
    
    file_read.close();
    return true;
}




void thread_func(data Dat)
{
    
    uint64_t* mem = nullptr;
    
    if (Dat.id == 0)
        mem = Dat.memory1;
    else
        mem = Dat.memory2;
    
    
    size_t len = 0;
    string name_file = "";
 
    while (true)
    {
        
        barrier_wait(2);

        uint64_t val = 0;
        if (Dat.id == 0)
        {
            
            Dat.len1 = 0;
            for (size_t i = 0; i < LEN; i++)
            {
                
                Dat.File.read(reinterpret_cast<char*>(&val), sizeof(uint64_t));
                
                if (!Dat.File)
                    break;
                else
                {
                    Dat.memory1[i] = val;
                    Dat.len1++;
                }
            }

            Dat.len2 = 0;
            for (size_t i = 0; i < LEN; i++)
            {
                
                Dat.File.read(reinterpret_cast<char*>(&val), sizeof(uint64_t));
                
                if (!Dat.File)
                    break;
                else
                {
                    Dat.memory2[i] = val;
                    Dat.len2++;
                }
            }   
            
        }
        
        //cout << "HAHAHAHA\n";
        barrier_wait(2);
        
        
        
        if (Dat.id == 0)
            len = Dat.len1;
        else
            len = Dat.len2;

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

        if (Dat.len1 == 0 || Dat.len2 == 0)
        {
            //Нужно сделать, иначе пойдём читать заново и встанем на барьер(Здавствуйте deadlock)
            break;
        }

    }
    

    barrier_wait(2);//Нужен барьер, чтобы не начать вдруг сливать последний файл
    
    string file1, file2, out;
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

void merge_files (const string& from1_, const string& from2_, 
                    const string& where_, uint64_t* mem1, uint64_t* mem2)
{
    ifstream from1, from2;
    ofstream where;
    
    from1.open(from1_, std::ios::binary);
    from2.open(from2_, std::ios::binary);
    where.open(where_, std::ios::binary);
    
    size_t len_arr = LEN / 2;
    size_t curr_len1 = 0, curr_len2 = 0;
    size_t val;

    while (true)
    {
        for (size_t i = curr_len1; i < len_arr; i++)//Считываем из первого файла
        {
            from1.read(reinterpret_cast<char*>(&val), sizeof(uint64_t));
                
            if (!from1)
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
            from2.read(reinterpret_cast<char*>(&val), sizeof(uint64_t));
                
            if (!from2)
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
                where.write(reinterpret_cast<char*>( mem2 + i ), sizeof(uint64_t));

            curr_len2 = 0;
            continue;
        }

        if (curr_len2 == 0)//Заходим, если вообще ничего не прочитали во второй массив
        {
            for (size_t i = 0; i < curr_len1; i++)
                where.write(reinterpret_cast<char*>( mem1 + i ), sizeof(uint64_t));
            
            curr_len1 = 0;  
            continue;
        }

        size_t fir = 0, sec = 0;

        while ( !( (fir == curr_len1) || (sec == curr_len2) ) )//Сливаем в файл
        {
            if (mem1[fir] < mem2[sec])
            {
                where.write(reinterpret_cast<char*>( mem1 + fir ), sizeof(uint64_t));
                fir++;
            }
            else
            {
                where.write(reinterpret_cast<char*>( mem2 + sec ), sizeof(uint64_t));
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
    where.close();
    from1.close();
    from2.close();

}

bool compare_files(const string& file1, const string& file2)
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