//=============================================================================
// AUTHORS: Maxwell Partington, Mary Wakefield
// CLASS:   CS 433
// ASSIGN:  5
// DATE:    5/7/14
//
// PURPOSE: Contains the information to run the RANDOM page replacement algorithm.
//  This file has the runRANDOM function and the printRANDOM function. 
//=============================================================================
#include <vector>
#include <iostream>
#include <fstream>
#include <istream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "structures.h"

int RANDOM_faults;
int RANDOM_memoryReferences;
int RANDOM_flushes;
int start_r = 0;
int stop_r= 0;

//function prototypes
void printRANDOM();

//=============================================================================
// PURPOSE: Perform the random page replacement algorithm.
// DESC:  This reads in reference addresses from the text file, checks to see if it
//      is even (read) or write (odd). In the case of even, it is marked valid. 
//      In the case of odd, it is marked dirty. It then calculates the page number
//      by dividing the reference by the page size the user entered. 
//      From there, the remainder of the algorithm is performed. 
//          checks to see if the pagenum is in the main memory
//          if it isnt, then it checks to see if the main memory is full
//          if the main memory is not full, it just adds the page to the back 
//          if the main memory is full, it must find a victim page number 
//          in the main memory to replace. the victim page number is a random 
//			page number in main memory. 
//=============================================================================
void runRANDOM(int pageSize, int memory, int average)
{
	srand(time(NULL));// used to ensure a random number each time in the for loop below
	start_r=clock();// start the clock
	vector <page> RANDOM_MainMemory(pageSize);

	int reference;
	int pageNum;
	bool inMemory;
    ifstream myfile ("references.txt");
    int j = 0;
    int victim_index =-1;

    // For each reference:
    // - find out its page number
    // - whether or not it is in memory (which memory? the data table or the frame queue?)
    // - if the ref is a write: (reference % 2) != 0), dirty_bit == dirty
    // - if it is not in mem, page_fault++, page is loaded into mem
    // - if mem is full, remove a page and new page is loaded in 


  	if (myfile.is_open())
  	{
  		// While there are still numbers in the file
    	while (myfile >> reference) 
    	{
    		
    		++RANDOM_memoryReferences;
    		j++;
    		pageNum = reference/pageSize;
     		page newPage = page(); // create a new page object
     		newPage.refPageNum = pageNum; 

    		if (reference % 2 == 0) // if reference is even, then it is a read access- make valid
    		{	
     			newPage.valid_bit = 1;
    		}
    		if ((reference % 2) != 0) // if reference is odd, then it is a write access- make it dirty
     		{
     			newPage.dirty_bit = 1;
     			inMemory = isInMemory(newPage.refPageNum, RANDOM_MainMemory);// returns true if pageNum is already in main memory

     			if( inMemory)
     			{
     				// The reference page is already in main mem, do nothing. 
     			}
     			else if ((!inMemory) && (RANDOM_MainMemory.size() > numElementsInMainMem(RANDOM_MainMemory)  )) // not in main and space in main available
     			{	
     				RANDOM_MainMemory[ numElementsInMainMem(RANDOM_MainMemory) ] = newPage; // push and increase num of faults
     				++RANDOM_memoryReferences;
     				RANDOM_faults++;
     			}

     			else if ((!inMemory) && (RANDOM_MainMemory.size() == numElementsInMainMem(RANDOM_MainMemory) )) // not in main and no space in main, pick a victim and remove
     			{// acquire a random page in the main memory to be the victim
     
     				victim_index = rand() % RANDOM_MainMemory.size(); // random number for the victim index

     				if(RANDOM_MainMemory[victim_index].dirty_bit == 1)
     				{
     					RANDOM_flushes++;
     				}

					RANDOM_MainMemory[victim_index] = newPage ; // now remove the victim pageNum and replace with new page num
     				++RANDOM_memoryReferences;
                    RANDOM_faults++;
     			}
     		}
    	}//end while
		stop_r=clock();
		printRANDOM();
	}
  	else  
  	{
  		cout << "Unable to open file.";
  		return;
  	}
}//end runRANDOM
//=============================================================================

//=============================================================================
// PURPOSE: Prints the statistics corresponding for the RANDOM algorithm.  
//=============================================================================
void printRANDOM()
{
	cout << "\n====================================================" << endl;
	cout << "\t\t RANDOM Results " << endl;
	cout << "====================================================" << endl;
	cout << "Number of RANDOM faults: " << RANDOM_faults << endl;
	cout << "Number of Memory References: " << RANDOM_memoryReferences << endl;
	cout << "Number of RANDOM Flushes: " << RANDOM_flushes << endl;
	cout << "Time of simulation: " << ((stop_r-start_r)/(double(CLOCKS_PER_SEC))) << endl;
	cout << "====================================================\n\n" << endl;
}//end printRANDOM
//=============================================================================