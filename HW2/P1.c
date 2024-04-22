#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 

int calculateMax(int *arr, int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

void childProcess(int *arr, int start, int end) {
    int max = calculateMax(arr + start, end - start);
    printf("Max in section [%d, %d] is: %d\n", start, end, max);
    exit(max); 
}

int main() {
    int n, m;
    printf("Enter the size of the array (n): ");
    scanf("%d", &n);
    printf("Enter the number of partitions (m): ");
    scanf("%d", &m);

    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

   
    for (int i = 0; i < m; i++) {
        pid_t pid = vfork();
        if (pid == 0) { 
            int start = (n / m) * i; 
            int end = (i == m - 1) ? n : (n / m) * (i + 1); 
            childProcess(arr, start, end);
        } else if (pid < 0) {
            printf("Error in creating child process.\n");
            exit(1);
        }
    }

    int *max_values = (int *)malloc(m * sizeof(int));
    printf("Max values in each section:\n");
    for (int i = 0; i < m; i++) {
        int status;
        wait(&status); 
        max_values[i] = WEXITSTATUS(status);
    }


    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            if (max_values[j] < max_values[j + 1]) {
                int temp = max_values[j];
                max_values[j] = max_values[j + 1];
                max_values[j + 1] = temp;
            }
        }
    }

  
    printf("Maxes in descending order :\n");
    for (int i = 0; i < m; i++) {
        printf("%d\n", max_values[i]);
    }

    free(arr);
    free(max_values);
    return 0;
}
