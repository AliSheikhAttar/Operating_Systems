#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 10

struct ThreadData {
    int *arr;
    int start;
    int end;
    int max;
};

void* threadFunction(void* arg) {
    struct ThreadData* data = (struct ThreadData*) arg;
    int max = data->arr[data->start];
    for (int i = data->start + 1; i < data->end; i++) {
        if (data->arr[i] > max)
            max = data->arr[i];
    }
    data->max = max;
    return NULL;
}

void sort(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, m;
    printf("Enter the size of the array (n): ");
    scanf("%d", &n);
    printf("Enter the number of partitions (m): ");
    scanf("%d", &m);

    if (m > n) {
        printf("Error: Number of partitions cannot exceed the size of the array.\n");
        return 1;
    }

    int *array = (int *)malloc(n * sizeof(int));
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    pthread_t threads[MAX_THREADS];
    struct ThreadData threadData[MAX_THREADS];

    int partitionSize = n / m;
    int remainingElements = n % m;
    int startIndex = 0;
    for (int i = 0; i < m; i++) {
        int partitionEnd = startIndex + partitionSize + (i < remainingElements ? 1 : 0);

        threadData[i].arr = array;
        threadData[i].start = startIndex;
        threadData[i].end = partitionEnd;

        pthread_create(&threads[i], NULL, threadFunction, &threadData[i]);

        startIndex = partitionEnd;
    }

    for (int i = 0; i < m; i++) {
        pthread_join(threads[i], NULL);
    }

    int *max_values = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        max_values[i] = threadData[i].max;
    }

    sort(max_values, m);

    printf("Maxes descending order :\n");
    for (int i = 0; i < m; i++) {
        printf("%d\n", max_values[i]);
    }

    free(array);
    free(max_values);

    return 0;
}
