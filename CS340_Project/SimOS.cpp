#include "SimOS.h"

SimOS::SimOS(int numberOfDisks, unsigned long long amountOfRAM, unsigned int pageSize){
    // init disk manager to have specified num of disks
    this->disks = DiskManager(numberOfDisks);

    // init MemoryManager to have specified amount of RAM and pages
    this->ram = MemoryManager(amountOfRAM,pageSize);

}

void SimOS::NewProcess(){}

void SimOS::SimFork(){}

void SimOS::SimExit(){}

void SimOS::SimWait(){}

void SimOS::TimerInterrupt(){}

void SimOS::DiskReadRequest( int diskNumber, std::string fileName ){}

void SimOS::DiskJobCompleted( int diskNumber ){}

void SimOS::AccessMemoryAddress(unsigned long long address){}

int SimOS::GetCPU(){}

std::deque<int> SimOS::GetReadyQueue(){}

MemoryUsage SimOS::GetMemory(){}

FileReadRequest SimOS::GetDisk(int diskNumber){}

std::deque<FileReadRequest> SimOS::GetDiskQueue( int diskNumber ){}
      
