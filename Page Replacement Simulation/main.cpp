//=============================================================================
// AUTHORS: Maxwell Partington, Mary Wakefield
// CLASS:   CS 433
// ASSIGN:  5
// DATE:    5/7/14
//
// PURPOSE: 
//=============================================================================

//=============================================================================
// This is the inclusion of relevant libraries and headers, as well as our global
// variables that will be used for the program. 
//=============================================================================
#include <string>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <istream>
#include <stdio.h>

using namespace std;

#include "FIFO.h"
#include "LRU.h"
#include "RANDOM.h"

//=============================================================================
// PURPOSE: This main program gets the page size and physical memory from the user and 
//	then calls the functions to run the FIFO, LRU, and Random page replacement algorithms. 
// DESC: Note that their are parameters on the page size and physical memory, which are 
//	displayed to the user on compilation time. The user will get stuck if the parameters entered 
//	are invalid. 
//		FIFO: first in first out. This paging algorithm first fills all spots in the main memory 
//			frames and then when you come across a page number that is not in main memory and the main 
//			memory frames are full, it replaces the pageNum that has been in main memory the longest 
//			with the new page number. 
//		LRU: least recently used. This paging algorithm first fills all spots in the main memory 
//			frames and then when it comes across a page number from the references file, which is not 
//			not in main memory and the main memory frames are full, it find the page number which has been 
//			least recently used and it replaces that one with the new page number. 
//		RANDOM: This paging algorithm first fills all spots in the main memory 
//			frames and then when it comes across a page number from the references file, which is not 
//			not in main memory and the main memory frames are full, it picks a random page number
//			from main memory frames and replaces it with the new frames. 
//		Generic Info: all of the algorithms tracks the number of faults, flushes, and memory references.
//			faults are the number of page numbers that are put into main memory which are not already in 
//			the main memory.  
//			flushes are when the page numbers in main memory correspond to a memory reference which are
//			dirty (which are write instructions-- can tell this by if even read, and write is odd).
//			memory references tracks the number of times we access the memory. This occurs 5 million times 
//			just from reading in references values from the text file and then the remaining are the number
//			of flushes that have occured. 
//=============================================================================
int main()
{
	int pageSize;
	int physicalMemory;
	int averageFrames;

	cout <<"\n========================================================" << endl;
	cout <<"\tPage Replacement Algorithm Simulation" << endl;
	cout << "\tMaxwell Partington and Mary Wakefield" << endl; 
	cout <<"========================================================" << endl;

	cout <<"\nPlease enter the page size you wish to simulate (Between 256 B and 8192 B): " << endl;
	cin >> pageSize;

	if ((pageSize < 256) || (pageSize > 8192) || ((pageSize % 2) != 0))
	{
		cout << "\nPlease enter a page size between 256 MB and 8192MB." << endl;
		return 0;
	}

	cout <<"\nPlease enter the physical memory you wish to simulate (4 MB, 16 MB, 32 MB, 64 MB): " << endl;
	cin >> physicalMemory;

	if ((physicalMemory != 4) && (physicalMemory != 16) && (physicalMemory != 32) && (physicalMemory != 64))
	{
		cout << "\nPlease enter a valid physical memory." << endl;
		return 0;
	}

	physicalMemory = (physicalMemory*1048576);
	averageFrames = physicalMemory/pageSize;

	cout << "\nRunning 'FIFO' algorithm, please wait..." << endl;
	runFIFO(pageSize, physicalMemory, averageFrames);

	cout << "\nRunning the 'LRU' algorithm, please wait..." << endl;
	runLRU(pageSize, physicalMemory, averageFrames);

	cout << "\nRunning the 'Random' algorithm, please wait..." << endl;
	runRANDOM(pageSize, physicalMemory, averageFrames);

	return 0;
}//end main
//=============================================================================