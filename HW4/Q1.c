#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct {
    int start;
    int end;
    double psum;
} ThreadData;

void* compute_seq(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    data->psum = 0.0;

    for (int i = data->start; i < data->end; ++i) {
        double factorial = 1.0;
        for (int j = 1; j <= i; ++j) {
            factorial *= j;
        }
        data->psum += 1.0 / factorial;
    }

    pthread_exit(NULL);
}
int main() {
    // inputs
    int terms_no;
    printf("# terms: ");
    scanf("%d", &terms_no);

    int threads_no;
    printf("# threads: ");
    scanf("%d", &threads_no);


    pthread_t* threads = (pthread_t*) malloc(threads_no * sizeof(pthread_t));
    ThreadData* thread_data = (ThreadData*) malloc(threads_no * sizeof(ThreadData));
    int range_per_thread = terms_no / threads_no;
    int remain_range = terms_no - range_per_thread*threads_no;
    double total_sum = 0.0;

    for (int i = 0; i < threads_no-1; ++i) {
        thread_data[i].start = i * range_per_thread + 1;
        thread_data[i].end = (i + 1) * range_per_thread + 1;
        pthread_create(&threads[i], NULL, compute_seq, (void*)&thread_data[i]);
    }

    // Last range

    int end = (remain_range > 0) ? (terms_no + 1) : (threads_no* range_per_thread + 1);
    thread_data[threads_no-1].start = (threads_no-1) * range_per_thread + 1;
    thread_data[threads_no-1].end = end;
    pthread_create(&threads[threads_no-1], NULL, compute_seq, (void*)&thread_data[threads_no-1]);

    for (int i = 0; i < threads_no; ++i) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].psum;
    }


    printf("result of the calculation of the sequence: %f\n", total_sum);

    free(threads);
    free(thread_data);

    return 0;
}
