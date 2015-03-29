//=============================================================================
// AUTHORS: Maxwell Partington, Mary Wakefield
// CLASS:   CS 433
// ASSIGN:  5
// DATE:    5/7/14
//
// PURPOSE: contains the declaration of type class page 
//		and functions which are used by the page repalcement algorithms. 
//=============================================================================
#ifndef structures_h
#define structures_h
#include <vector>
using namespace std;

//=============================================================================
//PURPOSE: class object of type page. 
//=============================================================================
class page
 {
 	public:
		int valid_bit; // 0 for not valid, 1 for valid
		int dirty_bit; // 0 for not dirty, 1 for dirty
		int frame_number; 
		int refPageNum; // page number 
		int lastUsedAtIndex; // where it was last seen-- for LRU
		page();// constructor
};

//function declaration-- these are used for all page repalcement algoritms. 
bool isInMemory(int pageNum, vector<page> & v);
int locationInMemory(int pageNum, vector<page> & v);
int numElementsInMainMem(vector<page> & v);

#endif