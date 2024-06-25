#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define NUM_SMOKERS 3
#define NUM_AGENTS 1
#define NUM_SUPPLIERS 3

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int smoker_count;
    int agent_count;
    int supplier_count;
    int action_in_progress;
} meeting_point_t;

meeting_point_t meeting_point;

void initialize_meeting_point(meeting_point_t *mp) {
    pthread_mutex_init(&mp->mutex, NULL);
    pthread_cond_init(&mp->cond, NULL);
    mp->smoker_count = 0;
    mp->agent_count = 0;
    mp->supplier_count = 0;
    mp->action_in_progress = 0;
}

void wait_for_meeting(meeting_point_t *mp, const char *role) {
    pthread_mutex_lock(&mp->mutex);

    if (strcmp(role, "Smoker") == 0) {
        mp->smoker_count++;
    } else if (strcmp(role, "Agent") == 0) {
        mp->agent_count++;
    } else if (strcmp(role, "Supplier") == 0) {
        mp->supplier_count++;
    }

    while ((mp->smoker_count == 0 || mp->agent_count == 0 || mp->supplier_count == 0 || mp->action_in_progress)) {
        pthread_cond_wait(&mp->cond, &mp->mutex);
    }

    // All three types are present, and no action is currently in progress
    mp->action_in_progress = 1;

    pthread_mutex_unlock(&mp->mutex);
}

void finish_meeting(meeting_point_t *mp) {
    pthread_mutex_lock(&mp->mutex);

    mp->action_in_progress = 0;

    pthread_cond_broadcast(&mp->cond);
    pthread_mutex_unlock(&mp->mutex);
}

void* smoker_func(void* arg) {
    int id = *((int*)arg);
    while (1) {
        printf("Smoker %d arrived at the meeting point.\n", id);
        wait_for_meeting(&meeting_point, "Smoker");
        printf("Smoker %d is smoking.\n", id);
        sleep(1); // Simulate the time taken to smoke
        finish_meeting(&meeting_point);
    }
    return NULL;
}

void* agent_func(void* arg) {
    int id = *((int*)arg);
    while (1) {
        printf("Agent %d arrived at the meeting point.\n", id);
        wait_for_meeting(&meeting_point, "Agent");
        printf("Agent %d is providing ingredients.\n", id);
        sleep(1); // Simulate the time taken to provide ingredients
        finish_meeting(&meeting_point);
    }
    return NULL;
}

void* supplier_func(void* arg) {
    int id = *((int*)arg);
    while (1) {
        printf("Supplier %d arrived at the meeting point.\n", id);
        wait_for_meeting(&meeting_point, "Supplier");
        printf("Supplier %d is providing an ingredient.\n", id);
        sleep(1); // Simulate the time taken to provide an ingredient
        finish_meeting(&meeting_point);
    }
    return NULL;
}

int main() {
    
    pthread_t smokers[NUM_SMOKERS];
    pthread_t agents[NUM_AGENTS];
    pthread_t suppliers[NUM_SUPPLIERS];
    int smoker_ids[NUM_SMOKERS] = {1, 2, 3};
    int agent_ids[NUM_AGENTS] = {1};
    int supplier_ids[NUM_SUPPLIERS] = {1, 2, 3};

    initialize_meeting_point(&meeting_point);

    for (int i = 0; i < NUM_SMOKERS; i++) {
        pthread_create(&smokers[i], NULL, smoker_func, &smoker_ids[i]);
    }

    for (int i = 0; i < NUM_AGENTS; i++) {
        pthread_create(&agents[i], NULL, agent_func, &agent_ids[i]);
    }

    for (int i = 0; i < NUM_SUPPLIERS; i++) {
        pthread_create(&suppliers[i], NULL, supplier_func, &supplier_ids[i]);
    }

    for (int i = 0; i < NUM_SMOKERS; i++) {
        pthread_join(smokers[i], NULL);
    }

    for (int i = 0; i < NUM_AGENTS; i++) {
        pthread_join(agents[i], NULL);
    }

    for (int i = 0; i < NUM_SUPPLIERS; i++) {
        pthread_join(suppliers[i], NULL);
    }

    pthread_mutex_destroy(&meeting_point.mutex);
    pthread_cond_destroy(&meeting_point.cond);

    return 0;
}
