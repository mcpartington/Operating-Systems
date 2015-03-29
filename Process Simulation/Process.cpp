// Programmer's Names: Maxwell Partington and Mary Wakefield
// Date Written: 2-12-2014
//Course and Assignement Number: Cs 433 Operating Systems Hw 1
//Functionality Description: This implements the functions from the class of Type Process which are used to manage
// and update the processes. 


#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;
#include "Process.h"

//__________________________________________________________________
Process::Process()//default constructor 
{
  id=0;
  priorityValue=0;
  state= "";
}
//__________________________________________________________________
Process::Process(int currentId, int currentPriorityValue)// constuctor
{
  id= currentId;
  priorityValue=currentPriorityValue;
  state= "NEW";
}
//__________________________________________________________________
Process::~Process()// destructor
{}

//__________________________________________________________________
//Prints id and priority value information from the process. 
//__________________________________________________________________
void Process:: printProcessInfo()
{
  cout<<"ID: " << id << " Priority Value: "<< priorityValue<<endl;
}
void Process:: setState( string newState)
{
  state=newState;
}

//__________________________________________________________________
// returns the unique id number of the process
//__________________________________________________________________
int Process::getId( )
{
  return id;
}

//__________________________________________________________________
// sets the state of the process
//__________________________________________________________________
string Process:: getState()
{
  return state;
}

//__________________________________________________________________
// returns the priority value of the process
//__________________________________________________________________
int Process:: getPriorityValue()
{
  return priorityValue;
}

//__________________________________________________________________
// changes the state of the process to the newString that was passed
//__________________________________________________________________
void Process::changeState(string newState)
{
  state=newState;
}
