//
// Created by 28108 on 2022/11/24.
//
#include<iostream>
#include<functional>
#include"../Threadpool.h"
int test1(){
    std::cout<<"this is test1"<<std::endl;
    return 10;
}
void test2(){
    std::cout<<"this is test2"<<std::endl;
}
void test3(){
    std::cout<<"this is test3"<<std::endl;
}
int main(){
    std::function<decltype(test3())()> func(test3);
    ThreadPool pool;
    //线程的初始化
    pool.init();

    //使用future进行线程同步
    auto future = pool.submit(test1);
    std::cout<<future.get()<<std::endl;

    //普通函数
    pool.submit(test2);

    //function
    pool.submit(func);

    //lambd表达式
    pool.submit([]{
       std::cout<<"this is test4"<<std::endl;
    });

}