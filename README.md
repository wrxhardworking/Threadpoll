# cpp11-Threadpoll
Use c 11 implementation of a thread pool,There is a lot of room to improve.
使用c++11实现的线程池，有一定的提升空间。
##  一、维护一个线程安全的任务队列
**知识要点**

 1. 互斥锁
 2. 条件变量
 3.  模板
 4. 万能引用加完美转发
 
 ##  二、实现线程安全的一个线程池
**知识要点：**
 1. 函数重载
 2. 智能指针
 3. function多态函数包装器的使用
 4. future期物的使用(异步提供)
 5. 函数后置返回类型（auto和decltype的混合使用）
 6. 多参函数模板的使用
