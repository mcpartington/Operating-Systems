#include <string>
#include <vector>
using namespace std;

class Process 
{
	public:
		int id;
		int startTime;
		int finishTime;
		int totalCPU;
		int remainingCPU;
		int averageCPUBurst;
		int nextBurst;
		int IOBurst;
		int priority;
		string status;

		Process(int newId);
		~Process();
};

class PrintProcess
{
	public:
		int id;
		double startTime;
		double finishTime;
		double serviceTime;
		double IOtime;
		double turnaroundTime;
		double waitingTime;

		PrintProcess();
		~PrintProcess();
		int findProcess(int processID, vector<PrintProcess>& infoVec);
};