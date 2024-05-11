#ifndef _CPUMANAGER_H
#define _CPUMANAGER_H

#include <iosfwd> // SimOS will include <iostream>
//#include <deque> // include STL double ended queue data structure for ready-queue implementation

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

        // similar to CPUTimerInterrupt except that we don't move process to readyQueue
        // this is used for DiskReadRequest(), Exit() and Wait()
        void RemoveCurrentProcessFromCPU(){
            CPU_Idle_ErrorCheck(); // check if CPU idle

            // if readyQueue is empty, then CPU will be idle
            if (readyQueue.empty()){
                process_using_cpu = NO_PROCESS;
            }
            else{ // else CPU will now run process at front of readyQueue
                process_using_cpu = readyQueue.front();
                readyQueue.pop_front();
            }
        }

        /**
         * @brief Implements timer interrupt from OS
         * Removes current process using cpu
         * Place that process in the back of readyQueue
         * Move process at front of readyQueue to CPU 
         */
        void CPUTimerInterrupt(){
            CPU_Idle_ErrorCheck(); // check if CPU idle

            int process_to_interrupt = process_using_cpu;

            RemoveCurrentProcessFromCPU();

            // add interrupted process to readyQueue
            readyQueue.push_back(process_to_interrupt);
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

        void RemoveProcessFromReadyQueue(int pid){
            if(readyQueue.empty()){ // first check if readyQueue is empty
                return; // if readyQueue empty there's no need to look
            }

            // search readyQueue for process to be terminated
            for (auto itr = readyQueue.begin(); itr != readyQueue.end();){
                if (*itr == pid){ // if process found in readyQueue
                    itr = readyQueue.erase(itr); // returns next iterator
                    return; // no need to keep looking
                }
                else{
                    ++itr;
                }
            }
        }


        /**
         * @brief Check if CPU is idle, if it is throw exception
         * 
         * @return true 
         * @return false 
         */
        bool CPU_Idle_ErrorCheck(){
            if(process_using_cpu == NO_PROCESS){
                throw std::logic_error("CPU is idle");
            }
        }
};

#endif

