#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;
int shared_data = 0;
bool dataReady = false;

void* writeFunction(void* arg){
    int threadID = *(int*)arg;
    pthread_mutex_lock(&lock);
    shared_data = 700;
    printf("Thread %d: Writing value %d into shared data\n", threadID, shared_data);
    dataReady = true;
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* readFunction(void* arg){
    int threadID = *(int*)arg;
    while(dataReady == true){
        pthread_mutex_lock(&lock);
        printf("Thread %d: Reading value %d from shared data\n", threadID, shared_data);
        pthread_mutex_unlock(&lock);
        break;
    }
    return NULL;
}

int main (){
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&thread1, NULL, writeFunction, &id1);
    pthread_create(&thread2, NULL, readFunction, &id2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&lock);
    printf("main thread finished\n");
    return 0;
}