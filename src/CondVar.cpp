#include <iostream>
#include <mutex>
#include <thread>

std::mutex m;
std::condition_variable cv;
int condition = 0;

void fnc(){
    std::unique_lock<std::mutex> lock(m); //lock acquired by instantiation
    cv.wait(lock, []{return condition ==1 ;}); // lock is released upon call, is now waiting
    //the reacquiring of lock when condition is met by the lock just above
    lock.unlock(); // manually unlock again
}

int main()
{   
    std::thread waitingT(fnc);// calls fnc
    {// starts a new scoped lock for mutex m
        std::scoped_lock lock(m);
        condition = 1;// locks this shared condition and change it to 1
    }// shared condition unlocked in here
    cv.notify_one(); // notifies the waitingT thread to wake up and try to acquire lock
    // waitingT checks the return condition == 1, only if true it reqacquries the lock
    // then it proceeds to do its job with the lock acuqired by cv.wait
    waitingT.join();

}