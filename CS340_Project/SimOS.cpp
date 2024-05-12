#include "SimOS.h"

SimOS::SimOS(int numberOfDisks, unsigned long long amountOfRAM, unsigned int pageSize) : disks(numberOfDisks), ram(amountOfRAM,pageSize){}

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
    processes[PID_counter].parent_pid = this->cpu.GetProcessUsingCPU(); // store parent PID in child PCB

    // parent tracks new child
    processes[this->cpu.GetProcessUsingCPU()].children.push_back(childPID);

    // add child to readyQueue
    this->cpu.AddToReadyQueue(childPID);
}

void SimOS::TimerInterrupt(){
    this->cpu.CPUTimerInterrupt();
}

void SimOS::DiskReadRequest( int diskNumber, std::string fileName ){

    // check if CPU is idle
    this->cpu.CPU_Idle_ErrorCheck();

    // current process using CPU requests to read file from Disk diskNumber
    this->disks.ReadFromDisk(this->cpu.GetProcessUsingCPU(),diskNumber,fileName);

    // track the disk the process will be using
    processes[this->cpu.GetProcessUsingCPU()].disk = diskNumber;
    
    // remove current process from CPU, 
    this->cpu.RemoveCurrentProcessFromCPU();

}

void SimOS::DiskJobCompleted( int diskNumber ){
    int servedProcessPID = this->GetDisk(diskNumber).PID;

    // Remove FileReadRequest obj associated with process from disk
    disks.RemoveProcessFromDisks(servedProcessPID,diskNumber);

    // update disk tracking for process that has been served
    processes[servedProcessPID].disk = -1; // process no longer using disk

    // move served process back to readyQueue, or CPU if CPU is idle
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
    return this->ram.GetMemory();
}



FileReadRequest SimOS::GetDisk(int diskNumber){
    return this->disks.GetDisk(diskNumber);
}

std::deque<FileReadRequest> SimOS::GetDiskQueue( int diskNumber ){
    return disks.GetDiskQueue(diskNumber);
}


void SimOS::SimExit(){
    this->cpu.CPU_Idle_ErrorCheck(); // if CPU idle throw error

    int process_to_exit_PID = this->cpu.GetProcessUsingCPU();
    bool parent_waiting = processes.at(GetParentPID(process_to_exit_PID)).waiting;


    // Check if parent of current process has called wait()
    if (parent_waiting){

        // terminate process immediately
        TerminateProcess(this->cpu.GetProcessUsingCPU());
        // change parent waiting state to false
        processes.at(GetParentPID(process_to_exit_PID)).waiting = false;
    }
    else{ // else if parent isn't waiting
        MakeZombie(processes.at(process_to_exit_PID)); // turn process into zombie
        // remove from cpu
    }

    // remove this process from CPU and don't put it in readyQueue
    // at this point if it's a zombie only it's PCB is left
    this->cpu.RemoveCurrentProcessFromCPU();
}

// TO DO
void SimOS::SimWait(){

    this->cpu.CPU_Idle_ErrorCheck(); // check if CPU idle, throw error if so

    // loop through children and check if any of them are zombies

    // get PID of process using CPU
    int pid_of_current_process = cpu.GetProcessUsingCPU();

    // if process has no children throw exception (it would wait forever)
    if (processes[pid_of_current_process].children.empty()){
        std::logic_error("Process has no children to wait for");
    }
    else{ // process has children

        // check if any of the children are zombies
        for (auto childPID : processes[pid_of_current_process].children){
            // if zombie exists
            if (processes[childPID].zombie){ // if child is a zombie
                // terminate zombie child (i.e., collect exit status)
                TerminateProcess(childPID);
                // continue execution (process keeps using CPU)
                return; 
            }
        }
        // if no zombies were found in loop
        // process pauses and waits
        processes[pid_of_current_process].waiting = true;
        // activate next process in readyQueue
        // temporarily leave waiting process out of readyQueue
        // it'll only return to readyQueue when it collects exit status from child
        this->cpu.RemoveCurrentProcessFromCPU();
    }
}

int SimOS::GetParentPID(int pid){

    return processes.at(pid).parent_pid;
}
       
void SimOS::TerminateProcess(int pid){

        // check if process has children
    if (!processes[pid].children.empty()){
        // terminate children recursively
        for (int childPID : processes[pid].children){
            TerminateProcess(childPID);
        }
    }

    // Remove this process from memory
    this->ram.RemoveProcessFromMemory(pid);

    // Remove this process from readyQueue
    this->cpu.RemoveProcessFromReadyQueue(pid);

    // Remove this process from Disks
    this->disks.RemoveProcessFromDisks(pid, processes[pid].disk);

    // Remove this process from diskQueue
    this->disks.RemoveProcessFromIOQueues(pid, processes[pid].disk);

    // remove pthis rocess from vector of processes
    processes.erase(pid);
}

void SimOS::TerminateChildren(int pid){
    // loop through children and call TerminateProcess on each
    for (auto child : processes.at(pid).children){
        TerminateProcess(child);
    }
}

void SimOS::MakeZombie(Process& p){
    // terminate all children of this process
    TerminateChildren(p.pid_);

    // Remove this process from memory
    this->ram.RemoveProcessFromMemory(p.pid_);

    // Remove this process from readyQueue
    this->cpu.RemoveProcessFromReadyQueue(p.pid_);

    // Remove this process from Disks
    this->disks.RemoveProcessFromDisks(p.pid_, processes[p.pid_].disk);

    // Remove this process from diskQueue
    this->disks.RemoveProcessFromIOQueues(p.pid_, processes[p.pid_].disk); // THIS LINE

    // keep process in process table but mark as a zombie
    p.zombie = true;
}