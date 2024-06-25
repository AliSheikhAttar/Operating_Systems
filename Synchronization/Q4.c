#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

pthread_barrier_t barrier;

int neccessary[3] = {};

void *smoker_function(void *arg) {
    int id = *(int *)arg;
    printf("Smoker %d arrived at the meeting\n", id);
    sleep(rand() % 3);
    printf("Smoker %d is waiting for others\n", id);
    pthread_barrier_wait(&barrier);
    printf("Smoker, agent & supplier gathered, Smoker %d is smoking\n", id);
    printf("Smoker %d is leaving the meeting\n", id);
    free(arg);
    return NULL;
}

void *agent_function(void *arg) {
    int id = *(int *)arg;
    printf("Agent %d arrived at the meeting\n", id);
    sleep(rand() % 3);
    printf("Agent %d is waiting for others\n", id);
    pthread_barrier_wait(&barrier);
    printf("Agent %d is leaving the meeting\n", id);
    free(arg);
    return NULL;
}

void *supplier_function(void *arg) {
    int id = *(int *)arg;
    printf("Supplier %d arrived at the meeting\n", id);
    sleep(rand() % 3);
    printf("Supplier %d is waiting for others\n", id);
    pthread_barrier_wait(&barrier);
    printf("Supplier %d is leaving the meeting\n", id);
    free(arg);
    return NULL;
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    
    int total_threads;
    printf("# all people: ");
    scanf("%d", &total_threads);

    pthread_t threads[total_threads];
    pthread_barrier_init(&barrier, NULL, total_threads);

    int counter_smoker = 0, counter_agent = 0, counter_supplier = 0;
    
    for (int i = 0; i < total_threads; i++) {
        int rand_value = rand() % 10;
        int *id = malloc(sizeof(int));
        // *id = i + 1; // Unique id for each thread

        if (rand_value == 0 || rand_value == 2 || rand_value == 5) {
            counter_smoker++;
            *id = counter_smoker;
            pthread_create(&threads[i], NULL, smoker_function, id);
        } else if (rand_value == 1 || rand_value == 3 || rand_value == 8 || rand_value == 9) {
            counter_agent++;
            *id = counter_agent;
            pthread_create(&threads[i], NULL, agent_function, id);
        } else if (rand_value == 4 || rand_value == 6 || rand_value == 7) {
            counter_supplier++;
            *id = counter_supplier;
            pthread_create(&threads[i], NULL, supplier_function, id);
        }
    }

    for (int i = 0; i < total_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);

    return 0;
}
