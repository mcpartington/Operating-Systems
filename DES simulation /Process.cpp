#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector> 
using namespace std;
#include "Process.h"



Process:: Process(int newId)
{
	//srand(time(NULL) );
	id = newId;
	startTime = 0;
	totalCPU = rand() %59001 + 1000; //1 second to 1 minute in ms 
	remainingCPU = totalCPU;
	averageCPUBurst = rand() % 96 + 5; //random 5 ms to 100 ms
	nextBurst = 0;
	IOBurst = 0;//initialized at completion of CPU burst
	priority= rand() %100 + 1;// priority value 1 -100
	status = "New";
}

Process:: ~Process()
{

}

PrintProcess:: PrintProcess()
{
	id = 0;
	startTime = 0;
	finishTime = 0;
	serviceTime = 0;
	IOtime = 0;
	turnaroundTime = 0;
	waitingTime = 0;
}

PrintProcess:: ~PrintProcess()
{

}

int PrintProcess:: findProcess(int processID, vector<PrintProcess>& infoVec)
{
	for (int i = 0; i < infoVec.size(); i++)
	{
		if(infoVec[i].id == processID)
			return i;
	}
}
