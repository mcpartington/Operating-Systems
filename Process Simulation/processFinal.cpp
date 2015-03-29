//=============================================================================
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

int heapSize=20;

class Process
{
public:
  int id;
  string state;
  int priorityValue;

  Process();
  Process(int currentId, int currentPriorityValue);//constructor 
  ~Process();
  void changeState(string newState);
  void setState(string newState); 
  int getId( );
  string getState();
  int getPriorityValue();
  void printProcessInfo();
};

Process::Process()
{
  id=0;
  priorityValue=0;
  state= "";
}

Process::Process(int currentId, int currentPriorityValue)
{
  id= currentId;
  priorityValue=currentPriorityValue;
  state= "NEW";
}

Process::~Process()
{}

void Process:: printProcessInfo()
{
  cout<<"ID: " << id << " Priority Value: "<< priorityValue<<endl;
}
void Process:: setState( string newState)
{
  state=newState;
}

int Process::getId( )
{
  return id;
}

string Process:: getState()
{
  return state;
}

int Process:: getPriorityValue()
{
  return priorityValue;
}

void Process::changeState(string newState)
{
  state=newState;
}

class ReadyQueue// implemented as a heap
{
private:
  Process *heapPointer;
  Process *newProcess;
  int numProcessInReadyQueue;

public:
  ReadyQueue (int heapSize);
  ~ReadyQueue();

  Process removeHighestProcess();
  int size ();
  void displayQueue();
  void decrement();
  void reheapRemove(int root, int bottom);//used to reheap after removing an item
  void reheapAdd(int root, int bottom);
  bool insertProcessToReadyQueue( Process *winners);
  bool addProcess( int Id, int priorityValue);
  Process *removeHighestProc();
  void printProcessInfo(Process *newProcess);
  bool searchForProcess(int newProcessId);

 };

ReadyQueue::ReadyQueue(int heapSize)
{
  heapPointer= new Process[heapSize];
  int numProcessInReadyQueue=0;
  newProcess= new Process[heapSize];
}

ReadyQueue::~ReadyQueue()
{
  delete[] heapPointer;
}

//=============================================================================
//this function will reheap the heap once you remove the root of the heap. 
//=============================================================================
void ReadyQueue::reheapRemove( int root, int bottom)
{
  int minChild; 
  int rightChild;
  int leftChild;
  Process temp;

  leftChild= root*2 +1;
  rightChild = root *2 +2;
  
  if( leftChild <= bottom)//if leftchild index is <= bottom index, then we re not finished 
    {

      //now must compare the leftChild and the rightChild to see which is larger
      if( leftChild == bottom)//root has no right child- then left has to be max
	{minChild = leftChild;}
      else// there is a right and left child
	{
	  if(heapPointer[leftChild].getPriorityValue() >= heapPointer[rightChild].getPriorityValue() )// if the right child priority is larger then the left 
	    {
	      minChild= rightChild;
	    }
	  else // the left child is larger than the right
	    {
	      minChild = leftChild;
	    }
	}

      if(heapPointer[root].getPriorityValue() > heapPointer[minChild].getPriorityValue() )// if the root is larger than largest child, then need to swap
	{
	  temp = heapPointer[root];
	  heapPointer[root]=heapPointer[minChild];
	  heapPointer[minChild]= temp;
	  reheapRemove(minChild, bottom);
	}
    }
}
//=============================================================================

//=============================================================================
//=============================================================================
void ReadyQueue::reheapAdd(int root, int bottom)
{
  int parent;
  Process temp;

  if(bottom > root)//if bottom index greater than root, not finished
    {
      parent = (bottom -1) /2 ;// get index of parent
      if( heapPointer[parent].getPriorityValue() > heapPointer[bottom].getPriorityValue() )//if the parent is greater than the child, want to switch- put lowest higher up
	{
	  temp= heapPointer[parent];
	  heapPointer[parent]= heapPointer[bottom];// parent now is the bottom
	  heapPointer[bottom]=temp;// bottom is now the parent
	  reheapAdd(root, parent);//recursively call until everything is reheaped
	}
    }
}
//=============================================================================


//=============================================================================
//this function acutally adds the process to the heap
//=============================================================================
bool ReadyQueue::insertProcessToReadyQueue( Process *newProcess)
{
  if(numProcessInReadyQueue < heapSize)
    {
      heapPointer[numProcessInReadyQueue] = *newProcess;
      newProcess -> changeState("READY");
      reheapAdd(0, numProcessInReadyQueue);
      numProcessInReadyQueue++;
      return true;
    }
  else
    return false;
}
//=============================================================================


//=============================================================================
//=============================================================================
void ReadyQueue::printProcessInfo( Process *newPointer)
{ 
  newPointer[0]=*newPointer;
  cout << "ID: " << newPointer->getId() << " Priority Value : "<< newPointer -> getPriorityValue() << endl;
}
//=============================================================================



