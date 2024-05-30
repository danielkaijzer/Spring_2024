#include <iostream>
#include <thread>
#include <mutex>

int glob{0}; // global variable

std::mutex for_glob;

void increment(){
    for_glob.lock();
    for (int i =0;i < 20000;i++){
        for_glob.lock();
        glob++; // modify shared resource (critical section)
        for_glob.unlock();
    }
    for_glob.unlock();
}

int main(){
    std::thread T1{increment};
    std::thread T2{increment};

    T1.join(); // main thread (main prog) waits for thread T1 to complete before continuing
    T2.join();

    std::cout << glob << std::endl;
}

// a critical section is a portion of code where a shared resource is accessed
// and where overlapping execution can cause race conditions. 
// Critical sections of code should not have overlapping execution
// by multiple threads/processes to ensure data integrity and consistency.