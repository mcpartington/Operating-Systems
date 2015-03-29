#include <string>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;
#include "Event.h"
#include "random.h"

const int totalTime = 300000;

int main( int argc, char const *argv[] )
{
	srand(time(NULL));
	bool isCpuIdle= true;
	int totalCpuTime=0;
	int totalWaitingTime = 0;
	bool processFinished = false;
	priority_queue <Event> eventQueue;
	//queue <Event> eventQueue;
	queue <Process> readyQueueFCFS;
	vector <Process> processUtilize;
	vector <PrintProcess> printProcessVector;
	
	cout<< "**** Maxwell Partington and Mary Wakefield ****" <<endl;

	if(argc == 2)// if there is the correct number of command line arguments
	{
		int numProcesses = atoi( argv[1] ); // command argument for number of processes 

		for(int i=0; i < numProcesses; i++)
		{// create process arrival events for each f
			Event *e = new Event(1);
			e-> procId = i;
			e-> eventTime= rand() % 300001; // random ms number bewteen 0-5 minutes
			eventQueue.push(*e);
		}

		cout<< "Process id\t | Arrival Time\t | Finish Time\t | Service Time\t | I/O Time\t | Turnaround Time\t | Waiting Time\t " <<endl;

		int currentTime =0;

		while( ( !eventQueue.empty() ) && (currentTime <= totalTime) ) // while there is still an event in the event queue
		{
			
			//cout << "type " <<eventQueue.top().type << " id: " << eventQueue.top().procId<< " eventTime: "<< (eventQueue.top().eventTime ) << endl;
			
			Event currentEvent = eventQueue.top();
			eventQueue.pop();
			currentTime = currentEvent.eventTime;
			int currentEventType= currentEvent.type;
			PrintProcess *pv1 = new PrintProcess();
			//now check to see what type the event is and perform right operations
			switch(currentEventType)
			{
				case 1: // process arrival type =1
					{	
						//first create the process that goes along with event
						//cout<< "Event with type 1- Process Arrival ";
						Process *p = new Process(currentEvent.procId);
						PrintProcess *pv = new PrintProcess();
						pv -> id = p -> id;

						p->startTime = currentEvent.eventTime;
						pv -> startTime = p -> startTime;

						//cout << "remaining cpu time : "<< p-> remainingCPU;
						//cout<< "----START TIME: " << p->startTime;
						p->nextBurst = CPUBurstRandom( p->averageCPUBurst );
						p->status = "Ready";
						readyQueueFCFS.push(*p); // put it into the ready queue
						printProcessVector.push_back(*pv);
						

						//now check to see if the CPU is idle. 
						//if the CPU is idle, then we want to pop the first process from the ready queue
						if(isCpuIdle)// it is idle
						{
							Process currentProcess = readyQueueFCFS.front();
							readyQueueFCFS.pop();
							currentProcess.status = "Running";
							if(currentProcess.remainingCPU < currentProcess.nextBurst )
								{currentProcess.nextBurst = currentProcess.remainingCPU;} //adjusts the remaining CPU time to handle timer expir
							isCpuIdle= false;// false because it is now working on the current process
							// create new event of type 2 for when it is done with burst time
							Event *eventType2 = new Event(2);
							eventType2->procId = currentProcess.id;
							eventType2-> eventTime = currentTime + currentProcess.nextBurst;
							eventQueue.push(*eventType2);
							processUtilize.push_back(currentProcess);
						}
						break;
					}
				
				case 2: 
					{//CPU burst completion 
						Process currentProcess = processUtilize.front();
						processUtilize.pop_back();
						isCpuIdle = true;
						totalCpuTime += currentProcess.nextBurst;
						currentProcess.remainingCPU -= currentProcess.nextBurst;
						//cout<< "Event with type 2- CPU burst completion ";
						//cout << "remaining cpu time : "<< currentProcess.remainingCPU;

						int index = pv1 -> findProcess(currentProcess.id, printProcessVector);
						printProcessVector[index].serviceTime += currentProcess.nextBurst;

						if (currentProcess.remainingCPU == 0)
						{
							currentProcess.status = "Terminated";
							processFinished = true;
							//currentProcess.finishTime = currentTime;
							printProcessVector[index].finishTime = currentTime;

						}
						else
						{	
							currentProcess.IOBurst = rand() % 71 + 30;
							Event *eventType3 = new Event(3);
							eventType3->procId = currentProcess.id;
							eventType3->eventTime = currentTime + currentProcess.IOBurst;
							eventQueue.push(*eventType3);
							processUtilize.push_back(currentProcess);
						}

						break;
					}
				
				case 3: // I/O completion
					{ 
						Process currentProcess = processUtilize.front();
						processUtilize.pop_back();
						currentProcess.nextBurst = CPUBurstRandom( currentProcess.averageCPUBurst );
						currentProcess.status = "Ready";
						readyQueueFCFS.push(currentProcess);


						int index = pv1 -> findProcess(currentProcess.id, printProcessVector);
						printProcessVector[index].IOtime = currentProcess.IOBurst;
						//printProcessVector[index].serviceTime += currentProcess.nextBurst;********************
						//cout << "Event with type 3- I/O completion ";
						//cout << "remaining cpu time : "<< currentProcess.remainingCPU;
						if(isCpuIdle)// it is idle
						{
							Process newProcess = readyQueueFCFS.front();
							readyQueueFCFS.pop();
							newProcess.status = "Running";
							if(newProcess.remainingCPU < newProcess.nextBurst )
								{newProcess.nextBurst = newProcess.remainingCPU;} //adjusts the remaining CPU time to handle timer expir
							isCpuIdle= false;// false because it is now working on the current process
							// create new event of type 2 for when it is done with burst time
							Event *eventType2 = new Event(2);
							eventType2->procId = newProcess.id;
							eventType2-> eventTime = currentTime + newProcess.nextBurst;
							eventQueue.push(*eventType2);
							processUtilize.push_back(newProcess);
						}

						break;
					}
				default: cout<<"Wrong case number"<<endl; break;
			}// end switch
		}// end while loop
		/*PrintProcess *pv1 = new PrintProcess();

		for( int j=0; j < printProcessVector.size(); j ++)
		{
			if( printProcessVector[j].id == 1)
				cout<<"waiting time1 : "<< printProcessVector[j].waitingTime <<endl;
		}

		int test =  pv1->findProcess(1, printProcessVector);
		printProcessVector[test].waitingTime = 13;

		//print vector with id 1
		//cout << test.waitingTime << endl;
		for( int x=0; x < printProcessVector.size(); x++)
		{
			if( printProcessVector[x].id == 1)
				cout<<"waiting time2 : " << printProcessVector[x].waitingTime<<endl;
		}*/

		for (int x = 0; x < printProcessVector.size(); x++)
		{
			cout << currentTime << endl;
			cout << printProcessVector[x].startTime << endl;
			cout << printProcessVector[x].serviceTime << endl;
			cout << printProcessVector[x].IOtime << endl;
			if (printProcessVector[x].finishTime == 0)
			{
				printProcessVector[x].waitingTime = ((currentTime - printProcessVector[x].startTime) - (printProcessVector[x].serviceTime + printProcessVector[x].IOtime));
				totalWaitingTime += printProcessVector[x].waitingTime;
			}
			else
			{
				printProcessVector[x].waitingTime = ((printProcessVector[x].finishTime - printProcessVector[x].startTime) - (printProcessVector[x].serviceTime + printProcessVector[x].IOtime));
				totalWaitingTime += printProcessVector[x].waitingTime;
				printProcessVector[x].turnaroundTime = (printProcessVector[x].finishTime - printProcessVector[x].startTime);
			}
			

			cout << printProcessVector[x].id << "\t\t\t"; 
			cout << printProcessVector[x].startTime * 0.001 << "\t\t"; 
			if (printProcessVector[x].finishTime != 0)
			{
				cout << printProcessVector[x].finishTime * 0.001 << "\t\t";
			}
			else
				cout << "Did not finish.";
			cout << printProcessVector[x].serviceTime * 0.001 << "\t\t";
			cout << printProcessVector[x].IOtime * 0.001;
			if (printProcessVector[x].finishTime > 0)
			{
				cout << "\t\t" << printProcessVector[x].turnaroundTime * 0.001;
			}
			else
			{
				cout << "Did not finish.";
			}
			cout << "\t\t" << printProcessVector[x].waitingTime * 0.001 << "\t" << endl;
		}
		cout << "CPU Utilization: " << ((double)totalCpuTime)	/((double)currentTime) * 100 << " %" << endl;
		cout << "Throughput: " << ((double)printProcessVector.size())/((double)currentTime)* 1000 << "jobs" << endl;
		/*for (int y = 0; y < printProcessVector.size(); y++)
		{
			totalWaitingTime += printProcessVector[y].waitingTime;
		}*/
		cout << "Average Waiting Time" << ((double)totalWaitingTime)/((double)printProcessVector.size()) / 1000 << "s" << endl;
	}// end if
	else
	{cout<<"!!Oh NO!! Not correct number of command line arguments!! "<<endl;}		
	return 0;
}// end main 
