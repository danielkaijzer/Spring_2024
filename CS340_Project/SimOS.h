/**
 * @file SimOS.h
 * @author Daniel Kaijzer
 * @brief Interface file for SimOS class
 * @version 0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _SIMOS_H
#define _SIMOS_H

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include "CPUManager.h"
#include "DiskManager.h"
#include "MemoryManager.h"

// essentially acts as a Process Control Block
struct Process{
    unsigned int pid_{0};
    std::vector<unsigned int> children;
    int disk{-1}; // initialize disk to -1 since process isn't using a disk 

    int parent_pid{0};

    bool waiting{false}; // process is waiting to collect exit status of child
    bool zombie{false}; // parent hasn't called wait yet

    // parameterized constructor
    Process(unsigned int pid) : pid_(pid) {}
};

class SimOS {
    private:
        int PID_counter{0};

        CPUManager cpu;
        DiskManager disks;
        MemoryManager ram;

        std::unordered_map<int, Process> processes; // acts like a process table
        
        /**
         * @brief Returns PID of parent of process given by pid
         * 
         * @param pid of process you want to find parent for
         * @return pid of parent
         */
        int GetParentPID(int pid);

        /**
         * @brief Terminates process
         * implements cascading termination
         * @param pid 
         */
        void TerminateProcess(int pid);

        /**
         * @brief kills children
         * 
         * @param pid 
         */
        void TerminateChildren(int pid);

        /**
         * @brief Turns process into zombie
         * i.e., all resources are removed but process remains in process table
         * only if parent process hasn't called wait() yet
         * almost identical to TerminateProcess except that we keep process in process table and mark it as a zombie
         */
        void MakeZombie(Process& p);

    public:
        /**
         * @brief Construct a new Sim OS object
         * 
         * Disks, frame, and page enumerations all start from 0.
         * 
         * @param numberOfDisks_ specifies number of hard disks in simulated computer
         * @param amountOfRAM_ specifies amount of memory
         * @param pageSize_ specifies page size
         */
        SimOS(int numberOfDisks, unsigned long long amountOfRAM, unsigned int pageSize);

        

        /**
         * @brief creates a new process in simulated system.
         * 
         * The new process takes place in the ready-queue or immediately starts using the CPU.
         * 
         * Every process in the simulated system has a PID. 
         * 
         * Your simulation assigns PIDs to a new process starting from 1
         * and increments it by one for each process.
         * 
         * Do NOT reuse PIDs of the terminated processes.
         */
        void NewProcess();


        /**
         * @brief The currently running process forks a child.
         * 
         * The child is placed in the end of the ready-queue.
         */
        void SimFork();


        /**
         * @brief The process that is currently using the CPU terminates.
         * 
         * Make sure you release the memory used by this process immediately.
         * 
         * If its parent is already waiting, the process terminates immediately
         * and the parent becomes runnable (goes to the ready-queue).
         * 
         * If its parent hasn't called wait yet, the process turns into a zombie.
         * 
         * To avoid the appearance of orphans, the system implements cascading termination.
         * (if a process terminates, all its descendants terminate with it).
         */
        void SimExit();


        /**
         * @brief The process wants to pause and wait for any of its child processes to terminate.
         * 
         * Once the wait is over, the process goes to the end of the ready-queue or the CPU.
         * 
         * If the zombie-child already exists, the process proceeds right away (keeps using the CPU)
         * and the zombie-child disappears.
         * 
         * If more than one zombie-child exists,
         * the system uses ANY one of them to immediately resume the parent,
         * while other zombies keep waiting for the next wait from the parent.
         */
        void SimWait();


        /**
         * @brief Interrupt arrives from the timer signaling that
         * the time slice of the currently running process is over.
         */
        void TimerInterrupt();


        /**
         * @brief Currently running process requests to read
         * the specified file from the disk with a given number.
         * 
         * The process issuing disk reading requests immediately stops using the CPU,
         * even if the ready-queue is empty (in this case CPU becomes idle)
         * 
         * If a disk with the requested number doesn’t exist throw std::out_of_range exception.
         * 
         * @param diskNumber 
         * @param fileName 
         */
        void DiskReadRequest( int diskNumber, std::string fileName );


        /**
         * @brief A disks with a specified number reports that a single job is completed.
         * The served process should return to the ready-queue.
         * 
         * If a disk with the requested number doesn’t exist throw std::out_of_range exception.
         * 
         * @param diskNumber 
         */
        void DiskJobCompleted( int diskNumber );

        /**
         * @brief Currently running process wants to access the specified logical memory address.
         * 
         * System makes sure the corresponding page is loaded in RAM.
         * If the corresponding page is already in RAM, its "recently used" information is updated.
         * 
         * @param address 
         */
        void AccessMemoryAddress(unsigned long long address);


        /**
         * @brief returns PID of process currently using CPU
         * 
         * If CPU is idle it returns NO_PROCESS
         * 
         * Uses GetProcessUsingCPU() from CPUManager class to get PID of process using CPU
         * 
         * @return int (PID)
         */
        int GetCPU();

        /**
         * @brief Get the Ready Queue object (from CPUManager)
         * 
         * Use GetReadyQueueFromCPUManager method of CPUManager class
         * 
         * @return std::deque<int> with PIDs of processes in the ready-queue
         * where the element in front corresponds with the start of the ready-queue.
         */
        std::deque<int> GetReadyQueue();


        /**
         * @brief Get the Memory object from MemoryManager
         * 
         * Remember, terminated "zombie" processes don't use memory,
         * so they don't contribute to memory usage.
         * 
         * MemoryItems appears in the MemoryUsage vector in the order they appear in memory 
         * (from low addresses to high)
         * 
         * @return MemoryUsage vector describing all currently used frames of RAM.
         */
        MemoryUsage GetMemory();


        /**
         * @brief returns an object with PID of the process served by 
         * specified disk and the name of the file read for that process.
         * 
         * If the disk is idle, GetDisk returns the default FileReadRequest object
         * (with PID 0 and the empty string in fileName)
         * 
         * If a disk with the requested number doesn’t exist throw std::out_of_range exception.
         * 
         * @param diskNumber 
         * @return FileReadRequest (with PID and file name)
         */
        FileReadRequest GetDisk(int diskNumber);


        /**
         * @brief Get the Disk Queue object
         * 
         * Returns the I/O-queue of the specified disk starting from the "next to be served" process
         * 
         * If a disk with the requested number doesn’t exist throw std::out_of_range exception.
         * 
         * @param diskNumber 
         * @return std::deque<FileReadRequest> (I/O-queue of specified disk)
         */
        std::deque<FileReadRequest> GetDiskQueue( int diskNumber );
        
        
};

#endif