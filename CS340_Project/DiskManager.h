#ifndef _DISKMANAGER_H
#define _DISKMANAGER_H

#include <iosfwd> // SimOS will include <iostream>
//#include <queue> // used for I/O-queue which is FIFO

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

        DiskManager(int numberOfDisks) : numberOfDisks_(numberOfDisks), ioQueues_(numberOfDisks), disks_(numberOfDisks) {}

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
        void ReadFromDisk( int current_process_PID, int diskNumber, std::string fileName){
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


        void dequeFrontIOQueue( int diskNumber ){
            if (!ioQueues_[diskNumber].empty()){
                ioQueues_[diskNumber].pop_front();
            }
            else{ // if IO queue is empty, there's no job to complete
                throw std::logic_error("ioQueue empty.");
            }
        }

        /**
         * @brief Delete process from ioQueue
         * if found, delete
         * used in exit() (for terminating processes in cascading termination)
         * @param pid 
         * @param diskNumber 
         */
        void RemoveProcessFromIOQueues(int pid, int diskNumber){
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


        /**
         * @brief removes using a Disk
         * used for Exit() for terminating processes via cascading termination
         */
        void RemoveProcessFromDisks(int pid, int diskNumber){

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

        /**
         * @brief Using specified disk, return disk object using 
         * 
         * @param diskNumber 
         * @return FileReadRequest object using disk
         */
        FileReadRequest GetDisk(int diskNumber){
            IfDiskExists(diskNumber);

            if (disks_[diskNumber].diskIdle){
                return FileReadRequest();
            }
            else // if disks isn't idle
            {
                return disks_[diskNumber].usingDisk;
            }
        }

        std::deque<FileReadRequest> GetDiskQueue( int diskNumber ){
            return ioQueues_[diskNumber];
        }

        /**
         * @brief Check if disk exists
         * 
         * @param diskNumber 
         */
        void IfDiskExists(int diskNumber){
            if (diskNumber > numberOfDisks_){
                throw std::out_of_range("Specified disk doesn't exist");
            }
        }
};

#endif