#include <stdio.h>
#include <pthread.h>

void *thread_func(void *arg) {
    int *num = (int *)arg;
    printf("Thread: Hello, I received %d\n", *num);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    int arg = 42;

    // Create thread
    if (pthread_create(&tid, NULL, thread_func, &arg) != 0) {
        perror("pthread_create");
        return 1;
    }

    // Wait for thread to finish
    if (pthread_join(tid, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    printf("Main: Thread finished\n");

    return 0;
}
