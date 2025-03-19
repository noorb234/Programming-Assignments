#include <string.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h> 
#include <math.h>
#include <stdio.h>
#include <algorithm>
using namespace std;


int turnaroundTime(int wt, int bt){
    return wt + bt;
}
int waitTime(int tat, int bt){
    return tat - bt;
}
double avgWaitTime(int waitTimes[], int n){
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += waitTimes[i];
    }
    return (double)sum / n;
}

struct Processes{
    int processId;
    int bt;
};
bool compareBurstTime(Processes a, Processes b){
    return a.bt < b.bt;
}

int main (){
    Processes process[] = {
        {1,2},
        {2,1},
        {3,8},
        {4,4},
        {5,5}
    };
    
    int turnaround[5];
    int processWaitTime[5];
    int start = 0;

    //FCFS
    for (int i = 0; i < 5; i++){
        turnaround[i] = turnaroundTime(start, process[i].bt);
        start += process[i].bt; 
    }
    for(int i = 0; i < 5; i++){
        processWaitTime[i] = waitTime(turnaround[i], process[i].bt);
    }
    printf("FCFS\n");
    printf("Process ID | Waiting Time | Turnaround Time\n");
    for(int i = 0; i < 5; i++){
        printf("%-15d %-17d %-10d\n", process[i].processId, processWaitTime[i], turnaround[i]);
    }
    printf("Average Weight Time: %f\n", avgWaitTime(processWaitTime, 5));


    //SJF
    sort (process, process + 5, compareBurstTime);

    start = 0;
    for (int i = 0; i < 5; i++) {
        turnaround[i] = 0;
        processWaitTime[i] = 0;
    }

    for (int i = 0; i < 5; i++){
        turnaround[i] = turnaroundTime(start, process[i].bt);
        start += process[i].bt; 
    }
    for(int i = 0; i < 5; i++){
        processWaitTime[i] = waitTime(turnaround[i], process[i].bt);
    }
    printf("\nSJF\n");
    printf("Process ID | Waiting Time | Turnaround Time\n");
    for(int i = 0; i < 5; i++){
        printf("%-15d %-17d %-10d\n", process[i].processId, processWaitTime[i], turnaround[i]);
    }
    printf("Average Weight Time: %f", avgWaitTime(processWaitTime, 5));


}