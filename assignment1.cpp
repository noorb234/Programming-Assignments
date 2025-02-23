#include <iostream> 
#include <string.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h> 
#include <cstdlib> 
#include <cmath>


void userMemoryAllocation (int array[], int startAddress, int pages) {
    int randomNum;
    int numPages = 0, processSize, unusedMem;
    int processID = 0;
    printf("Process:     Starting Mem:      Size of the Process:      Unused Space: \n");

    for (int i = 0; i < pages; i+=numPages){
        randomNum = rand() % 31;
        processSize = randomNum*80;         //size of the process
        numPages = ceil((double)processSize/160);         //number of pages for process
        if(i + numPages > pages)
            break;
        unusedMem = (numPages*160) - processSize;    //Unused space
        printf("%-12d %-18d %-25d %d\n", processID, startAddress, processSize, unusedMem);
        startAddress += numPages*160;               //starting address of the next process
        processID++;
    }
}


int main (){
    int array [100];
    userMemoryAllocation(array, 2000, 100);
}