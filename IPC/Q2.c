#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#define N 3 // Rows in A
#define M 3 // Columns in A and rows in B
#define P 3 // Columns in B


void multiply(int row, int col, int (*A)[M], int (*B)[P], int (*C)[P], sem_t *sem) {
    int sum = 0;
    for (int k = 0; k < M; k++) {
        sum += A[row][k] * B[k][col];
    }
    // Enter critical section
    sem_wait(sem);
    C[row][col] = sum;
    sem_post(sem); 
}

int main() {

    int A[N][M] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    int B[M][P] = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };

    int shm_fd = shm_open("/matrix_shm", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(int) * (N * M + M * P + N * P));
    int (*shared)[P] = mmap(0, sizeof(int) * (N * M + M * P + N * P), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    int (*sharedA)[M] = (int (*)[M])shared;
    int (*sharedB)[P] = (int (*)[P])(shared + N);
    int (*sharedC)[P] = (int (*)[P])(shared + N + M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            sharedA[i][j] = A[i][j];
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            sharedB[i][j] = B[i][j];
        }
    }

    sem_t *sem = sem_open("/matrix_sem", O_CREAT, 0666, 1);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            if (fork() == 0) {
                multiply(i, j, sharedA, sharedB, sharedC, sem);
                exit(0);
            }
        }
    }

    for (int i = 0; i < N * P; i++) {
        wait(NULL);
    }
    
    printf("Result matrix C:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", sharedC[i][j]);
        }
        printf("\n");
    }

    // Clean up
    munmap(shared, sizeof(int) * (N * M + M * P + N * P));
    shm_unlink("/matrix_shm");
    sem_close(sem);
    sem_unlink("/matrix_sem");


    return 0;
}
