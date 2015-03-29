#include <string>
using namespace std;
#include "Process.h"


class Event
{
	public:
		int eventTime;// time when event should take place. this needs to be overloaded
		int type;//type of event
		int procId; // process to which event belongs	

		Event(int eventType);
		Event();
		~Event();
		void printEvent();
		bool operator<(const Event& thing1)const ;
};