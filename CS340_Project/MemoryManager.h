#ifndef _MEMORYMANAGER_H
#define _MEMORYMANAGER_H

#include <iosfwd> // SimOS will include <iostream>

struct MemoryItem
{
    unsigned long long pageNumber;
    unsigned long long frameNumber;
    int PID; // PID of the process using this frame of memory
};
 
using MemoryUsage = std::vector<MemoryItem>;


class MemoryManager{

};

#endif