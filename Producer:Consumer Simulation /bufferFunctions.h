//=============================================================================
// AUTHORS: Maxwell Partington, Mary Wakefield
// CLASS:   CS 433
// ASSIGN:  4
// DATE:    4/21/14
// PURPOSE: This file is called buffer1.h.  It contains the functionality for 
//		the insert and remove functions from the buffer.
//=============================================================================

#include "buffer.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//=============================================================================
//Purpose: The purpose of this function is to insert an item into the buffer.
// 	It does this by pushing it to the rear of the vector. The semaphores in 
//	the main function checks to see if the buffer is full before inserting. 
//=============================================================================
//=============================================================================
void insert_item(buffer_item item) 
{ 
	buffer.push_back(item); // push item to back of buffer
}

//=============================================================================
//Purpose: The purpose of this function is to remove an item from the 
// 	buffer. It saves the removed buffer item into "item" so that it can 
//	print it in the consumer function. The empty semaphore in the main function 
//	is used to check to see if the buffer is full. 
//=============================================================================
//=============================================================================
void remove_item(buffer_item &item) 
{ 
	if( buffer.size() != 0) // if the buffer has something, then save it into 
		// item and then erase it. 
	{
		item= buffer[0]; // save first element in buffer into item
		buffer.erase(buffer.begin() + 0); // erase it from buffer
	}
}