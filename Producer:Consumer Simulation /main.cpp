//=============================================================================
// AUTHORS: Maxwell Partington, Mary Wakefield
// CLASS:   CS 433
// ASSIGN:  4
// DATE:    4/21/14
// PURPOSE: This is our cpp file for our buffer.
//=============================================================================
#include <iostream>
#include <string>
#include <cstdio>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

#include "bufferFunctions.h"

//Function Prototypes
void getInitialInfo(int &mainThreadSleepTime, int &numProducerThreads, int &numConsumerThreads);
void initializeBuffer(int &mainThreadSleepTime, int &numProducerThreads, int &numConsumerThreads);
void *producer(void *param);
void *consumer(void *param);
void printingBuffer();

//=============================================================================
// PURPOSE: This is the main function. It sets up the the parameters needed 
//			for the program to run and then sleeps for the given amount of time. 
//			It provides a nice user input/table options for the user to input and 
//			change parameters.
// DESCRIPTION: It gets the user entered inputs for the length of time the 
//			main program will sleep, the number of producer threads, and the consumer threads. 
//			It then calls get initial info that provides a table format. 
//=============================================================================
int main(int argc, char *argv[]) {

//double checks to make sure the buffer is empty before starting
while(buffer.size() != 0)
{
	buffer.erase(buffer.begin() + 0);
}

int numProducerThreads; 
int numConsumerThreads;

cout << "===============================================================================" << endl;
cout << "Funded and designed by Maxwell Partington and Mrs. Mary Wakefield" << endl;
cout << "\n(Please feel free to donate with contributions of pizza and Disneyland tickets.)" << endl;
cout << "(Disneyland is copyright and trademark ©Disney, 2014.)" << endl;
cout << "===============================================================================" << endl;

cout << "\n\n===============================================================================" << endl;
cout << "Hello! Welcome to your personal producer-consumer simulation!" << endl;
cout << "===============================================================================" << endl;
cout << "Enter the length of time the main thread should Sleep (in seconds): ";
cin >> mainThreadSleepTime;
cout << "Enter the number of Producer Threads: ";
cin >> numProducerThreads;
cout << "Enter the number of Consumer Threads: ";
cin >> numConsumerThreads; 
cout << "===============================================================================" << endl;

//sets up remaining part of program
getInitialInfo(mainThreadSleepTime, numProducerThreads, numConsumerThreads);

cout << "\n-----------------------------" << endl;	
cout << "Putting the main to sleep..." << endl;
cout << "-----------------------------" << endl;

//sleep for indicated time, then exit upon awakening
sleep(mainThreadSleepTime );
return  0;

}//end main 

//=============================================================================

//=============================================================================
// PURPOSE: The purpose of this function is to ensure user entered parameters
//			are correct to the users specifications.
// DESCRIPTION: The following function displays the information that was entered by
//			the user, and asks whether or not the user would like to edit it
//			or continue on. 
//=============================================================================
void getInitialInfo(int &mainThreadSleepTime, int &numProducerThreads, int &numConsumerThreads)
{

	int userResponse; // contains the user entered response to the menu options
	// 1 = confirm, 2= change sleep, 3= change producer, 4= change consumer
	
	//menu formatting
	cout<< "\n===================== THANK YOU! ==================" << endl;
	cout<< "You entered: " << endl;
	cout<< "---------------------------------------------------" << endl;
	cout<< "\tSleep Time: " << mainThreadSleepTime << endl;
	cout<< "\tProducer Threads: " << numProducerThreads << endl;
	cout<< "\tConsumer Threads: " << numConsumerThreads<< endl;
	cout<< "===================================================" << endl;

	cout<< "\n===================================================" << endl;
	cout<< "Please confirm or edit the Following: " << endl;
	cout<< "	1. Confirm your entry." << endl;
	cout<< "	2. Change sleep time" << endl;
	cout<< "	3. Change number of producer threads." << endl;
	cout<< "	4. Change number of consumer threads." <<endl;
	cout<< "===================================================" << endl;
	cout<< "Entry: "; 
	cin>> userResponse;
	cout<< "===================================================" << endl;
	
	switch(userResponse)
	{
		case 1: {//confirm
					// run remainder of program
					cout << "Well, alright then! Lets start simulating!" << endl;
					cout<< "===================================================\n" << endl;
					initializeBuffer(mainThreadSleepTime, numProducerThreads, numConsumerThreads);
					break;
				}
		case 2: {// change sleep time
					cout << "\nEnter your new sleep time: ";
					cin >> mainThreadSleepTime;
					getInitialInfo(mainThreadSleepTime, numProducerThreads, numConsumerThreads);
					break;
				}
		case 3: { // change producer threads
					cout << "\nEnter your new producer thread count: ";
					cin >> numProducerThreads;
					getInitialInfo(mainThreadSleepTime, numProducerThreads, numConsumerThreads);
					break;
				}
		case 4: { // change consumer threads
					cout << "\nEnter your new consumer thread count: ";
					cin >> numConsumerThreads;
					getInitialInfo(mainThreadSleepTime, numProducerThreads, numConsumerThreads);
					break;
				}
		default:{  // entered incorrect option 
					cout<<"\n\n!!Wrong command- Please try again!!\n";
					getInitialInfo(mainThreadSleepTime, numProducerThreads, numConsumerThreads);
					break;
				}
	}	
}//end getInitialInfo

