/**
 * @file CPUManager.cpp
 * @author Daniel Kaijzer
 * @date 2024-05-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "CPUManager.h"

void CPUManager::AddToReadyQueue(int pid){
    if(process_using_cpu != NO_PROCESS){
        readyQueue.push_back(pid);
    }
    else{ // if CPU is idle
        process_using_cpu = pid;
    }
}

void CPUManager::RemoveCurrentProcessFromCPU(){
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

void CPUManager::CPUTimerInterrupt(){
    CPU_Idle_ErrorCheck(); // check if CPU idle

    int process_to_interrupt = process_using_cpu;

    RemoveCurrentProcessFromCPU();

    // add interrupted process to readyQueue
    readyQueue.push_back(process_to_interrupt);
}

int CPUManager::GetProcessUsingCPU(){
    return process_using_cpu;
}

std::deque<int> CPUManager::GetReadyQueueFromCPUManager(){
    return readyQueue;
}

void CPUManager::RemoveProcessFromReadyQueue(int pid){
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

void CPUManager::CPU_Idle_ErrorCheck(){
    if(process_using_cpu == NO_PROCESS){
        throw std::logic_error("CPU is idle");
    }
}