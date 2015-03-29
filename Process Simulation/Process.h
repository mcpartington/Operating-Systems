// Programmer's Names: Maxwell Partington and Mary Wakefield
// Date Written: 2-12-2014
//Course and Assignement Number: Cs 433 Operating Systems Hw 1
//Functionality Description: This creates a class of Type Process that is essentially the "task" that one wants to execute. 
//  each Process has a unique id, and state (either NEW, READY, or RUNNING) which decribes the current state of execution of the 
//  task, and also has a Priority value (1-50 with 1 being highest priority). 
//   Various functions are written to perform simple tasks such as change state, or print info.

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;


class Process
{
public:
  int id;// unique id
  string state;//New default, READY when in queue, and RUNNING when out of queue
  int priorityValue;// num 1-50 with 1 being hightest priority

  Process();// default constructor
  Process(int currentId, int currentPriorityValue);//constructor 
  ~Process();// destructor
  void changeState(string newState);//change state of process
  void setState(string newState); //sets state 
  int getId( );//returns id of process
  string getState();//gets state of process
  int getPriorityValue();// gets priority value of process
  void printProcessInfo();// prints all info from process
};


