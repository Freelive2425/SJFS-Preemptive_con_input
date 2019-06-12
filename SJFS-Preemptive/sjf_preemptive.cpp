#include <iostream>
#include <array>
#include <vector>
#include <algorithm> // std::find
#include <iterator> // std::begin, std::end
#include <limits> //std::numeric_limits
#include "scheduling.h"

typedef unsigned int uint;

using namespace std;
Scheduling::Scheduling(uint n)
{
	for (int i = 0; i < n; i++)
	{
		arrivalTime.reserve(n);
		burstTime.reserve(n);
		waitingTime.reserve(n);

		uint val;
		std::cout << "Enter arrival time for process " << i + 1 << "\n";
		std::cin >> val;
		arrivalTime.push_back(val);

		std::cout << "Enter burst time for process " << i + 1 << "\n";
		std::cin >> val;
		burstTime.push_back(val);

		waitingTime.push_back(0);
	}
}

bool isAllZeroes(std::vector<uint>& burstTimeCopy)
{
	for (int i = 0; i < burstTimeCopy.size(); i++)
	{
		if (burstTimeCopy[i] != 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

void Scheduling::calcWaitingTime()
{
	std::vector<uint> burstTimeCopy;
	burstTimeCopy.reserve(burstTime.size());
	uint index = 0;
	std::vector<uint>::iterator it;
	while (isAllZeroes(burstTimeCopy) == false)
	{
		auto max = std::max_element(arrivalTime.begin(), arrivalTime.end());
		if (timeCounter <= *max)
		{
			it = arrivalTime.end();
			it = std::find(arrivalTime.begin(), arrivalTime.end(), timeCounter);
			if (it != arrivalTime.end())
			{
				index = std::distance(arrivalTime.begin(), it);
			}

			if (burstTimeCopy.empty() == true || index != currActiveProcessID)
			{
				burstTimeCopy.push_back(burstTime[index]);
			}

			uint minBurstTime = std::numeric_limits<uint>::max();
			//Find index with minimum burst Time remaining
			for (int i = 0; i < burstTimeCopy.size(); i++)
			{
				if (burstTimeCopy[i] != 0 && burstTimeCopy[i] < minBurstTime)
				{
					minBurstTime = burstTimeCopy[i];
					index = i;
				}
			}
			currActiveProcessID = index;
			burstTimeCopy[currActiveProcessID] -= 1;

			for (int i = 0; i < arrivalTime.size(); i++)
			{
				if (timeCounter >= arrivalTime[i] && i != currActiveProcessID
					&& burstTimeCopy[i] != 0)
				{
					waitingTime[i] += 1;
				}
			}
			timeCounter++;
		}
		else
		{
			uint minBurstTime = std::numeric_limits<uint>::max();
			//Find index with minimum burst Time remaining
			for (int i = 0; i < burstTimeCopy.size(); i++)
			{
				if (burstTimeCopy[i] != 0 && burstTimeCopy[i] < minBurstTime)
				{
					minBurstTime = burstTimeCopy[i];
					index = i;
				}
			}
			currActiveProcessID = index;
			burstTimeCopy[index] -= minBurstTime;

			for (int i = 0; i < arrivalTime.size(); i++)
			{
				if (i != currActiveProcessID && burstTimeCopy[i] != 0)
				{
					waitingTime[i] = waitingTime[i] + minBurstTime;
				}
			}
			timeCounter += minBurstTime;
		}
	}
}

void Scheduling::printInfo()
{
	std::cout << "ProcessID\tArrival Time\tBurst Time\tWaiting Time\n";
	for (int i = 0; i < arrivalTime.size(); i++)
	{
		std::cout << i + 1 << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i];
		std::cout << "\t\t" << waitingTime[i] << "\n";
	}
}

int main()
{
	int num;
	std::cout << "Enter the number of processes\n";
	std::cin >> num;
	Scheduling shortestJobFirst(num);
	shortestJobFirst.calcWaitingTime();
	shortestJobFirst.printInfo();
	system("pause");
	return 0;
}