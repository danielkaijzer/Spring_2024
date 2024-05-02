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
        unsigned int numberOfDisk_;
        std::queue<FileReadRequest> ioQueue; // I/O-Queue

    public:
        DiskManager() = default;

        DiskManager(int numberOfDisks){
            this->numberOfDisk_ = numberOfDisks;
        }
};

#endif