#include "SimOS.h"

SimOS::SimOS(int numberOfDisks, unsigned long long amountOfRAM, unsigned int pageSize){
    // init disk manager to have specified num of disks
    this->disks = DiskManager(numberOfDisks);

    // init MemoryManager to have specified amount of RAM and pages
    this->ram = MemoryManager(amountOfRAM,pageSize);

}

void SimOS::NewProcess(){
    PID_counter++;
    this->cpu.AddToReadyQueue(PID_counter); // Add new process to readyQueue
}

void SimOS::SimFork(){
    if(!this->cpu.GetProcessUsingCPU()){ // if CPU is idle throw error
        throw std::logic_error("CPU is idle");
    }
    int childPID = ++PID_counter;
    this->cpu.AddToReadyQueue(childPID);
}

void SimOS::SimExit(){
    if(!this->cpu.GetProcessUsingCPU()){ // if CPU is idle throw error
        throw std::logic_error("CPU is idle");
    }

}

void SimOS::SimWait(){
    // TBD
}

void SimOS::TimerInterrupt(){
    this->cpu.CPUTimerInterrupt();
}

void SimOS::DiskReadRequest( int diskNumber, std::string fileName ){
    // current process using CPU requests to read file from Disk diskNumber
    this->disks.ReadFromDisk(this->cpu.GetProcessUsingCPU(),diskNumber,fileName);

    // remove current process from CPU, 
    this->cpu.RemoveProcessFromCPU();

}

void SimOS::DiskJobCompleted( int diskNumber ){}

void SimOS::AccessMemoryAddress(unsigned long long address){}

int SimOS::GetCPU(){
    return this->cpu.GetProcessUsingCPU();
}

std::deque<int> SimOS::GetReadyQueue(){
    return this->cpu.GetReadyQueueFromCPUManager();
}

MemoryUsage SimOS::GetMemory(){}

FileReadRequest SimOS::GetDisk(int diskNumber){}

std::deque<FileReadRequest> SimOS::GetDiskQueue( int diskNumber ){}
      
