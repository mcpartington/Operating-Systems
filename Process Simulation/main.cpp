// Programmer's Names: Maxwell Partington and Mary Wakefield
// Date Written: 2-12-2014
// Course and Assignement Number: Cs 433 Operating Systems Hw 1
// Functionality Description: This is the main driver for the following files: Process.h Process.cpp ReadyQueue.h and ReadyQueue.cpp
//   this main driver has two main tasks. The first is to create a PCB table with 20 Processes of random priority values
//   ranging from 1-50. Then specfic Processes are added into the ReadyQueue, the highest Priority is deleted, the ReadyQueue is 
//   displayed, then a few more are added, again displays updated ReadyQueue. Then, all elements in the readyQueue are removed 
//   in order from highest priority to lowest. The second task is to test the effectiveness of this program. This part uses the 
//   PCB table and ReadyQueue from the first part. It selects 10 processes from the table, adds them into the ReadyQueue, they
//   are sorted then the following tasks are repeated 1000000 : the highest prioirty process is removed, the existing priority
//   values are decremented by one, then a random process from the PCBtable, which is not in the ReadyQueue is added. 
//   A timer then prints out the time it took to perform these tasks. Average Time: 1.51 seconds when used with -O2 flag
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;
#include "ReadyQueue.h"

int main()
{
  cout<<"Names: Mary Wakefield and Maxwell Partington"<<endl;
  int test1Size=20;

  Process *pcbTable[test1Size]; // create tcb Table array
  srand(time(NULL));  //used to check the computer clock each time the rand() function is called. essentially this makes sure 
  // that a new random number is generated whenever the time is different and function is called. 
   for( int i=0; i< test1Size; i++)// generate 20 Processes with ID 1-20 with random PV 1-50
    {
	int randomPriorityValue= rand() % 50 +1;// get random value 1-50
      Process *newItem = new Process ( i+1, randomPriorityValue);
      pcbTable[i]= newItem;// add to table
    }


  //print pcb table
 // cout<<"**********PCB TABLE**********"<<endl;

  ReadyQueue *q1 = new ReadyQueue(test1Size);
/*  for( int i=0; i< test1Size; i++)
   {
     q1 -> printProcessInfo (pcbTable[i]);
   }*/

  cout<<endl;
  

  // add the following Processes to the Ready Queue: 5, 1, 8, and 11- Note: -1 because arrays start at index 0, not 1 
  q1 -> insertProcessToReadyQueue( pcbTable[5-1]);
  q1 -> insertProcessToReadyQueue (pcbTable [ 1-1]);
  q1 ->insertProcessToReadyQueue (pcbTable [ 8-1]);
  q1 ->insertProcessToReadyQueue (pcbTable [ 11-1]);
  //display info
  cout<< "Size "<< q1 -> size() <<endl;
  q1 -> displayQueue();
  
  //remove highest priority then display again 
  /*Process *removedProcess =*/ q1 -> removeHighestProc();
  //removedProcess -> changeState("RUNNING");
  //q1 -> printProcessInfo(removedProcess);
  cout<< "Size "<< q1 -> size() <<endl;
  q1 -> displayQueue();

 //remove highest priority then display again 
  q1 ->removeHighestProc();  
  cout<< "Size "<< q1 -> size() <<endl;
  q1 -> displayQueue();
// add the following Process to the Ready Queue: 3, 7, 2, 12, 9
  q1 -> insertProcessToReadyQueue (pcbTable [ 3-1]);
  q1 -> insertProcessToReadyQueue (pcbTable [ 7-1]);
  q1 -> insertProcessToReadyQueue (pcbTable [ 2-1]);
  q1 -> insertProcessToReadyQueue (pcbTable [ 12-1]);
  q1 -> insertProcessToReadyQueue (pcbTable [ 9-1]);
  // display
  q1 -> displayQueue();
  
  //remove everything in the queue and print as you go
  while(  q1->size() != 0)
    {
      q1 ->removeHighestProc();
      
      cout<< "Size "<< q1 -> size() <<endl;
      q1 -> displayQueue();
    }

    /*
  cout<<"**********PCB TABLE**********"<<endl;
 
  for( int i=0; i< test1Size; i++)
    {
      q1 -> printProcessInfo (pcbTable[i]);
    }

  q1 -> printProcessInfo (pcbTable[0]);
  */

//=============================================  
// TEST 2

//choose 10 random Processes from the pcb table and add into Readyqueue
   for (int i = 0; i < 10; i++) 
	{
     	 q1 -> insertProcessToReadyQueue(pcbTable[rand() % 10 +1]);
	}

  //used to keep track of the time it took to run the following code portion
   clock_t start;//, end;   
   start = clock();
   //for a million iterations
   for (int mil = 0; mil < 1000000; mil++)
   {
    //remove highest Priority Process, decrement all remaining Priority values by 1, then select a random process from pcbtable 
    // that is not in the queue already
   q1 -> removeHighestProc(); 
   q1 -> decrement();
   int newProcessId;
   bool doesExist = true; //
   while(doesExist == true)
     {
       newProcessId = rand() % 19 +1;// random process id 1-20
       doesExist = q1-> searchForProcess(newProcessId); // returns false if it is not in the queue- AKA ok to add.
       // if true, then want to search for anther to add
     }
   if( !doesExist)// doesnt already exist in queue, so add it!
     q1->insertProcessToReadyQueue( pcbTable[ newProcessId ]);
 }
   q1 -> displayQueue();// display queue and print time took 
   cout << "Total time: " << (double(clock()-start)/double(CLOCKS_PER_SEC)) << "seconds" << endl;	
  
	return 0;
}
//=============================================================================

