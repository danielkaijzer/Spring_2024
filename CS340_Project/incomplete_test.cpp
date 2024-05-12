#include"SimOS.h"
// #include<deque>

int main()
{
	SimOS sim{ 3, 1000, 10 };
	bool allTestsClean{ true };

	if (sim.GetCPU() != NO_PROCESS)
	{
		allTestsClean = false;
		std::cout << "Test on the line 12 fails!" << std::endl;
	}
	else{
		std::cout << "CPU not used yet since there aren't any processes yet" << std::endl;
	}

	sim.NewProcess(); // creates a single process that will use CPU
	if (sim.GetCPU() != 1)
	{
		allTestsClean = false;
		std::cout << "Test on the line 16 fails!" << std::endl;
	}else{
		std::cout << "Single process created and now using CPU" << std::endl;
	}

	sim.DiskReadRequest(0, "file1.txt"); // Process will stop using CPU
	if (sim.GetCPU() != NO_PROCESS)
	{
		allTestsClean = false;
		std::cout << "Test on the line 23 fails!" << std::endl;
	}
	else{
		std::cout << "Process no longer using CPU because file read was requested" << std::endl;
	}

	// FIX!!!
	FileReadRequest request{ sim.GetDisk(0) }; // Read from logical disk 0
	if (request.PID != 1 || request.fileName != "file1.txt")
	{
		allTestsClean = false;
		std::cout << "Test on the line 30 fails!" << std::endl;
	}
	else{
		std::cout << "Successfully checked that request PID is 1 and filename is file1.txt" << std::endl;
	}


	// FIX!!!
	std::deque<FileReadRequest> ioQueue0{ sim.GetDiskQueue(0) };
	if (ioQueue0.size() != 0)
	{
		allTestsClean = false;
		std::cout << "Test on the line 37 fails! You should change code so that when process is reading it is NOT in ioQueue" << std::endl; // FIX !!!
	}
	else{
		std::cout << "ioQueue is currently empty" << std::endl;
	}

	sim.DiskJobCompleted(0);
	request = sim.GetDisk(0);
	if (request.PID != NO_PROCESS || request.fileName != "")
	{
		allTestsClean = false;
		std::cout << "Test on the line 45 fails!" << std::endl;
	}
	else{
		std::cout << "Disk Job Successfully Completed." << std::endl;
	}

	if (sim.GetCPU() != 1)
	{
		allTestsClean = false;
		std::cout << "Test on the line 51 fails!" << std::endl;
	}
	else{
		std::cout << "Process is back to using CPU." << std::endl;
	}

	std::deque<int> readyQueue{ sim.GetReadyQueue() };
	if (readyQueue.size() != 0)
	{
		allTestsClean = false;
		std::cout << "Test on the line 58 fails!" << std::endl;
	}
	else{
		std::cout << "ReadyQueue is empty." << std::endl;
	}

	sim.SimFork();
	readyQueue = sim.GetReadyQueue();
	if (readyQueue[0] != 2)
	{
		allTestsClean = false;
		std::cout << "Test on the line 66 fails!" << std::endl;
	}
	else{
		std::cout << "Child process is created. We call it process 2. \nWe successfully checked that process 2 is at front of readyQueue" 
		<< std::endl;
	}

	sim.TimerInterrupt();
	readyQueue = sim.GetReadyQueue();
	if (sim.GetCPU() != 2 || readyQueue[0] != 1)
	{
		allTestsClean = false;
		std::cout << "Test on the line 74 fails!" << std::endl;
	}
	else{
		std::cout << "Removed process 1 from CPU. Process 2 is now using CPU and Process 1 is at front of readyQueue" 
		<< std::endl;
	}

	// NEEDS WORK!!!
	sim.SimExit();


	readyQueue = sim.GetReadyQueue();
	if (sim.GetCPU() != 1 || readyQueue.size() != 0)
	{
		allTestsClean = false;
		std::cout << "Test on the line 82 fails!" << std::endl;
	}
	else{
		std::cout << "Called Exit() on Proces 2. Process 1 is using CPU again." 
		<< std::endl;
	}

// 	sim.AccessMemoryAddress(140);
// 	MemoryUsage ram{ sim.GetMemory() };
// 	if (ram[0].pageNumber != 14 || ram[0].PID != 1)
// 	{
// 		allTestsClean = false;
// 		std::cout << "Test on the line 90 fails!" << std::endl;
// 	}

// 	sim.SimWait();
// 	if (sim.GetCPU() != 1)
// 	{
// 		allTestsClean = false;
// 		std::cout << "Test on the line 97 fails!" << std::endl;
// 	}

// 	sim.SimExit();
// 	ram = sim.GetMemory();
// 	if (sim.GetCPU() != NO_PROCESS || ram.size() != 0)
// 	{
// 		allTestsClean = false;
// 		std::cout << "Test on the line 105 fails!" << std::endl;
// 	}

// 	if (allTestsClean)
// 		std::cout << "These preliminary tests are passed" << std::endl;

	return 0;
}