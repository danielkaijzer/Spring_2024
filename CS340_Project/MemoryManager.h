#ifndef _MEMORYMANAGER_H
#define _MEMORYMANAGER_H

#include <iosfwd> // SimOS will include <iostream>

// simulate paging. If memory is full, the least recently used frame is removed from memory.
// I can ask your libary to simulate large amounts of memory 
// It is NOT ALLOWED to represent each byte of memory individually. 
// E.g., you can't use a vector with 1000 elements to represent 1000 bytes of memory

struct MemoryItem
{
    unsigned long long pageNumber;
    unsigned long long frameNumber;
    int PID; // PID of the process using this frame of memory
};
 
using MemoryUsage = std::vector<MemoryItem>;


class MemoryManager{
    private:
        // pages and frames start at 0
        unsigned int pageSize_;
        unsigned long long totalFrames_;

        MemoryUsage memory;

    public:
        MemoryManager() = default;

        MemoryManager(unsigned long long amountOfRAM, unsigned int pageSize){
            this->pageSize_ = pageSize;
            this->totalFrames_ = amountOfRAM/pageSize;
        }

        // void AccessMemoryAddressMM(unsigned long long address){}

        // MemoryUsage GetMemoryMM(){};
        
        MemoryUsage GetMemory(){
            return memory;
        }


       /**
        * @brief Remove process from RAM (frames and pages)
        * 
        * @param pid 
        */
        void removeProcessFromMemory(int pid){

            // iterate through memory (vector of MemoryItems) 
            // to remove frames and pages with specified process
        }


        /*
        Currently running process wants to access the specified logical memory address. 
        System makes sure the corresponding page is loaded in the RAM. 
        If the corresponding page is already in the RAM, 
        its “recently used” information is updated.
        */
        void AccessMemoryAddress(unsigned long long address, int process_using_cpu){

        }

};

#endif