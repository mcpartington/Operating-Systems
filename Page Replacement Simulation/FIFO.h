//=============================================================================
// AUTHORS: Maxwell Partington, Mary Wakefield
// CLASS:   CS 433
// ASSIGN:  5
// DATE:    5/7/14
//
// PURPOSE: Contains the information to run the FIFO page replacement algorithm.
//  This file has the runFIFO function and the printFIFO function. 
//=============================================================================
#include <vector>
#include <iostream>
#include <fstream>
#include <istream>
#include <ctime>

#include "structures.h"

int FIFO_faults = 0;
int FIFO_memoryReferences = 0;
int FIFO_flushes = 0;
int start_s = 0;
int stop_s = 0;

//function prototypes
void printFIFO();

//=============================================================================
// PURPOSE: Perform the FIFO page replacement algorithm.
// DESC:  This reads in reference addresses from the text file, checks to see if it
//      is even (read) or write (odd). In the case of even, it is marked valid. 
//      In the case of odd, it is marked dirty. It then calculates the page number
//      by dividing the reference by the page size the user entered. 
//      From there, the remainder of the algorithm is performed. 
//          checks to see if the pagenum is in the main memory
//          if it isnt, then it checks to see if the main memory is full
//          if the main memory is not full, it just adds the page to the back 
//          if the main memory is full, it must find a victim page number 
//          in the main memory to replace. the victim page number is the first in 
//          page in the main memory.   
//=============================================================================
void runFIFO(int pageSize, int memory, int average)
{	
	start_s=clock();//start the time 

	vector <page> FIFO_MainMemory(pageSize); // vector of size user entered

	int reference;// input from the text file
	int pageNum; // holds value of calculated page numeber value
	bool inMemory;//true if page num is in memory

    ifstream myfile ("references.txt"); 
    int j = 0;

    // For each reference:
    // - find out its page number
    // - whether or not it is in memory (which memory? the data table or the frame queue?)
    // - if the ref is a write: (reference % 2) != 0), dirty_bit == dirty
    // - if it is not in mem, page_fault++, page is loaded into mem
    // - if mem is full, remove a page and new page is loaded in 

    //Open file 
  	if (myfile.is_open())
  	{
  		// While there are still numbers in the file
    	while (myfile >> reference) 
    	{
    		++j;
            ++FIFO_memoryReferences;
    		pageNum = reference/pageSize;
     		page newPage = page(); // create a new page object
     		newPage.refPageNum = pageNum; //update the pagenum of object

    		if (reference % 2 == 0) // if reference is even, then it is a read access- make valid
    		{	
     			newPage.valid_bit = 1;
    		}
    		if ((reference % 2) != 0) // if reference is odd, then it is a write access- make it dirty
     		{
     			newPage.dirty_bit = 1;
     			inMemory = isInMemory(newPage.refPageNum, FIFO_MainMemory);// returns true if pageNum is already in main memory

     			if ((!inMemory) && (FIFO_MainMemory.size() > numElementsInMainMem(FIFO_MainMemory)  )) // not in main and space in main available
     			{	
     				FIFO_MainMemory[numElementsInMainMem(FIFO_MainMemory) ] = newPage; //.push_back(newPage); // push to back and increase num of faults
     				FIFO_faults++;
                    ++FIFO_memoryReferences;
     			}

     			else if ((!inMemory) && (FIFO_MainMemory.size() == numElementsInMainMem(FIFO_MainMemory) )) // not in main and no space in main, pick a victim and remove
     			{// for FIFO, victim is the last in which was the front of the vector. 
     				if (FIFO_MainMemory.begin() -> dirty_bit == 1)
     				{
     					FIFO_flushes++;
     				}

     				FIFO_MainMemory.erase(FIFO_MainMemory.begin()); // erase vicitm page num
     				FIFO_MainMemory.push_back(newPage); // add new pagenum
     				FIFO_faults++;
                    ++FIFO_memoryReferences;
     			}
     		}
    	}//end while
		stop_s=clock(); //end clock
		printFIFO();
	}
  	else  
  	{
  		cout << "Unable to open file.";
  		return;
  	}
}//end runFIFO
//=============================================================================

//=============================================================================
// PURPOSE: Prints the statistics corresponding for the FIFO algorithm.  
//=============================================================================
void printFIFO()
{
	cout << "\n====================================================" << endl;
	cout << "\t\t FIFO Results" << endl;
	cout << "====================================================" << endl;
	cout << "Number of FIFO page faults: " << FIFO_faults << endl;
	cout << "Number of Memory References: " << FIFO_memoryReferences << endl;
	cout << "Number of FIFO Flushes: " << FIFO_flushes << endl;
	cout << "Time of simulation: " << ((stop_s-start_s)/(double(CLOCKS_PER_SEC))) << endl;
	cout << "====================================================" << endl;
}//end printFIFO
//=============================================================================


