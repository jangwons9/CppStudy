#include <iostream>
#include <mutex>
#include <thread>


int SharedResource1 =0;
int SharedResource2 =0;
std::mutex global1;
std::mutex global2;

void add1() 
{
    std::scoped_lock(global1, global2);
    SharedResource1++;
}
void add2() 
{
    std::scoped_lock(global1, global2);
    SharedResource2++;
}

int main()
{   
    std::thread t1(add1);
    std::thread t2(add2);

    t1.join();
    t2.join();
    
    std::cout << SharedResource1 << SharedResource2 << std::endl;
}