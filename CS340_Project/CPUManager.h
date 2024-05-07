#ifndef _CPUMANAGER_H
#define _CPUMANAGER_H

#include <iosfwd> // SimOS will include <iostream>
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
        CPUManager(){
            process_using_cpu = NO_PROCESS;
        }
    

        /**
         * @brief Adds a process to ready queue or to CPU if ready queue is empty
         * 
         * Make sure to push back to readyQueue only if CPU isn't idle
         * 
         * @param pid 
         */
        void AddToReadyQueue(int pid){
            if(process_using_cpu != NO_PROCESS){
                readyQueue.push_back(pid);
            }
            else{ // if CPU is idle
                process_using_cpu = pid;
            }
        }

        /**
         * @brief Implements timer interrupt from OS
         * Removes current process using cpu
         * Place that process in the back of readyQueue
         * Move process at front of readyQueue to CPU 
         */
        void CPUTimerInterrupt(){
            if(process_using_cpu == NO_PROCESS){
                throw std::logic_error("CPU is idle");
            }
            
            // remove current process using CPU from  CPU and return to ready queue
            readyQueue.push_back(process_using_cpu);
            process_using_cpu = readyQueue.front();
            readyQueue.pop_front();
        }

        /**
         * @brief returns PID of process using CPU
         * 
         * If CPU is idle, then return 0
         * 
         */
        int GetProcessUsingCPU(){
            return process_using_cpu;
        }

        std::deque<int> GetReadyQueueFromCPUManager(){
            return readyQueue;
        }
};

#endif