//=============================================================================

//=============================================================================
// PURPOSE: This function intializes all of the necessary parts of the buffer,
//			such as the mutex, the semaphores, and the consumer and producer 
//			threads. 
// DESCRIPTION: It begins by creating the p_thread mutex, which will be used to call
//			the lock and unlock functions when the buffer will be used. The sem's
//			will also be created to be used to examine when the buffer is full
//			or empty. Lastly, our function calls to the produced and consumer
//			thread creators is used and we finish intializing the buffer. 
//=============================================================================
void initializeBuffer(int &sleepTime, int &producerThreads, int &consumerThreads)
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_t producerID[producerThreads];
	pthread_t consumerID[consumerThreads];

	pthread_mutex_init(&le_mutex,NULL);

	for (int i =0; i < producerThreads; i++ ) //creates all producer threads
		{
			pthread_create(&producerID[i], &attr, producer, NULL);
			//cout <<" pthread : " << producerID[i]<<endl; 
		}
	for(int j =0; j < consumerThreads; j++) // creates all consumer threads
		{
			pthread_create(&consumerID[j], &attr, consumer, NULL);
			//cout<< " cthread: " << consumerID[j] <<endl;
	    }

}//end intializebuffer

//=============================================================================-

//=============================================================================
// PURPOSE: The following function controls our newly created producer thread.
//			It will alternate between sleeping for random periods of time, as well
//			as inserting items (producing) into the buffer. 
// DESCRIPTION: This function achieves it's purpose by producing a randomly generated
//			integer, checking to see if the buffer is free to use. If it is, it
//			inserts the new integer. Otherwise, it waits until it can. 
//=============================================================================
void *producer(void *param)
{	
	buffer_item item; // buffer item

	while( true)
	{
		sleep( rand() % mainThreadSleepTime );//random number for thread to sleep
		// did mod mainThreadSleepTime because we assumed that the thread sleep time 
		// had to be less than the main function sleep time
	
		item = rand() % MAXIMUM +1; // random item number 1-MAXIMUM

		pthread_mutex_lock(&le_mutex); // lock mutex

		// Critical Section
		cout<< "\nItem: \"" << item << "\", added to the buffer. ";
		insert_item(item);
		printingBuffer();
		// end Critical Section 

		pthread_mutex_unlock(&le_mutex); // unlock mutex

		sem_post( &full);
	} 

}//end producer 

//=============================================================================

//=============================================================================
// PURPOSE: This function controls the consumer thread. It will sleep for random
//			periods of time, and when it awakens, it will attempt to remove an 
//			item from the buffer. 
// DESCRIPTION: It achieves the above purpose by checking to see if the buffer is
//			unoccupied. If it is, it will remove an item from the buffer, other
//			-wise it will wait until it is able to do so. Lastly, it will sleep
//			for random intervals. 
//=============================================================================
void *consumer(void *param)
{
	buffer_item item;	// buffer item

	while(true) 
	{ 
		sleep( rand() % mainThreadSleepTime);//random number for thread to sleep
		// did mod mainThreadSleepTime because we assumed that the thread sleep time 
		// had to be less than the main function sleep time

		sem_wait(&full); 

		pthread_mutex_lock(&le_mutex); // lock mutex
		 
		 //Critical Section 
		remove_item(item);	
		if( item != 0 )
			cout << "\nItem: \""  << item << "\", consumed by a consumer.";
		else
			cout<< "\nNothing to consume.";
		printingBuffer();
		// End Critical Section 
		
		pthread_mutex_unlock(&le_mutex); // unlock mutex

		sem_post(&empty);
	} 
}// end consumer 

//=============================================================================
//PURPOSE: This purpose of this function is to print the contents of the buffer. 	
// DESCRIPTION: If there is nothing in the buffer, "buffer empty" is printed. 
//  	If there is contents in the buffer, then the items are print in the 
//		following format: < item, item ,... , item >
//=============================================================================
//=============================================================================
void printingBuffer()
{
	
	if(buffer.size() == 0) // If there is nothing in the buffer
		{
			cout<< "\nUpdated Buffer: ";
			cout << "< buffer empty >" << endl;
		}
	else // buffer contains items, print them out
	{	cout<< "\nUpdated Buffer: ";
		cout << "< ";
		for(int i = 0; i < buffer.size(); i++)
			{
				if( i != buffer.size() -1 ) // if it is not the last element
					// in the buffer, then put , after it is printed
					cout << buffer[i] << ", ";
				else // if it is last in buffer, then no , 
					cout << buffer[i] ;
			}
		cout << " >\n"; 
	}
}//end printingBuffer
//=============================================================================