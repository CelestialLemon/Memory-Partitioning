#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "Visualizer.h"
#include "StaticPartitioningWithFixedPartitionSize.h"
#include "StaticPartitioningWithVariablePartitionSize.h"
#include "DynamicPartitioning.h"

int ChooseMemoryPartitionMethod()
{
    int opt;
    
    printf("Choose the method for partitioning:\n");
    printf("1. Static Partitioning with fixed partition size\n");
    printf("2. Static Partitioning with variable partition size\n");
    printf("3. Dynamic Partitioning\n");
    
    std::cin >> opt;
    return opt;
}


int main()
{
    int memorySize;
    printf("Enter the size of memory(MB) : ");
    std::cin >> memorySize;
    
    switch (ChooseMemoryPartitionMethod())
    {
    case 1:
        StaticPartitioningWithFixedPartitionSize(memorySize);
        break;

    case 2:
        StaticPartitioningWithVariablePartitionSize(memorySize);
        break;

    case 3:
        DynamicPartitioning(memorySize);
        break;

    default:
        printf("Invalid choice!");
    }

    

    return 0;
}