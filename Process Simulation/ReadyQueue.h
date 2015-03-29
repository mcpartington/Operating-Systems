// Programmer's Names: Maxwell Partington and Mary Wakefield
// Date Written: 2-12-2014
// Course and Assignement Number: Cs 433 Operating Systems Hw 1
// Functionality Description: This creates a class of Type "ReadyQueue" which is an array of type Process. The purpose
//  is to add, remove, sort, print, decrement, and search for Processes in the ReadyQueue. It is implemented as an 
//  array min-heap. We choose min-heap data structure because it is very fast at sorting and searching through large lists. 
//  And we chose array over vector because arrays have less overhead, and this resulted in a quicker execution. 

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;
#include "Process.h"

class ReadyQueue// new class of Type ReadyQueue-implemented as a heap
{
private:
  Process *heapPointer;
  Process *newProcess;
  int numProcessInReadyQueue;

public:
  ReadyQueue (int heapSize);// constructor
  ~ReadyQueue();// default constructor

  //Process removeHighestProcess();// removes and returns the highest priority in the ReadyQueue
  int size ();// returns the size of the readyQueue
  void displayQueue();// displays all ids and Priority values of the Processes in the readyQueue
  void decrement(); // decrements all priority values in all the Processes in the readyQueue
  void reheapRemove(int root, int bottom);//Reheaps the ReadyQueue once an item is removed from the heap. 
  //root is the index of the current root and bottom is the root of the last leaf. 
  void reheapAdd(int root, int bottom);// Reheaps the ReadyQueue once an iten is added to the heap.
  bool insertProcessToReadyQueue( Process *winners);// inserts the passes Process to the ReadyQueue and calls 
  //reheapAdd to reheap the ReadyQueue
  //bool addProcess( int Id, int priorityValue);
  Process *removeHighestProc();// removes and returns the highest priority in the ReadyQueue
  void printProcessInfo(Process *newProcess);// Prints out the id and priority value from the passed parameter
  bool searchForProcess(int newProcessId);// searches for the passed Id in all the Processes in the ReadyQueue. 
  //returns true if it was found. 

 };



