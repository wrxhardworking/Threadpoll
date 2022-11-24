
#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include<memory>
#include<iostream>
#include<queue>
#include<thread>
#include<vector>
#include<mutex>
#include<condition_variable>
#include<functional>
#include<future>
#include <utility>
#include"TaskQueue.hpp"

using namespace std;
class ThreadPool
{
public:
    //此处可以修改初始的线程数
    explicit ThreadPool(const int threads=4):work_threads(vector<thread>(threads)),m_shutdown(false){
    }

    ThreadPool(const ThreadPool &) = delete;

    ThreadPool(ThreadPool &&) = delete;

    ThreadPool &operator=(const ThreadPool &) = delete;

    ThreadPool &operator=(ThreadPool &&) = delete;

    ~ThreadPool();

    void init();

    void shutdown();

    template<typename F,typename... Args>//多参数的函数模板
    auto submit(F&&f,Args&& ...args)->std::future<decltype(f(args...))>;//多参数的函数模板化

private:
    class Work{
    public:
        Work(ThreadPool*pool,int id):m_pool(pool),m_id(id){//初始化工作线程
            std::cout<<"thread begin"<<std::endl;
        }

        void operator()();//重载（）开始工作

    private:
        int m_id;       //工作线程的id
        ThreadPool *m_pool;//所属的线程池
    };


    TaskQue<std::function<void()>>tasks;//std::function 用于包装函数
    vector<thread>work_threads;
    condition_variable cond;
    mutex m_mutex;
    bool m_shutdown;
};


template<typename F, typename... Args>
auto ThreadPool::submit(F &&f, Args &&... args) -> future<decltype(f(args...))> {
        std::function<decltype(f(args ...))()>func=std::bind(std::forward<F>(f),std::forward<Args>(args) ...);//避免左右值的歧义
        auto taskptr=make_shared<packaged_task<decltype(f(args ...))()>>(func);//创建了一个智能指针 std::packaged_task的绑定构造 用于期物的创建
        function<void()> task_func=[taskptr](){
            (*taskptr)();
        };
        tasks.push(task_func);//压入任务队列
        cond.notify_one();//唤醒其中的一个线程
        return taskptr->get_future();//返回一个期物 用于在不同线程调用函数返回值
}

#endif
