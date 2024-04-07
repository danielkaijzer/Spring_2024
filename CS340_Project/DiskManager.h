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
        std::queue<FileReadRequest> ioQueue; // I/O-Queue


};

#endif