/**
 * @file CPUManager.h
 * @author Daniel Kaijzer
 * @date 2024-05-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _CPUMANAGER_H
#define _CPUMANAGER_H

#include <iostream> 
#include <deque> // include STL double ended queue data structure for ready-queue implementation

constexpr int NO_PROCESS{ 0 };

class CPUManager{
    private:
        std::deque<int> readyQueue;
        int process_using_cpu = NO_PROCESS;

    public:

        /**
         * @brief Construct a new CPUManager object
         * 
         * default cpu to equal 0 (meaning it is idle)
         * 
         */
        CPUManager();
    

        /**
         * @brief Adds a process to ready queue or to CPU if ready queue is empty
         * 
         * Make sure to push back to readyQueue only if CPU isn't idle
         * 
         * @param pid 
         */
        void AddToReadyQueue(int pid);

        /**
         * @brief similar to CPUTimerInterrupt 
         * except that we don't move process to readyQueue
         * this is used for DiskReadRequest(), Exit() and Wait()
         */
        void RemoveCurrentProcessFromCPU();

        /**
         * @brief Implements timer interrupt from OS
         * Removes current process using cpu
         * Place that process in the back of readyQueue
         * Move process at front of readyQueue to CPU 
         */
        void CPUTimerInterrupt();

        /**
         * @brief returns PID of process using CPU
         * 
         * If CPU is idle, then return 0
         * 
         */
        int GetProcessUsingCPU();

        std::deque<int> GetReadyQueueFromCPUManager();

        void RemoveProcessFromReadyQueue(int pid);


        /**
         * @brief Check if CPU is idle, if it is throw exception
         * 
         */
        void CPU_Idle_ErrorCheck();
};

#endif

