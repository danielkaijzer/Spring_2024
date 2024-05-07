#ifndef _DISKMANAGER_H
#define _DISKMANAGER_H

#include <iosfwd> // SimOS will include <iostream>
#include <queue> // used for I/O-queue which is FIFO

struct FileReadRequest
{
    int  PID{0};
    std::string fileName{""};
};

class DiskManager{
    private:
        unsigned int numberOfDisks_;
        std::queue<FileReadRequest> ioQueue; // I/O-Queue

    public:
        DiskManager() = default;

        DiskManager(int numberOfDisks){
            this->numberOfDisks_ = numberOfDisks;
        }

        void addToIOQueue(int pid, std::string fileName){
            FileReadRequest f; 
            f.PID = pid;
            f.fileName = fileName;

            ioQueue.push(f);
        }

        void ReadFromDisk( int current_process_PID, int diskNumber, std::string fileName){
            if (diskNumber > numberOfDisks_){
                throw std::out_of_range("Specified disk doesn't exist");
            }

            // add process to I/O queue
            addToIOQueue(current_process_PID, fileName);
        }
};

#endif