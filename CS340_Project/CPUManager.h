#ifndef _CPUMANAGER_H
#define _CPUMANAGER_H

#include <iosfwd> // SimOS will include <iostream>
#include <deque> // include STL double ended queue data structure for ready-queue implementation

constexpr int NO_PROCESS{ 0 };

class CPUManager{
    private:
        std::deque<int> readyQueue;
        int cpu;
        // int PID_counter;

    public:

        /**
         * @brief Construct a new CPUManager object
         * 
         * default cpu to equal 0 (meaning it is idle)
         * 
         */
        CPUManager(){
            cpu = NO_PROCESS;
        }
    

        /**
         * @brief Adds a process to ready queue or to CPU if ready queue is empty
         * 
         * Make sure to push back to readyQueue only if CPU isn't idle
         * 
         * @param pid 
         */
        void AddToReadyQueue(int pid){
            if(cpu != NO_PROCESS){
                readyQueue.push_back(pid);
            }

        }

        /**
         * @brief returns PID of process using CPU
         * 
         * If CPU is idle, then return 0
         * 
         */
        int GetProcessUsingCPU();

        std::deque<int> GetReadyQueueFromCPUManager();
};

#endif

