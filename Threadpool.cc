//
// Created by 28108 on 2022/11/24.
//
#include "TaskQueue.hpp"
#include "Threadpool.h"

void ThreadPool::init() {

    for(int i=0;i<work_threads.size();++i)
    {
        work_threads[i]=thread(Work(this,i));
    }
}

ThreadPool::~ThreadPool() {
    shutdown();
}

void ThreadPool::shutdown() {
    m_shutdown=true;
    cond.notify_all();
    for(auto & work_thread : work_threads)
    {
        if(work_thread.joinable())
        {
            work_thread.join();
        }
    }
}

void ThreadPool::Work::operator()() {

    std::function<void()>task;
    bool dequeued;
    while(!m_pool->m_shutdown)
    {
        {
            std::unique_lock<std::mutex>locker(m_pool->m_mutex);
            if(m_pool->tasks.empty())
            {
                std::cout<<m_id<<" is blocked"<<std::endl;
                m_pool->cond.wait(locker);
            }
            std::cout<<"be waked id is "<<m_id<<std::endl;
            dequeued=m_pool->tasks.pop(task);
        }
        if(dequeued)
        {
            task();
        }
    }
}
