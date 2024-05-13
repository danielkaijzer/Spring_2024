/**
 * @file DiskManager.h
 * @author Daniel Kaijzer
 * @date 2024-05-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _DISKMANAGER_H
#define _DISKMANAGER_H

#include <iostream> 
#include <deque> // used for I/O-queue which is FIFO
#include <vector>

struct FileReadRequest
{
    int  PID{0};
    std::string fileName{""};
};

/**
 * @brief A disk class 
 * Contains info if disk is being used
 * and if so, the PID of process using it
 * and fileName of being requested to read
 * 
 */
struct Disk
{
    FileReadRequest usingDisk; // pid and file name of process using disk
    bool diskIdle{true}; // contains info if a disk is idle
};

class DiskManager{
    private:
        unsigned int numberOfDisks_;
        std::vector<std::deque<FileReadRequest>> ioQueues_; // I/O-Queue
        std::vector<Disk> disks_;

    public:
        DiskManager() = default;

        DiskManager(int numberOfDisks);

        /**
         * @brief read from disk
         * 
         * if Disk idle, add FileReadRequest info to Disk object
         * if Disk is in use, put FileReadRequest object in ioQueue associated with that Disk
         * 
         * @param current_process_PID 
         * @param diskNumber 
         * @param fileName 
         */
        void ReadFromDisk( int current_process_PID, int diskNumber, std::string fileName);


        void dequeFrontIOQueue( int diskNumber );

        /**
         * @brief Delete process from ioQueue
         * if found, delete
         * used in exit() (for terminating processes in cascading termination)
         * @param pid 
         * @param diskNumber 
         */
        void RemoveProcessFromIOQueues(int pid, int diskNumber);


        /**
         * @brief removes using a Disk
         * used for Exit() for terminating processes via cascading termination
         */
        void RemoveProcessFromDisks(int pid, int diskNumber);

        /**
         * @brief Using specified disk, return disk object using 
         * 
         * @param diskNumber 
         * @return FileReadRequest object using disk
         */
        FileReadRequest GetDisk(int diskNumber);

        std::deque<FileReadRequest> GetDiskQueue( int diskNumber );

        /**
         * @brief Check if disk exists
         * 
         * @param diskNumber 
         */
        void IfDiskExists(int diskNumber);
};

#endif