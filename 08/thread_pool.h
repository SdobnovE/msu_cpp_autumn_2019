#pragma once
#include <queue>
#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <mutex>
#include <atomic>
#include <condition_variable>




class ThreadPool
{
public:
    ThreadPool(size_t poolSize);
    ~ThreadPool();
    
    template <class Func, class... Args>
    auto exec(Func&& func, Args&&... args)->std::future<decltype(func(args...))>;

    
private:
    
    std::atomic<bool> exit;
    std::queue<std::function<void()>> _que_task;
    std::vector<std::thread> _threads;
    std::mutex _mut;
    std::condition_variable _cond;
    void thread_func();
    
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



void ThreadPool::thread_func()
{
    std::function<void()> task;

    while (true)
    {   
        {
            std::unique_lock<std::mutex> lock(this->_mut);
            
            this->_cond.wait(lock, 
                [this](){ return (this->_que_task.size() > 0) || this->exit;}
                );
            
            
            if (this->_que_task.size() > 0)
            {
                task = this->_que_task.front();
                this->_que_task.pop();
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
        _threads.emplace_back([this] { this->thread_func();});
    // for (auto& i : _threads)
    //     i.join();
}


ThreadPool::~ThreadPool()
{
    
    exit = true;
    

    _cond.notify_all();

    for (auto& i : _threads)
        i.join();
        
}
