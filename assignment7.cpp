#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 2

// Semaphore for forks
sem_t forks[NUM_PHILOSOPHERS];

// Semaphore for mutual exclusion
sem_t mutex;

// Function to simulate philosopher thinking
void think(int philosopher_id) {
    printf("Philosopher %d is thinking.\n", philosopher_id);
    sleep(1);  // Simulate thinking time
}

// Function to simulate philosopher eating
void eat(int philosopher_id) {
    printf("Philosopher %d is eating.\n", philosopher_id);
    sleep(2);  // Simulate eating time
}

// Function to simulate a philosopher's life cycle
void* philosopher(void* arg) {
    int philosopher_id = *(int*)arg;

    while (1) {
        think(philosopher_id);  // Philosopher thinks

        // Pick up forks
        sem_wait(&mutex);  // Enter critical section
        sem_wait(&forks[philosopher_id]);  // Pick up left fork
        sem_wait(&forks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);  // Pick up right fork

        // Start eating
        eat(philosopher_id);

        // Put down forks
        sem_post(&forks[philosopher_id]);  // Put down left fork
        sem_post(&forks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);  // Put down right fork
        sem_post(&mutex);  // Exit critical section
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);  // Initialize each fork semaphore to 1 (available)
    }
    sem_init(&mutex, 0, 1);  // Initialize mutex semaphore to 1 (available)

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Wait for all threads to finish (in this case, threads run forever)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }
    sem_destroy(&mutex);  // Destroy mutex semaphore

    return 0;
}