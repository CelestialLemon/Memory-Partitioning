#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Visualizer.h"

int ChooseOperationDy()
{
	printf("\n\nChoose Operation\n1. Add a process\n2. Mark a process as complete\n3. View Active Processes\n4. Visualize\n5. Exit\n");
	int opt;
	std::cin >> opt;
	return opt;
}

int CalculateAvailableMemory(int memorySize, std::vector<int> partitionsOccupied)
{
	int memoryUsed = 0;
	for (int i = 0; i < partitionsOccupied.size(); i++)
	{
		memoryUsed += partitionsOccupied[i];
	}
	return memorySize - memoryUsed;
}

int AddAProcess(int memorySize, int numOfActiveProcess, std::vector<int>& partitionsOccupied, 
	std::vector<std::string>& processNames)
{
	printf("Enter name of the process : ");
	std::string newProcessName;
	std::getline(std::cin >> std::ws, newProcessName);

	printf("Enter memory required for the process(MB) : ");
	int memoryRequired;
	std::cin >> memoryRequired;

	int memoryAvailable = CalculateAvailableMemory(memorySize, partitionsOccupied);
	if (memoryRequired <= memoryAvailable)
	{
		if (newProcessName != "" && memoryRequired > 0)
		{
			std::cout << newProcessName << " was added and allocated " << memoryRequired
				<< "MB of memory\n";
			partitionsOccupied.push_back(memoryRequired);
			processNames.push_back(newProcessName);
			numOfActiveProcess++;
		}
		return numOfActiveProcess;
	}
	else
	{
		printf("Not enough memory!\n");
		return numOfActiveProcess;
	}
}

int FinishAProcess(int numOfActiveProcesses, std::vector<std::string>& processNames,
	std::vector<int>& partitionsOccupied)
{
	printf("Enter name of the process to finish : ");
	std::string processToFinish;
	std::getline(std::cin >> std::ws, processToFinish);


	for (int i = 0; i < numOfActiveProcesses; i++)
	{
		if (processNames[i] == processToFinish)
		{
			//found
			std::cout << processToFinish << " was finished and " << partitionsOccupied[i] << "MB of memory was released\n";
			processNames.erase(processNames.begin() + i);
			partitionsOccupied.erase(partitionsOccupied.begin() + i);
			numOfActiveProcesses--;
			return numOfActiveProcesses;
		}
	}

	printf("Process not found!\n");
	return numOfActiveProcesses;
}

void ViewActiveProcesses(int numOfActiveProcesses, std::vector<std::string>& processNames, 
	std::vector<int>& partitionOccupied)
{
	for (int i = 0; i < numOfActiveProcesses; i++)
	{
		std::cout << processNames[i] << " , Memory Usage : " << partitionOccupied[i] << "\n";
	}
}

void DynamicPartitioning(int memorySize)
{
	int numOfActiveProcesses = 0;
	std::vector<int> partitionOccupied;
	std::vector<std::string> processNames;
	while (true)
	{
		bool hasExit = false;

		switch (ChooseOperationDy())
		{
		case 1:
			numOfActiveProcesses = AddAProcess(memorySize, numOfActiveProcesses, partitionOccupied, processNames);
			break;

		case 2:
			numOfActiveProcesses = FinishAProcess(numOfActiveProcesses, processNames, partitionOccupied);
			break;

		case 3:
			ViewActiveProcesses(numOfActiveProcesses, processNames, partitionOccupied);
			break;

		case 4:
			Visualize(memorySize, sqrt(memorySize), numOfActiveProcesses, partitionOccupied, partitionOccupied);
			break;

		case 5:
			hasExit = true;
			break;
		}

		if (hasExit)
			break;
	}
}