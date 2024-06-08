#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define FREE_SEATS 10

sem_t barber_is_ready;
sem_t access_seat_no;
sem_t customer_is_ready;
int free_seats_no = FREE_SEATS;

void *barber(void *arg) {
    while (1) {
        sem_wait(&customer_is_ready); // Wait for customer
        sem_wait(&access_seat_no); // Get access to modify free seats
        free_seats_no +=1; // One chair gets free
        sem_post(&barber_is_ready); // Barber is ready
        sem_post(&access_seat_no); // Signal to release access to seats
        printf("Barber is now cutting a customer hair.\n");
        sleep(rand() % 5); // Simulate hair cutting, it may differ customer to customer , for better simulation
        printf("Barber is done cutting.\n");
    }
}

void *customer(void *arg) {
    int id = *((int *)arg);
    sem_wait(&access_seat_no); 
    if (free_seats_no > 0) {
        free_seats_no--; // Sit down in a free seat
        printf("Customer %d is waiting on Free seats, # of free seats: %d\n", id, free_seats_no);
        sem_post(&customer_is_ready); 
        sem_post(&access_seat_no); // Signal to release access to seats
        sem_wait(&barber_is_ready); // Wait for the barber
        printf("Customer no %d is now getting a haircut.\n", id);
    } else {
        printf("There are no free seats -> customer no %d is now leaving.\n", id);
        sem_post(&access_seat_no); // Signal to release access to seats
    }
    free(arg);
    return NULL;
}

int main() {

    // inputs
    int customers_no;
    printf("# customers: ");
    scanf("%d", &customers_no);
    printf("# free chairs: %d\n", free_seats_no);


    pthread_t barber_thread;
    pthread_t customer_threads[customers_no];

    sem_init(&barber_is_ready, 0, 0);
    sem_init(&customer_is_ready, 0, 0);
    sem_init(&access_seat_no, 0, 1);


    pthread_create(&barber_thread, NULL, barber, NULL);

    for (int i = 0; i < customers_no; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&customer_threads[i], NULL, customer, (void *)id);
        sleep(rand() % 3); //time interval between each customer
    }

    for (int i = 0; i < customers_no; i++) {
        pthread_join(customer_threads[i], NULL);
    }

    pthread_cancel(barber_thread); 
    pthread_join(barber_thread, NULL);

    sem_destroy(&barber_is_ready);
    sem_destroy(&customer_is_ready);
    sem_destroy(&access_seat_no);

    return 0;
}
