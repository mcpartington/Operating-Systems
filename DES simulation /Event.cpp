#include <string>
#include <iostream>
using namespace std;
#include "Event.h"


Event::Event()
{
	eventTime=0;
	type = 0;
	procId=0;
}
Event::~Event()
{

}

Event::Event(int eventType)
{
	eventTime= 0;
	type =eventType;
	procId =0;
}
void Event::printEvent()
{
	cout<< "time, type, id: " << eventTime <<" " << type << " " << procId <<endl;
}


bool Event::operator<(const Event& thing1)const 
{
	return (eventTime < thing1.eventTime); // want to compare the event time of Event
}