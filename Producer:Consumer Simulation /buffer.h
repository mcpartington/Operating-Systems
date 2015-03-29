//=============================================================================
// AUTHORS: Maxwell Partington, Mary Wakefield
// CLASS:   CS 433
// ASSIGN:  4
// DATE:    4/21/14
// PURPOSE: This is our header file for the buffer and it's function required for 
//			the other parts of the program. 
//=============================================================================

#ifndef _BUFFER_H
#define _BUFFER_H

#include <semaphore.h>
#include <vector>
using namespace std;
#define BUFFER_SIZE 20

typedef int buffer_item;

const int MAXIMUM = 100; // used for random number for item
int mainThreadSleepTime; // time the main function will sleep for

sem_t full; // semaphore full- number of full slots in buffer 
sem_t empty; // sempaphore empty- number of empty slots in buffer

pthread_t cThread; // consumer thread 
pthread_t prodThread; // producer thread
pthread_mutex_t le_mutex; // the mutex lock

vector <buffer_item> buffer; // declaration of the actual buffer used

void insert_item(buffer_item item); // insert an item into the buffer
void remove_item(buffer_item *item); // remove an iten from the buffer

#endif