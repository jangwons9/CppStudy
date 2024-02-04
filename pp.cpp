False sharing = vector/array of threads with their own memory allocation
                later they sum each elements
                BUT result in slower process
                CPU Hardware with each cache line in each core has to get 64 byte of memory
                So each core's cache line is different so need synchronization in b/w steps so its slow
                -- this is called False sharing--> accessing memory thats not synced
        2 solutions : Padding to fill 64 bytes & Mutex



MUTEX-( lock the resource before actual computation)
lock --> if not yet has to wait
trylock--> return to its own job

-- problem of sharing one single mutex... second thread has to wait until first thread finish using the mutex
    
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
    


Deadlock --> each threads waits for each other mutex to unlock
        To avoid: 1) must lock in same order
                  2) use lock_gaurd or scoped_lock
    
    int SharedResource1 =0;
    int SharedResource2 =0;
    std::mutex global1;
    std::mutex global2;
    void add1()
    {
        global1.lock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        global2.lock();
        SharedResource1++;
    }
    void add2()
    {
        global1.lock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        global2.lock();
         SharedResource2++;
    }
    

std::lock_gaurd vs std::scoped_lock
~RAII(lock_gaurd) --> allow self unlock so no deadlock  std::lock_gaurd<std::mutex> lock(gMutex)
~ScopedLock --> can lock multiple lock at once like locking in order and unlock automatically
scope of contruction and destruction of Lock_gaurd is the entire scope BUT scoped_lock is within smaller scopes
Simple answer! single mutex --> lock_gaurd & multiple mutex --> scoped_lock
    
    void add1() //Lockgaurd
    {
        std::lock_gaurd<std::thread> lock(global1);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_gaurd<std::thread> lock(global2);
        SharedResource1++;
    }
    void add2() // Scopedlock
    {
        std::scoped_lock(global1, global2);
        SharedResource2++;
    }
    


Condition Variable = variable to communicate b/w 2 or more threads
cv.wait() method releases the lock until the condition is met, condition =1
cv.notify_one() notifies the thread to wake up and reacquire the lock

    
    std::mutex mutex;
    std::condition_variable cv;
    int condition = 0;

    void fnc(){
        std::unique_lock<std::mutex> lock(m); //lock acquired by instantiation
        cv.wait(lock, []{return condition ==1 ;}) // lock is released upon call, is now waiting
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
    