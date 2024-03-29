#include <iostream>
#include <mutex>
#include <thread>


int SharedResource1 =0;
int SharedResource2 =0;
std::mutex global1;
std::mutex global2;
void add1()
{
    global1.lock();
    std::this_thread::sleep_for(std::chrono::seconds(1)); // can check deadlock directly
    global2.lock();
    SharedResource1++;
}
void add2()
{
    global2.lock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    global1.lock();
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
    
/*
Deadlock --> each threads waits for each other's mutex to unlock
        To avoid: 1) must lock in same order
                  2) use lock_gaurd or scoped_lock
    

*/