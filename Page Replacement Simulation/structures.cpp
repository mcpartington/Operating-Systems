//=============================================================================
// AUTHORS: Maxwell Partington, Mary Wakefield
// CLASS:   CS 433
// ASSIGN:  5
// DATE:    5/7/14
//
// PURPOSE: contains implementation for the functions used by all the 
//		page repalcement algoritms. 
//=============================================================================

#include "structures.h"

//=============================================================================
//PURPOSE: To check to see if the pageNum passed is currently in the 
//		main memory vector passed in by the user. 
//DESC: If the page number is found, then it returns true. Otherwise, it returns false.
// 		It does this by looking at the items in the main memory and comparing it 
//		with the pagenumber which was passed in.  
//=============================================================================
bool isInMemory(int pageNum, vector<page> & v)
{
	for(int i = 0; i < v.size(); i++)
	{
		if(pageNum == v[i].refPageNum)
			return true;
	}
	return false; 
}
//=============================================================================

//=============================================================================
//PURPOSE: To get the location of the pageNum in the main memory vector.
//DESC: It returns the index location of the spot where the pagenum is found
//		in the memory vector. To ensure error checking, the function returns -1
//		if the pagenum was not found. 
//=============================================================================
int locationInMemory(int pageNum, vector<page> & v)
{
	for(int i = 0; i < v.size(); i++)
	{
		if(pageNum == v[i].refPageNum)
			return i;
	}
	return -1; 
}
//=============================================================================

//=============================================================================
//PURPOSE: To get the size of the vector which actually contains something. 
//DESC: It returns the integer number of spots in the vector (which is passed
//		in by the user), which contains page number. This is different from the 
//		.size() function because the .size() function does not account the spots
//		which are empty in a vector which is declared with a size. 
//=============================================================================
int numElementsInMainMem(vector<page> & v)
{
	int counter = 0;
	for (int i = 0; i < v.size(); i++)
	{
		if(v[i].refPageNum != 0)
		{
			counter++;
		}
	}
	return counter;
}
//=============================================================================

//=============================================================================
//PURPOSE: constructor for page
//=============================================================================
page::page()
{
	valid_bit = 0;
	dirty_bit = 0;
	frame_number = 0;
	refPageNum = 0; 
}
//=============================================================================

