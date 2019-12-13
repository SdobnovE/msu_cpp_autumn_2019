#pragma once
#include <queue>
#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <mutex>
#include <condition_variable>




class ThreadPool
{
public:
    ThreadPool(size_t poolSize);
    ~ThreadPool();
    
    template <class Func, class... Args>
    auto exec(Func&& func, Args&&... args)->std::future<decltype(func(args...))>;

    
private:
    
    bool exit;
    std::queue<std::function<void()>> _que_task;
    std::vector<std::thread> _threads;
    std::mutex _mut;
    std::condition_variable _cond;
    friend void thread_func(ThreadPool* This);
    
};

template<class F>
auto make_function_copyable(F&& f ) 
{
    auto sp = std::make_shared<std::decay_t<F>>(std::forward<F>(f));
    return [sp](auto&&...args){return (*sp)(std::forward<decltype(args)>(args)...);};
}

template <class Func, class... Args>
auto ThreadPool::exec(Func&& func, Args&&... args)->std::future<decltype(func(args...))>
{
    
    using return_type = decltype( func(args...) );

    auto task = std::packaged_task <decltype (func(args...))()>(
        std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
        );

    auto future = task.get_future();


    
    {
        std::unique_lock<std::mutex> lock(_mut);
        _que_task.push(make_function_copyable(std::move(task)));
    }
    
    _cond.notify_one();
   
    return future;
}



void thread_func(ThreadPool* This)
{
    std::function<void()> task;

    while (true)
    {   
        {
            std::unique_lock<std::mutex> lock(This->_mut);
            
            This->_cond.wait(lock, 
                [This](){ return (This->_que_task.size() > 0) || This->exit;}
                );
            
            
            if (This->_que_task.size() > 0)
            {
                task = This->_que_task.front();
                This->_que_task.pop();
            }
            else
            {
                break;
            }
        }
        task();


    }

}

ThreadPool::ThreadPool(size_t poolSize) : exit(false)
{
    for (size_t i = 0; i < poolSize; i++)
        _threads.push_back(std::thread(thread_func, this));
    // for (auto& i : _threads)
    //     i.join();
}


ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(_mut);
        exit = true;
    }

    _cond.notify_all();

    for (auto& i : _threads)
        i.join();
        
}
