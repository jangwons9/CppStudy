#include <iostream>
#include <mutex>
#include <thread>
#include <headertry.h>
//#include <Eigen/Dense> just to try it worked~
//using Eigen::MatrixXd;

int SharedResource1 =0;
int SharedResource2 =0;
std::mutex global;

void add1()
{
    global.lock();
    SharedResource1++;
    std::cout << "haha" << std::endl;
    global.unlock();


}

void add2()
{
    global.lock();
    SharedResource2++;
    std::cout << "haha1212" << std::endl;
    global.unlock();

}

int main()
{   
    std::thread t1(add1);
    // adding t1.join() here makes sure t1 thread execute first
    std::thread t2(add2);

    t1.join();
    t2.join();
    // putting the t1join and t2join together like this make unsure which thread is excuted first
    std::cout << SharedResource1 << SharedResource2 << std::endl;
}
    
/*
problem of sharing one single mutex... second thread has to wait until first thread finish using the mutex

*/