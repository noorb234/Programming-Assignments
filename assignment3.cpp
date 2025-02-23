//Noor Baig R02136650
/*
1. When the fork() operation is executed, the stack and heap storage are not shared between the parent and child process. 
The fork() operation duplicates the memory space for each process, allowing changes made in each process to be done independently of one another. 
Shared memory segments are shared between the parent and child processes. 
In this case, both process can access and modify this memory segment to allow inter process communication to occur. 

2. Apple's IOS was able to run concurrent processes by allowing a foreground application to open and appear on the screen and the background application to remain in the memory but not on the display screen.
This allows multiple processes to run without being suspended. Recent devices are able to hold multiple processing cores that allowed two foreground apps to run at the same time. 
Android supported concurrent processing by including a service component to their applications. 
If an application in the background required processing, the service will allow it to run even if the background application is suspended. 
Services do not use a user interface and only took up a small part in the memory, so this allowed processes to run concurrently and efficiently. 
Concurrent processing can lead to complications such as deadlocks. 
It multiple processes are waiting for resources that are held by each other, processes are stuck waiting and can cause a deadlock in the system. 
Likewise, synchronization can also be an issue when it comes to shared memory. 
The memory needs to be modified synchronously with other processes to prevent any inconsistencies in the data. 
Finally, if processes are running concurrently, we need to ensure the parent process is waiting for the child to terminate before exiting to not leave the child processes as orphans. 
*/

#include <iostream> 
#include <string.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h> 
#include <cstdlib> 
#include <cmath>


int main (){
    int num;
    int array[20];
    int arraySize = sizeof(array)/ sizeof(int);
    int start, end, min, finalMin;
    int fd[2];

    printf("Array: ");
    for (int i = 0; i < arraySize; i++){
        num = rand() % 101;
        array[i] = num; 
        printf("%d,", array[i]);
    }
    printf("\n");

    if (pipe(fd) == -1){
        return 2;
    }
    int id = fork();

    if (id == -1){
        return 1;
    }
    
    if (id == 0){
        start = 0;
        end = arraySize/2;
        min = array[start];
    }
    else{ 
        start = arraySize/2 + 1;
        end = arraySize;
        min = array[start];
    }
    for (int i = start; i < end; i++){
        if (array[i] < min)
            min = array[i];
    
    }
    printf("Minimum value: %d\n", min);

    if (id == 0){
        printf("Child Process ID: %d\n", getpid());
        write(fd[1], &min, sizeof(min));
        close (fd[1]);
    }
    else {
        printf("Parent Process ID: %d\n", getpid());
        close (fd[1]);
        int childMin;
        read(fd[0], &childMin, sizeof(int));
        close (fd[0]);
        if (min <= childMin){
            finalMin = min;
        }
        else{
            finalMin = childMin;
        }
        printf("The minimum value in the array is: %d\n", finalMin);
    }
return 0;
}