//=============================================================================
//=============================================================================
Process *ReadyQueue::removeHighestProc()//aka remove root
{
	heapPointer[0].changeState("RUNNING"); 
 Process *temp = new Process(heapPointer[0].getId() , heapPointer[0].getPriorityValue());
 numProcessInReadyQueue --;
  //move last leaf in heap to root
  heapPointer[0]= heapPointer[numProcessInReadyQueue];
  reheapRemove(0, numProcessInReadyQueue -1);
  if(numProcessInReadyQueue == 0)
    return NULL;
  else 
  {	
	  return temp;
  }
}
//=============================================================================

//=============================================================================
//=============================================================================
int ReadyQueue::size()
{
  return numProcessInReadyQueue;
}

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

void ReadyQueue::decrement()
{
	for (int i = 0; i < numProcessInReadyQueue; i++)
	{
		heapPointer[i].priorityValue -= 1;
	}
}

bool ReadyQueue::searchForProcess(int newProcessId)
{
	
	for(int i = 0; i < numProcessInReadyQueue; i++)
	{
	  if( heapPointer[i].id == newProcessId)//add
	    return true;
	}
	return false; 
}
//=============================================================================
//=============================================================================
int main()
{
  cout<<"Names: Mary Wakefield and Maxwell Partington"<<endl;
  int test1Size=20;

  Process *pcbTable[test1Size];
  srand(time(NULL));  
   for( int i=0; i< test1Size; i++)
    {
	int randomPriorityValue= rand() % 50 +1;// get random value 1-50
      Process *newItem = new Process ( i+1, randomPriorityValue);
      pcbTable[i]= newItem;
    }


  //print pcb table
  cout<<"**********PCB TABLE**********"<<endl;

  ReadyQueue *q1 = new ReadyQueue(test1Size);
  for( int i=0; i< test1Size; i++)
   {
     q1 -> printProcessInfo (pcbTable[i]);
   }
  cout<<endl;
  q1 -> insertProcessToReadyQueue( pcbTable[5-1]);// process 5 is in index 4 because array starts at index 0.
  q1 -> insertProcessToReadyQueue (pcbTable [ 1-1]);
  q1 ->insertProcessToReadyQueue (pcbTable [ 8-1]);
  q1 ->insertProcessToReadyQueue (pcbTable [ 11-1]);
  cout<< "Size "<< q1 -> size() <<endl;
  q1 -> displayQueue();
  
  /*Process *removedProcess =*/ q1 -> removeHighestProc();
  //removedProcess -> changeState("RUNNING");
  //q1 -> printProcessInfo(removedProcess);
  cout<< "Size "<< q1 -> size() <<endl;
  q1 -> displayQueue();

  q1 ->removeHighestProc();  
  cout<< "Size "<< q1 -> size() <<endl;
  q1 -> displayQueue();

  q1 -> insertProcessToReadyQueue (pcbTable [ 3-1]);
  q1 -> insertProcessToReadyQueue (pcbTable [ 7-1]);
  q1 -> insertProcessToReadyQueue (pcbTable [ 2-1]);
  q1 -> insertProcessToReadyQueue (pcbTable [ 12-1]);
  q1 -> insertProcessToReadyQueue (pcbTable [ 9-1]);
  q1 -> displayQueue();
  while(  q1->size() != 0)
    {
      q1 ->removeHighestProc();
      
      cout<< "Size "<< q1 -> size() <<endl;
      q1 -> displayQueue();
    }
  cout<<"**********PCB TABLE**********"<<endl;
 
  for( int i=0; i< test1Size; i++)
    {
      q1 -> printProcessInfo (pcbTable[i]);
    }

  q1 -> printProcessInfo (pcbTable[0]);
  

//=============================================  
// TEST 2

   for (int i = 0; i < 10; i++)
	{
     	 q1 -> insertProcessToReadyQueue(pcbTable[rand() % 10 +1]);
	}
   clock_t start;//, end;   
   start = clock();
   for (int mil = 0; mil < 1000000; mil++)
   {
   q1 -> removeHighestProc(); 
   q1 -> decrement();
   int newProcessId;
   bool doesExist = true; 
   while(doesExist == true)
     {
       newProcessId = rand() % 19 +1;
       doesExist = q1-> searchForProcess(newProcessId);
     }
   if( !doesExist)
     q1->insertProcessToReadyQueue( pcbTable[ newProcessId ]);
 }
   q1 -> displayQueue();
   cout << "Total time: " << (double(clock()-start)/double(CLOCKS_PER_SEC)) << "seconds" << endl;	
  
	return 0;
}
//=============================================================================

