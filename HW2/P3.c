#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define SIZE 100
#define THREAD_NUMS 5

double numbers[SIZE];
double sums[THREAD_NUMS];
pthread_mutex_t lock;


void* calculatePartialSum(void* arg) {
    int start = *((int*)arg);
    int step = SIZE / THREAD_NUMS;
    int end = (start + 1) * step;

    double partialSum = 0;
    for (int i = start * step; i < end; i++) {
        partialSum += numbers[i];
    }

    pthread_mutex_lock(&lock);
    sums[start] = partialSum;
    pthread_mutex_unlock(&lock);

    return NULL;
}


double calculateAverage() {
    double totalSum = 0;
    for (int i = 0; i < THREAD_NUMS; i++) {
        totalSum += sums[i];
    }
    return totalSum / SIZE;
}


void generateNumbersFile(const char* filename) {

    char touch_command[100];
    sprintf(touch_command, "touch %s", filename);
    if (system(touch_command) == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }


    srand(time(NULL));


    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < SIZE; i++) {
        double randomNumber = (double)rand() / RAND_MAX; // Generate a random number between 0 and 1
        fprintf(file, "%.2f\n", randomNumber);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    const char* dir_name =  argv[1];
    const char* numbers_filename = "numbers.txt";


    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("Mutex initialization failed");
        exit(EXIT_FAILURE);
    }


    generateNumbersFile(numbers_filename);


    FILE* numbers_file = fopen(numbers_filename, "r");
    if (numbers_file == NULL) {
        perror("Error opening numbers file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < SIZE; i++) {
        if (fscanf(numbers_file, "%lf", &numbers[i]) != 1) {
            fprintf(stderr, "Error reading from file\n");
            exit(EXIT_FAILURE);
        }
    }
    fclose(numbers_file);


    pthread_t threads[THREAD_NUMS];
    int threadArgs[THREAD_NUMS];
    for (int i = 0; i < THREAD_NUMS; i++) {
        threadArgs[i] = i;
        if (pthread_create(&threads[i], NULL, calculatePartialSum, (void*)&threadArgs[i]) != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
    }


    for (int i = 0; i < THREAD_NUMS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Thread joining failed");
            exit(EXIT_FAILURE);
        }
    }


    double average = calculateAverage();


    pid_t pid = fork();

    if (pid == -1) {
        perror("Error in forking process");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { 

        if (mkdir(dir_name, 0777) == -1) {
            perror("Error creating directory");
            exit(EXIT_FAILURE);
        }
        
        if (chdir(dir_name) == -1) {
            perror("Error changing directory");
            exit(EXIT_FAILURE);
        }

        const char* student_id = "99542222"; 
        FILE* outfile = fopen(student_id, "w");
        if (outfile == NULL) {
            perror("Error creating file");
            exit(EXIT_FAILURE);
        }
        fprintf(outfile, "Average: %.2f\n", average);
        fclose(outfile);

        exit(EXIT_SUCCESS);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }


    pthread_mutex_destroy(&lock);

    return 0;
}
