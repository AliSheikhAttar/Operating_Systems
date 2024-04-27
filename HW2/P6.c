#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#define PORT 8090       // http:localhost:8090
#define BUFFER_SIZE 1024
#define MAX_NUMBERS 100

typedef struct {
    int sock;
    struct sockaddr address;
    int addr_len;
} connection_t;

float calculate_mean(const char *sequence) {
    float sum = 0.0;
    int count = 0;

 
    char *token = strtok((char *)sequence, " ");
    while (token != NULL) {
   
        float number = atof(token);
  
        sum += number;
    
        token = strtok(NULL, " ");
        count++;
    }


    if (count > 0) {
        return sum / count;
    } 
}

float calculate_standard_deviation(const char *sequence, float mean) {
    float sum_squared_diff = 0.0;
    int count = 0;

    char *token = strtok((char *)sequence, " ");
    while (token != NULL) {

        float number = atof(token);

        float diff = number - mean;
        sum_squared_diff += diff * diff;

        token = strtok(NULL, " ");
        count++;
    }

    // Calculate the standard deviation
    if (count > 0) {
        return sqrt(sum_squared_diff / count);
    } else {
        return 0.0; // Avoid division by zero
    }
}

void *handle_connection(void *ptr) {
    connection_t *connection = (connection_t *)ptr;
    char* message = "Enter a sequence of numbers with decimals separated by spaces (e.g., 3.5 6 1.54): ";
    int shm_fd;
    float *derivations;

    // Open shared memory
    shm_fd = shm_open("derivations", O_CREAT | O_RDWR, 0666);
    if (shm_fd < 0) {
        perror("shm_open failed");
        close(connection->sock);
        free(connection);
        pthread_exit(NULL);
    }
    if (ftruncate(shm_fd, MAX_NUMBERS * sizeof(float)) == -1) {
        perror("ftruncate failed");
        close(shm_fd);
        close(connection->sock);
        free(connection);
        pthread_exit(NULL);
    }
    derivations = (float *)mmap(0, MAX_NUMBERS * sizeof(float),PROT_READ  | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (derivations == MAP_FAILED) {
        perror("mmap failed");
        close(shm_fd);
        close(connection->sock);
        free(connection);
        pthread_exit(NULL);
    }

    char buffer[BUFFER_SIZE] = {0};
    long valread;

    if (send(connection->sock, message, strlen(message), 0) == -1) {
        perror("send failed");
        goto cleanup;
    }

    valread = recv(connection->sock, buffer, BUFFER_SIZE, 0);
    if (valread > 0) {
        printf("Received sequence: %s\n", buffer);


       
        float mean = calculate_mean(buffer);

        // Fork a child process for each number to calculate standard deviation
        int child_count = 0;
        char *token = strtok(buffer, " ");
        while (token != NULL) {
            float number = atof(token);
            int pid = fork();
            if (pid < 0) {
                perror("Fork failed");
                break;
            } else if (pid == 0) { // Child process
                float deviation = calculate_standard_deviation(token, mean);
                derivations[child_count] = deviation;
                exit(0);
            } else { // Parent process
                child_count++;
            }
            token = strtok(NULL, " ");
        }

        // Wait for all child processes to finish
        for (int i = 0; i < child_count; i++) {
            if (wait(NULL) == -1) {
                perror("wait failed");
            }
        }

        float sum_deviation = 0.0;
        for (int i = 0; i < child_count; i++) {
            sum_deviation += derivations[i];
        }

        // Send sum of deviations to client
        char sum_message[50];
        snprintf(sum_message, sizeof(sum_message), "Sum of deviations: %.2f\n", sum_deviation);
        if (send(connection->sock, sum_message, strlen(sum_message), 0) == -1) {
            perror("send failed");
        }


        sleep(3);

       
        if (send(connection->sock, "Standard deviations calculated & saved.\n", strlen("Standard deviations calculated & saved.\n"), 0) == -1) {
            perror("send failed");
        }
    } else {
        perror("Error receiving sequence");
    }

cleanup:
    // Close connection and clean memory
    close(connection->sock);
    free(connection);
    // Close shared memory
    if (munmap(derivations, MAX_NUMBERS * sizeof(float)) == -1) {
        perror("munmap failed");
    }
    if (close(shm_fd) == -1) {
        perror("close failed");
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
    int server_fd;
    connection_t *connection;
    struct sockaddr_in address;
    pthread_t t_id;

    // Create shared memory
    int shm_fd = shm_open("derivations", O_CREAT | O_RDWR, 0666);
    if (shm_fd < 0) {
        perror("shm_open failed");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(shm_fd, MAX_NUMBERS * sizeof(float)) == -1) {
        perror("ftruncate failed");
        exit(EXIT_FAILURE);
    }
    if (close(shm_fd) == -1) {
        perror("close failed");
        exit(EXIT_FAILURE);
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0) {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        connection = (connection_t *)malloc(sizeof(connection_t));
        connection->sock = accept(server_fd, &connection->address, &connection->addr_len);

        if (connection->sock < 0) {
            perror("In accept");
            free(connection);
            continue;
        }

        // Create a new thread for each connection
        if (pthread_create(&t_id, NULL, handle_connection, (void *)connection) != 0) {
            perror("Thread creation failed");
            close(connection->sock);
            free(connection);
        }
    }
    return 0;
}
