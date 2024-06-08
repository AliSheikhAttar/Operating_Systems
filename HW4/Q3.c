#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define N 5  // Number of chefs
#define C 3  // Pantry capacity

// Mutexes for utensils
pthread_mutex_t utensils[N];

// Semaphores for pantry
sem_t empty_slots;  // Counts empty slots in the pantry
sem_t filled_slots; // Counts filled slots in the pantry

void* chef(void* arg) {
    int id = *((int*)arg);
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        // Try to acquire utensils
        if (id % 2 == 0) { // read the explanation for this at the end
            pthread_mutex_lock(&utensils[left]);
            pthread_mutex_lock(&utensils[right]);
        } else {
            pthread_mutex_lock(&utensils[right]);
            pthread_mutex_lock(&utensils[left]);
        }

        // Prepare food
        printf("Chef %d is preparing food.\n", id);
        sleep(1.01); // Simulate time to prepare food

        // Store food in pantry
        sem_wait(&empty_slots);
        sleep(.85);// Simulate time to store food
        printf("Chef %d stored food.\n", id);
        sem_post(&filled_slots);

        // Release utensils
        pthread_mutex_unlock(&utensils[right]);
        pthread_mutex_unlock(&utensils[left]);

        // Serve food
        sem_wait(&filled_slots);
        sleep(1.32); // Simulate time to serve food
        printf("Chef %d served food.\n", id);
        sem_post(&empty_slots);
    }

    return NULL;
}

int main() {
    pthread_t chefs[N];
    int ids[N];

    // Initialize utensils mutexes
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&utensils[i], NULL);
    }

    // Initialize semaphores
    sem_init(&empty_slots, 0, C); // Pantry starts with C empty slots
    sem_init(&filled_slots, 0, 0); // Pantry starts with 0 filled slots

    // Create chef threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&chefs[i], NULL, chef, &ids[i]);
    }

    // Join chef threads
    for (int i = 0; i < N; i++) {
        pthread_join(chefs[i], NULL);
    }

    // Destroy utensils mutexes
    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&utensils[i]);
    }

    // Destroy semaphores
    sem_destroy(&empty_slots);
    sem_destroy(&filled_slots);

    return 0;
}

// Changes and Explanation:
// Alternating Lock Order:

// Chefs with even IDs try to acquire the left utensil first and then the right utensil.
// Chefs with odd IDs try to acquire the right utensil first and then the left utensil.
// This alternating lock order helps to prevent deadlock by ensuring that not all chefs are always trying to acquire the same utensil in the same order.
// Ensuring Fairness:

// By alternating the lock order, we prevent a single chef from continuously acquiring resources and dominating the execution.
// Each chef now has a fair chance to acquire the necessary utensils and access the pantry.
// Mutex and Semaphore Management:

// The mutexes and semaphores ensure proper synchronization, so no two adjacent chefs can use the same utensil simultaneously, and pantry capacity constraints are respected.