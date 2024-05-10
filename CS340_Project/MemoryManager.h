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

        /*
        Currently running process wants to access the specified logical memory address. 
        System makes sure the corresponding page is loaded in the RAM. 
        If the corresponding page is already in the RAM, 
        its “recently used” information is updated.
        */
        void AccessMemoryAddress(unsigned long long address, int process_using_cpu){
            unsigned long long pageNumber = address / pageSize_;

            bool pageFound = false;

            // search memory if requested logical address already loaded into RAM    
            for (auto& frame : memory){
                if (frame.pageNumber == pageNumber && frame.PID == process_using_cpu){
                    pageFound = true;
                    // if page is already in RAM, update recently used
                    UpdateRecentlyUsed(frame);
                    break;
                }
            }

            // if requested logical address is NOT in RAM (i.e., page fault)
            // load page into RAM
            if (!pageFound){
                HandlePageFault(pageNumber,process_using_cpu);
            }

        }


        void UpdateRecentlyUsed(MemoryItem& frame) {
            // Find frame in memory (vector of all memory items)
            auto it = std::find_if(memory.begin(), memory.end(), [&](const MemoryItem& item) {
                return item.pageNumber == frame.pageNumber && item.PID == frame.PID;
            });

            // if frame already exists in memory, move it to the front
            if (it != memory.end()) {
                // Rotate the found frame to the front of the vector
                std::rotate(memory.begin(), it, it + 1);
            }
        }


        // Page fault: A situation where process wants to use a page that is not currently in RAM
        // So page must be loaded from HD into RAM
        void HandlePageFault(unsigned long long pageNumber, int pid) {

            // if memory full, then we must replace requested address with least recently used
            if (memory.size() >= totalFrames_) {

                // Replace the least recently used frame, assumed to be at the end of the vector (memory)
                memory.back().pageNumber = pageNumber;
                memory.back().PID = pid;

                // Move the updated frame to the front to mark as recently used
                std::rotate(memory.begin(), memory.end() - 1, memory.end());

            } 
            
            // else if memory isn't full, then add new frame at the front
            else
            {
                MemoryItem newFrame {pageNumber, static_cast<unsigned long long>(memory.size()), pid};
                memory.insert(memory.begin(), newFrame); // Insert new frame at the front of memory to mark as recently used
            }
        }



       /**
        * @brief Remove process from RAM (frames and pages)
        * 
        * @param pid 
        */
        void RemoveProcessFromMemory(int pid){
            // Remove all frames associated with the process PID
            for (auto itr = memory.begin(); itr != memory.end();) {
                if (itr->PID == pid) {
                    // Erase and get the new iterator pointing to the next element
                    itr = memory.erase(itr);
                } 
                else
                {
                    // Only increment the iterator if no erasure happens
                    ++itr;
                }
            }
        }


};

#endif