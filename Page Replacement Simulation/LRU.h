//=============================================================================
// AUTHORS: Maxwell Partington, Mary Wakefield
// CLASS:   CS 433
// ASSIGN:  5
// DATE:    5/7/14
//
// PURPOSE: Contains the information to run the LRU page replacement algorithm.
//  This file has the runLRU function, the printLRU function, and the findLRUVictim.
//=============================================================================
#include <vector>
#include <iostream>
#include <fstream>
#include <istream>
#include <ctime>

#include "structures.h"

int LRU_faults = 0;
int LRU_memoryReferences = 0;
int LRU_flushes = 0;
int start_lru = 0;
int stop_lru = 0;

//function prototypes
void printLRU();
void findLRUvictim (vector<page> & v, int & victimIndex);

//=============================================================================
// PURPOSE: Perform the LRU page replacement algorithm.
// DESC:  This reads in reference addresses from the text file, checks to see if it
//      is even (read) or write (odd). In the case of even, it is marked valid. 
//      In the case of odd, it is marked dirty. It then calculates the page number
//      by dividing the reference by the page size the user entered. 
//      From there, the remainder of the algorithm is performed. 
//          checks to see if the pagenum is in the main memory
//          if it isnt, then it checks to see if the main memory is full
//          if the main memory is not full, it just adds the page to the back 
//          if the main memory is full, it must find a victim page number 
//          in the main memory to replace. the victim page number is the page number
//          which has been seen farthest back in time. 
//=============================================================================
void runLRU(int pageSize, int memory, int average)
{
    start_lru=clock();// start clock
	vector <page> LRU_MainMemory(pageSize); // vector of size user entered

	int reference = 0;
	int pageNum =0;
	bool inMemory = false;
    ifstream myfile ("references.txt");//("stupid.txt");
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
    		++j;
            LRU_memoryReferences++;

    		pageNum = reference/pageSize;
     		page newPage = page(); // create a new page object
     		newPage.refPageNum = pageNum; 
            newPage.lastUsedAtIndex = j; // update when it was seen last

    		if (reference % 2 == 0) // if reference is even, then it is a read access- make valid
    		{	
     			newPage.valid_bit = 1;
    		}
    		if ((reference % 2) != 0) // if reference is odd, then it is a write access- make it dirty
     		{
     			newPage.dirty_bit = 1;
     			inMemory = isInMemory(newPage.refPageNum, LRU_MainMemory);// returns true if pageNum is already in main memory

                if( inMemory)
                {
                    int page_index = locationInMemory(pageNum, LRU_MainMemory);
                    LRU_MainMemory[page_index].lastUsedAtIndex=j;//update when it was last seen
     			  
                }
                else if ((!inMemory) && (LRU_MainMemory.size() > numElementsInMainMem(LRU_MainMemory)) ) // not in main and space in main available
     			{
     				LRU_MainMemory[ numElementsInMainMem(LRU_MainMemory) ] = newPage;
                    LRU_memoryReferences++;
                    LRU_faults++;
     			}
     			else if ((!inMemory) && (LRU_MainMemory.size() == numElementsInMainMem(LRU_MainMemory))) // not in main and no space in main, pick a victim and remove
     			{// for LRU, this will be the last recently seen pageNum in our main memory. 
     				//find the victim 

                    findLRUvictim(LRU_MainMemory, victim_index);// contains the page that will be removed from the LRU main memory

     				if(LRU_MainMemory[victim_index].dirty_bit == 1)
     				{
     					LRU_flushes++;
     				}

     				LRU_MainMemory[victim_index] = newPage ; // now remove the victim pageNum and replace with new page num
                    LRU_memoryReferences++;
                    LRU_faults++;
     			}
     		}
     
    	}//end while
		stop_lru=clock();// stop clock
		printLRU();
	}
  	else  
  	{
  		cout << "Unable to open file.";
  		return;
  	}
}//end runLRU
//=============================================================================

//=============================================================================
// PURPOSE: To find the victim page number in the main memory 
// DESC: This returns the page which is the victim. The victim page is the page 
//     in main memory which has been least recently seen. It finds this by comparing 
//     the lastUsedAtIndex of each pagenumber in the main memory frames. 
//=============================================================================
void findLRUvictim (vector<page> &v, int & victimIndex)
{
    page victimPage = page(); // victim variable of type page.

    for( int i=0; i < v.size(); i++)
    {
        if( i ==0)//take the first page and compare to all other pages to find one with smalled LRU
        {
            victimPage = v[0];
            victimIndex=0;
        }
        else 
        {
            if( v[i].lastUsedAtIndex < victimPage.lastUsedAtIndex) // if found a new item in LRU main which has a later seen date, update the victim page
                {
                    victimPage = v[i];    
                    victimIndex =i;
                } 
        }
    }
}//end findLRUvictim
//=============================================================================


//=============================================================================
// PURPOSE: Prints the statistics corresponding for the LRU algorithm.  
//=============================================================================
void printLRU()
{
	cout << "\n====================================================" << endl;
	cout << "\t\t LRU Results " << endl;
	cout << "\n====================================================" << endl;
	cout << "Number of LRU faults: " << LRU_faults << endl;
	cout << "Number of Memory References: " << LRU_memoryReferences << endl;
	cout << "Number of LRU Flushes: " << LRU_flushes << endl;
	cout << "Time of simulation: " << ((stop_lru-start_lru)/(double(CLOCKS_PER_SEC))) << endl;
	cout << "====================================================" << endl;
}//end printLRU
//=============================================================================