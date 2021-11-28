#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#define PROCESS_NAME_MAX_LENGTH 60;

int ChooseOperation()
{
    printf("\n\nChoose an operation\n1. Add a process\n2. Mark Process as complete\n3. View active processes\n4. Visualize\n5. Exit\n");
    int opt;
    std::cin >> opt;
    return opt;
}

int FindEmptyPartitionIndex(int* partitionsOccupied, int numOfPartitions)
{
    //find which partition in the array is empty for allowing the allocation of a process
    for (int i = 0; i < numOfPartitions; i++)
    {
        if(partitionsOccupied[i] == 0)
        return i;
    }

    return -1;
}

int AddAProcess(int* partitionsOccupied, std::string* processNames, int numOfActiveProcesses, int partitionSize, int numOfPartitions)
{
    int emptyIndex = FindEmptyPartitionIndex(partitionsOccupied, numOfPartitions);

    if (emptyIndex == -1)
    {
        printf("Can't find empty partitions to allocate memory\n");
        return numOfActiveProcesses;
    }
    else
    {
        printf("Enter the name of the process : ");
        std::string newProcessName;
        std::getline(std::cin >> std::ws, newProcessName);
        printf("Enter memory required for the proccess : ");
        int memoryRequired;
        std::cin >> memoryRequired;

        if (partitionsOccupied[emptyIndex] > partitionSize)
        {
            //cant fit process in partition
            printf("Can't allocate memory for partition that large");
            processNames[emptyIndex] = "";
            partitionsOccupied[emptyIndex] = 0;
        }

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

void ViewActiveProcesses(std::string* processNames, int* partitionOccupied, int numOfPartitions, int numOfActiveProcesses)
{
    printf("Active processes : %d\n", numOfActiveProcesses);
    for (int i = 0; i < numOfPartitions; i++)
    {
        if(processNames[i] != "" && partitionOccupied[i] > 0)
        std::cout << processNames[i] << " , Memory Usage : " << partitionOccupied[i] << "MB\n";
    }
}

int FinishAProcess(std::string* processNames, int* partitionOccupied, int numOfPartitions, int numOfActiveProccesess)
{
    printf("Enter name of the process to finish : ");
    std::string processToFinish;
    std::getline(std::cin >> std::ws, processToFinish);

    for (int i = 0; i < numOfPartitions; i++)
    {
        if (processNames[i] == processToFinish)
        {
            std::cout << processToFinish << " was finished and " << partitionOccupied[i] << "MB of memory was released\n";
            processNames[i] = "";
            partitionOccupied[i] = 0;
            numOfActiveProccesess--;
            return numOfActiveProccesess;
        }
    }

    //if process not found
    printf("Process not found!\n");
    return numOfActiveProccesess;
}

void StaticPartitioningWithFixedPartitionSize(int memorySize)
{
    int numOfPartitions, numOfActiveProcesses = 0;

    printf("Enter num of partitions : ");
    std::cin >> numOfPartitions;
    int rowSize = sqrt(numOfPartitions);

    int* partitionSizes = new int[numOfPartitions];
    int* partitionsOccupied = new int[numOfPartitions];
    std::string* processNames = new std::string[numOfPartitions];

    int partitionSize = memorySize / numOfPartitions; //if 100 memory blocks and 10 partition each partition gets 10 blocks
    for (int i = 0; i < numOfPartitions; i++)
    {
        partitionSizes[i] = partitionSize;
        partitionsOccupied[i] = 0;
        processNames[i] = "";
    }


    while (true)
    {
        bool hasExit = false;
        switch (ChooseOperation())
        {
        case 1:
            if (numOfActiveProcesses >= numOfPartitions)
                printf("The memory partitions are full, wait for some processes to finish\n");
            else
                numOfActiveProcesses = AddAProcess(partitionsOccupied, processNames, numOfActiveProcesses, partitionSize, numOfPartitions);
            break;

        case 2:
            numOfActiveProcesses = FinishAProcess(processNames, partitionsOccupied, numOfPartitions, numOfActiveProcesses);
            break;

        case 3:
            ViewActiveProcesses(processNames, partitionsOccupied, numOfPartitions, numOfActiveProcesses);
            break;

        case 4:
            Visualize(memorySize, sqrt(memorySize), numOfPartitions, partitionSizes, partitionsOccupied);
            break;

        case 5:
            hasExit = true;

        default:
            printf("Invalid choice!\n");
        }

        if (hasExit)
            break;
    }

    
}