#include "SimOS.h"

SimOS::SimOS(int numberOfDisks, unsigned long long amountOfRAM, unsigned int pageSize){
    // init disk manager to have specified num of disks
    this->disks = DiskManager(numberOfDisks);

    // init MemoryManager to have specified amount of RAM and pages
    this->ram = MemoryManager(amountOfRAM,pageSize);

}

void SimOS::NewProcess(){
    PID_counter++;
    processes[PID_counter] = Process(PID_counter);

    this->cpu.AddToReadyQueue(PID_counter); // Add new process to readyQueue or CPU if idle
    
}

void SimOS::SimFork(){
    this->cpu.CPU_Idle_ErrorCheck(); // if CPU idle throw error

    // create child
    PID_counter++;
    int childPID = PID_counter;
    processes[PID_counter] = Process(childPID);

    // parent tracks new child
    processes[this->cpu.GetProcessUsingCPU()].children.push_back(childPID);

    // add child to readyQueue
    this->cpu.AddToReadyQueue(childPID);
}

void SimOS::TimerInterrupt(){
    this->cpu.CPUTimerInterrupt();
}

void SimOS::DiskReadRequest( int diskNumber, std::string fileName ){

    // current process using CPU requests to read file from Disk diskNumber
    this->disks.ReadFromDisk(this->cpu.GetProcessUsingCPU(),diskNumber,fileName);

    // track the disk the process will be using
    processes[this->cpu.GetProcessUsingCPU()].disk = diskNumber;
    
    // remove current process from CPU, 
    this->cpu.RemoveCurrentProcessFromCPU();

}

void SimOS::DiskJobCompleted( int diskNumber ){
    int servedProcessPID = this->GetDisk(diskNumber).PID;

    // "Complete" job by dequeing from front of IO queue
    disks.dequeFrontIOQueue(diskNumber);

    // update disk tracking for process that has been served
    processes[servedProcessPID].disk = -1; // process no longer using disk

    // move served process back to readyQueue
    this->cpu.AddToReadyQueue(servedProcessPID);

}

void SimOS::AccessMemoryAddress(unsigned long long address){
    // check if CPU idle
    cpu.CPU_Idle_ErrorCheck();
    
    // MemoryManager will handle the memory address access operation
    ram.AccessMemoryAddress(address,this->cpu.GetProcessUsingCPU());
}

int SimOS::GetCPU(){
    return this->cpu.GetProcessUsingCPU();
}

std::deque<int> SimOS::GetReadyQueue(){
    return this->cpu.GetReadyQueueFromCPUManager();
}

MemoryUsage SimOS::GetMemory(){
    this->ram.GetMemory();
}

FileReadRequest SimOS::GetDisk(int diskNumber){
    return this->disks.GetDisk(diskNumber);
}

std::deque<FileReadRequest> SimOS::GetDiskQueue( int diskNumber ){
    return disks.GetDiskQueue(diskNumber);
}


void SimOS::SimExit(){
    this->cpu.CPU_Idle_ErrorCheck(); // if CPU idle throw error

    // terminate process, terminates it's children (and release from memory)
    TerminateProcess(this->cpu.GetProcessUsingCPU());
    this->cpu.RemoveCurrentProcessFromCPU();

}
      
void SimOS::TerminateProcess(int pid){
    std::vector<unsigned int> children = processes[pid].children;

    // terminate children
    for (int childPID : children){ // recursively
        TerminateProcess(childPID);
    }

    // Remove process from memory
    this->ram.RemoveProcessFromMemory(pid);

    // Remove processes from readyQueue
    this->cpu.RemoveProcessFromReadyQueue(pid);

    // Remove process from diskQueue
    this->disks.RemoveProcessFromIOQueues(pid, processes[pid].disk);
    
    // remove process from map of processes
    processes.erase(pid);
}

// -------------- TO DO ---------------

void SimOS::SimWait(){
    // TO DO

    cpu.CPU_Idle_ErrorCheck(); // check if CPU idle, throw error if so

    // check for zombie children
    // terminate zombies

    // if there's no zombie children,
    // process pauses and waits
    // activate next process in readyQueue

    // if zombie child exists,
    // continue execution (process keeps using CPU)


}