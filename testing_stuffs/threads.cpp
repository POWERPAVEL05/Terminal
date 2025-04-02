#include <cstdio>
#include <thread>
#include <mutex>


std::mutex m1;

void test1()
{
        m1.lock();
        printf("1 is running\n");
        m1.unlock();
}

void test2()
{
        m1.lock();
        printf("2 is running\n");
        m1.unlock();
}

int main()
{
   std::thread t1(test1);
   std::thread t2(test2);
   t1.join();
   t2.join();
   return 69;
}