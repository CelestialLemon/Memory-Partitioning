#pragma once
#include <iostream>
#include <string>
#include "Visualizer.h"

int ChooseOperationVr()
{
	printf("\n\nChoose Operation\n1. Add a proces\n2. Mark process as complete\n3. View active processes\n4. Visualize\n5. Exit\n");
	int opt;
	std::cin >> opt;
	return opt;
}

int FindEmptyPartitionIndex(int memoryRequired, int numOfPartitions, int* partitionsOccupied, int* partitionSizes)
{
	int emptyPartitionSize = INT32_MAX;
	int emptyPartitionIndex = -1;
	for (int i = 0; i < numOfPartitions; i++)
	{
		if (partitionsOccupied[i] <= 0 && partitionSizes[i] >= memoryRequired)
		{
			if (partitionSizes[i] < emptyPartitionSize)
			{
				emptyPartitionIndex = i;
				emptyPartitionSize = partitionSizes[i];
			}
		}
	}
	return emptyPartitionIndex;
}

int AddAProcess(int numOfPartitions, int numOfActiveProcesses, int* partitionSizes, int* partitionsOccupied, std::string* processNames)
{
	printf("Enter name for process : ");
	std::string newProcessName;
	std::getline(std::cin >> std::ws, newProcessName);
	
	printf("Enter memory required for the process(MB) : ");
	int memoryRequired;
	std::cin >> memoryRequired;

	int emptyIndex = FindEmptyPartitionIndex(memoryRequired, numOfPartitions, partitionsOccupied, partitionSizes);
	if (emptyIndex == -1)
	{
		printf("Can't add the proccess, all partitions occupied or memory required to big\n");
		return numOfActiveProcesses;
	}
	else
	{
		if (newProcessName != "" && memoryRequired > 0)
		{
			//process has been added
			processNames[emptyIndex] = newProcessName;
			partitionsOccupied[emptyIndex] = memoryRequired;

			std::cout << processNames[emptyIndex] << " was added and allocated " << partitionsOccupied[emptyIndex]
				<< "MB of memory\n";
			numOfActiveProcesses++;
		}
		return numOfActiveProcesses;
	}
}

int FinishAProcess(int numOfPartitions, int numOfActiveProcesses, int* partitionsOccupied, std::string* processNames)
{
	printf("Enter name of process to finish : ");
	std::string processToFinish;
	std::getline(std::cin >> std::ws, processToFinish);

	for (int i = 0; i < numOfPartitions; i++)
	{
		if (processNames[i] == processToFinish)
		{
			//found
			std::cout << processToFinish << " was finished and " << partitionsOccupied[i] << "MB of memory was released\n";
			processNames[i] = "";
			partitionsOccupied[i] = 0;
			numOfActiveProcesses--;
			return numOfActiveProcesses;
		}
	}

	printf("Process not found!\n");
	return numOfActiveProcesses;
}



void ViewActiveProcesses(int numOfPartitions, int* partitionsOccupied, std::string* processNames)
{
	for (int i = 0; i < numOfPartitions; i++)
	{
		if (processNames[i] != "" && partitionsOccupied[i] > 0)
		{
			std::cout << processNames[i] << " , Memory Usage : " << partitionsOccupied[i] << "MB\n";
		}
	}
}

void StaticPartitioningWithVariablePartitionSize(int memorySize)
{
	printf("Enter num of partitions : ");
	int numOfPartitions;
	std::cin >> numOfPartitions;
	printf("Enter the sizes for %d partitions\n", numOfPartitions);
	int* partitionSizes = new int[numOfPartitions];
	int* partitionOccupied = new int[numOfPartitions];
	std::string* processNames = new std::string[numOfPartitions];

	for (int i = 0; i < numOfPartitions; i++)
	{
		std::cin >> partitionSizes[i];
		partitionOccupied[i] = 0;
		processNames[i] = "";
	}

	int numOfActiveProcesses = 0;
	while (true)
	{
		bool hasExit = false;

		switch (ChooseOperationVr())
		{
		case 1:
			numOfActiveProcesses = AddAProcess(numOfPartitions, numOfActiveProcesses, partitionSizes, partitionOccupied, processNames);
			break;

		case 2:
			numOfActiveProcesses = FinishAProcess(numOfPartitions, numOfActiveProcesses, partitionOccupied, processNames);
			break;

		case 3:
			ViewActiveProcesses(numOfPartitions, partitionOccupied, processNames);
			break;

		case 4:
			Visualize(memorySize, sqrt(memorySize), numOfPartitions, partitionSizes, partitionOccupied);
			break;

		case 5:
			hasExit = true;
			break;

		default:
			printf("Invalid choice!");
		}
		if (hasExit)
			break;
	}
}