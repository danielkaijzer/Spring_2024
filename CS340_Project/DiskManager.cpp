/**
 * @file DiskManager.cpp
 * @author Daniel Kaijzer
 * @date 2024-05-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "DiskManager.h"

DiskManager::DiskManager(int numberOfDisks) : numberOfDisks_(numberOfDisks), ioQueues_(numberOfDisks), disks_(numberOfDisks) {}

void DiskManager::ReadFromDisk( int current_process_PID, int diskNumber, std::string fileName){
    IfDiskExists(diskNumber); // check if disk exists

    FileReadRequest f; 
    f.PID = current_process_PID;
    f.fileName = fileName;

    // check if disk is idle
    if (disks_[diskNumber].diskIdle){
        // if disk idle, then start file read request at disk
        disks_[diskNumber].usingDisk = f;
        disks_[diskNumber].diskIdle = false;
    }
    else // if disk is in use add process to I/O queue
    { 
        ioQueues_[diskNumber].push_back(f);
    }
}


void DiskManager::dequeFrontIOQueue( int diskNumber ){
    if (!ioQueues_[diskNumber].empty()){
        ioQueues_[diskNumber].pop_front();
    }
    else{ // if IO queue is empty, there's no job to complete
        throw std::logic_error("ioQueue empty.");
    }
}

void DiskManager::RemoveProcessFromIOQueues(int pid, int diskNumber){
    if (diskNumber == -1){
        return; // if invalid disk number, you don't need to look
    }

    // search disk for process using FileReadRequest
    // iterate through ioQueue of specified disk and remove process if found
    for (auto itr = ioQueues_[diskNumber].begin(); itr != ioQueues_[diskNumber].end();){
        if (itr->PID == pid){ // if process found in ioQueue
            ioQueues_[diskNumber].erase(itr); // erase FileReadRequest obj associated with process from ioQueue

            return; // no need to keep looking
        }
        else{ // if process not yet found, continue searching
            ++itr;
        }
    }
}

void DiskManager::RemoveProcessFromDisks(int pid, int diskNumber){

    // if Disk idle throw exception
    if (disks_[diskNumber].diskIdle){
        throw std::logic_error("Disk is not in use.");
    }

    // if process is indeed using this disk, remove it
    if (disks_[diskNumber].usingDisk.PID == pid){
        // default FileReadRequest obj 
        FileReadRequest emptyf;

        // else remove FileReadRequest obj associated with processfrom ioQueue
        disks_[diskNumber].usingDisk = emptyf;
        disks_[diskNumber].diskIdle = true;
    }
}


FileReadRequest DiskManager::GetDisk(int diskNumber){
    IfDiskExists(diskNumber);

    if (disks_[diskNumber].diskIdle){
        return FileReadRequest();
    }
    else // if disks isn't idle
    {
        return disks_[diskNumber].usingDisk;
    }
}

std::deque<FileReadRequest> DiskManager::GetDiskQueue( int diskNumber ){
    IfDiskExists(diskNumber);

    return ioQueues_[diskNumber];
}


void DiskManager::IfDiskExists(int diskNumber){
    if (diskNumber > numberOfDisks_ || diskNumber < 0){
        throw std::out_of_range("Specified disk doesn't exist");
    }
}