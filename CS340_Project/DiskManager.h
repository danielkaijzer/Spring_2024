#ifndef _DISKMANAGER_H
#define _DISKMANAGER_H

#include <iosfwd> // SimOS will include <iostream>
//#include <queue> // used for I/O-queue which is FIFO

struct FileReadRequest
{
    int  PID{0};
    std::string fileName{""};
};

class DiskManager{
    private:
        unsigned int numberOfDisks_;
        std::vector<std::deque<FileReadRequest>> ioQueues; // I/O-Queue

    public:
        DiskManager() = default;

        DiskManager(int numberOfDisks){
            this->numberOfDisks_ = numberOfDisks;
        }

        void dequeFrontIOQueue( int diskNumber ){
            if (!ioQueues[diskNumber].empty()){
                ioQueues[diskNumber].pop_front();
            }
            else{ // if IO queue is empty, there's no job to complete
                throw std::logic_error("Disk is not in use.");
            }
        }

        void ReadFromDisk( int current_process_PID, int diskNumber, std::string fileName){
            ifDiskExists(diskNumber);

            // add process to I/O queue
            FileReadRequest f; 
            f.PID = current_process_PID;
            f.fileName = fileName;

            ioQueues[diskNumber].push_back(f);
        }

        /**
         * @brief Delete process from ioQueue
         * if found, delete
         * @param pid 
         * @param diskNumber 
         */
        void removeProcessFromIOQueues(int pid, int diskNumber){
            ifDiskExists(diskNumber);

            if (diskNumber == -1){
                return; // if invalid disk number, you don't need to look
            }

            // search disk for process using FileReadRequest
            // iterate through ioQueue of specified disk and remove process if found
            for (auto itr = ioQueues[diskNumber].begin(); itr != ioQueues[diskNumber].end();){
                if (itr->PID == pid){ // if process found in ioQueue
                    itr = ioQueues[diskNumber].erase(itr); // returns next iterator
                    return; // no need to keep looking
                }
                else{ // if process not yet found, continue searching
                    ++itr;
                }
            }
        }

        /**
         * @brief Using specified disk, return object at front of ioQueue which is the process currently using disk
         * 
         * @param diskNumber 
         * @return FileReadRequest object
         */
        FileReadRequest GetDisk(int diskNumber){
            ifDiskExists(diskNumber);

            // if ioQueue isn't empty for disk, return process currently using disk (i.e., at front of queue)
            if(!ioQueues[diskNumber].empty()){
                return ioQueues[diskNumber].front();
            }

            // else if ioQueue is empty just return empty FileReadRequest object
            return FileReadRequest();
        }

        std::deque<FileReadRequest> GetDiskQueue( int diskNumber ){
            return ioQueues[diskNumber];
        }

        /**
         * @brief Check if disk exists
         * 
         * @param diskNumber 
         * @return true 
         * @return false 
         */
        bool ifDiskExists(int diskNumber){
            if (diskNumber > numberOfDisks_){
                throw std::out_of_range("Specified disk doesn't exist");
            }
        }
};

#endif