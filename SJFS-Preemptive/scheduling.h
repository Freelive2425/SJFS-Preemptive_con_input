#ifndef SCHEDULING_H_
#define SCHEDULING_H_

#include <vector>

typedef unsigned int uint;

class Scheduling
{
	uint currActiveProcessID;
	uint timeCounter = 0;

	std::vector<uint> arrivalTime;
	//When process start to execute
	std::vector<uint> burstTime;
	//process wait to execute after they have arrived
	std::vector<uint> waitingTime;

public:
	Scheduling(uint);
	Scheduling() = default;
	Scheduling(const Scheduling&) = delete;
	Scheduling &operator=(const Scheduling&) = delete;
	Scheduling(Scheduling&&) = delete;
	Scheduling &operator=(Scheduling&&) = delete;
	~Scheduling() = default;

	void calcWaitingTime();
	void printInfo();
};

#endif