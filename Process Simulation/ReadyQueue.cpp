// Programmer's Names: Maxwell Partington and Mary Wakefield
// Date Written: 2-12-2014
// Course and Assignement Number: Cs 433 Operating Systems Hw 1
// Functionality Description: This is the implementation of the ReadyQueue functions as described in 
//   the ReadyQueue.h file. Again, ReadyQueue is implemented as an array min Heap. This means that one is allowed
//    to add a Process to the ReadyQueue, when it is added, a min heap will be made where all the Processes with the 
//    hightest priority values will remain at the top where the ones with the lower values will trinkle down the heap. 
//    Once a Process is removed or added, the ReadyQueue must "reheapify"- meaning it will re-sort everything.
//   Once a process is added to the ReadyQueue, its' state is changed to "READY" and when it is removed from the 
//   ReadyQueue, the process state is changed to "RUNNING". 
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;
#include "ReadyQueue.h"

int heapSize=20;

//=============================================================================
//Constructor
//=============================================================================
ReadyQueue::ReadyQueue(int heapSize)
{
  heapPointer= new Process[heapSize];
  int numProcessInReadyQueue=0;
  newProcess= new Process[heapSize];
}

//=============================================================================
//Destuctor
//=============================================================================
ReadyQueue::~ReadyQueue()
{
  delete[] heapPointer;
}

//=============================================================================
//Reheaps the ReadyQueue once an item is removed from the heap. 
//root is the index of the current root and bottom is the root of the last leaf. 
//=============================================================================
void ReadyQueue::reheapRemove( int root, int bottom)
{
  int minChild; // hold the index of the smallest child of the parent node
  int rightChild;
  int leftChild;
  Process temp;// temporary Process type used to swap parent and child accurately

  leftChild= root*2 +1;// index of left child is next level down (root*2) , on left(+1) 
  rightChild = root *2 +2;// index of the right child is next level down from parent (root*2), on right(+2)
  
  if( leftChild <= bottom)//if leftchild index is <= bottom index, then we re not finished 
    {

      //now must compare the leftChild and the rightChild to see which is smaller
      if( leftChild == bottom)//root has no right child- then left has to be minimum
	{minChild = leftChild;}
      else// there is a right and left child
	{
	  if(heapPointer[leftChild].getPriorityValue() >= heapPointer[rightChild].getPriorityValue() )// if the right child priority is smaller then the left 
	    { // then the min is the right
	      minChild= rightChild;
	    }
	  else // the left child is larger than the right
	    {
	      minChild = leftChild;
	    }
	}

      if(heapPointer[root].getPriorityValue() > heapPointer[minChild].getPriorityValue() )// if the root is larger than largest child, 
        //then need to swap because want smallest priority values on top. 
	{   
	  temp = heapPointer[root];// used to swap
	  heapPointer[root]=heapPointer[minChild];
	  heapPointer[minChild]= temp;
	  reheapRemove(minChild, bottom);// recursively call this function until all nodes are sorted
	}
    }
}
//=============================================================================
// Reheaps the ReadyQueue once an iten is added to the heap.
//root is the index of the current root and bottom is the root of the last leaf. 
//=============================================================================
void ReadyQueue::reheapAdd(int root, int bottom)
{
  int parent; // parent index
  Process temp;// temporary Process type used to swap 

  if(bottom > root)//if bottom index greater than root, not finished
    {
      parent = (bottom -1) /2 ;// get index of parent( meaning move over once (-1)and then up a row)(/2)
      if( heapPointer[parent].getPriorityValue() > heapPointer[bottom].getPriorityValue() )//if the parent is greater than the child, 
      {//want to switch- put lowest higher up
    
	     temp= heapPointer[parent];
	     heapPointer[parent]= heapPointer[bottom];// parent now is the bottom
	     heapPointer[bottom]=temp;// bottom is now the parent
	     reheapAdd(root, parent);//recursively call until everything is reheaped
	     }  
    }
  
}

//=============================================================================
// inserts the passes Process to the ReadyQueue and calls 
//reheapAdd to reheap the ReadyQueue
//=============================================================================
bool ReadyQueue::insertProcessToReadyQueue( Process *newProcess)
{
  if(numProcessInReadyQueue < heapSize) // if the readyQueue is not full
    {
      heapPointer[numProcessInReadyQueue] = *newProcess;// insert into ReadyQueue
      newProcess -> changeState("READY");// Change state of Process to Ready
      reheapAdd(0, numProcessInReadyQueue);// reheap ReadyQueue
      numProcessInReadyQueue++;// increment num in readyQueue
      return true;
    }
  else
    return false;
}

//=============================================================================
// Prints out the id and priority value from the passed parameter
//=============================================================================
void ReadyQueue::printProcessInfo( Process *newPointer)
{ 
  newPointer[0]=*newPointer;
  cout << "ID: " << newPointer->getId() << " Priority Value : "<< newPointer -> getPriorityValue() << endl;
}

//=============================================================================
//removes and returns the highest priority in the ReadyQueue
//=============================================================================
Process *ReadyQueue::removeHighestProc()//aka remove root
{
	heapPointer[0].changeState("RUNNING"); // changes the top Process state to Running 
 Process *temp = new Process(heapPointer[0].getId() , heapPointer[0].getPriorityValue());
 numProcessInReadyQueue --;// decrement because removing from Queue
  //move last leaf in heap to root
  heapPointer[0]= heapPointer[numProcessInReadyQueue];
  reheapRemove(0, numProcessInReadyQueue -1);//reheap ReadyQueue
  if(numProcessInReadyQueue == 0)// ReadyQueue is empty
    return NULL;
  else 
  {	
	  return temp;
  }
}

//=============================================================================
//returns the size of the readyQueue
//=============================================================================
int ReadyQueue::size()
{
  return numProcessInReadyQueue;
}

//=============================================================================
// displays all ids and Priority values of the Processes in the readyQueue
//=============================================================================
void ReadyQueue:: displayQueue()
{
  cout<<"__________________________________"<<endl;
  for( int i=0; i< numProcessInReadyQueue; i++)
    {
      cout<< "ID: " << heapPointer[i].getId() << " Priority Value: " << heapPointer[i].getPriorityValue() << endl;
    }
  cout<<endl;
}
//=============================================================================
// decrements all priority values in all the Processes in the readyQueue
//=============================================================================
void ReadyQueue::decrement()
{
	for (int i = 0; i < numProcessInReadyQueue; i++)// for each Process in ReadyQueue, decrement Priority Value
	{
		heapPointer[i].priorityValue -= 1;
	}
}
//=============================================================================
// searches for the passed Id in all the Processes in the ReadyQueue. 
//returns true if it was found, otherwise returns false.
//=============================================================================
bool ReadyQueue::searchForProcess(int newProcessId)
{
	
	for(int i = 0; i < numProcessInReadyQueue; i++)
	{
	  if( heapPointer[i].id == newProcessId)//add
	    return true;
	}
	return false; 
}
