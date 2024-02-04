#include <iostream>
#include <mutex>
#include <thread>

int SharedResource1 =0;
int SharedResource2 =0;
std::mutex global;

void add1()
{
    global.lock();
    SharedResource1++;
}

void add2()
{
    global.lock();
    SharedResource2++;
}

int main()
{   std::thread t1(add1);
    std::thread t2(add2);

    std::cout << SharedResource1 << SharedResource2 << std::endl;
}
    
/*
problem of sharing one single mutex... second thread has to wait until first thread finish using the mutex

*/