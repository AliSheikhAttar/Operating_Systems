#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>
#include </home/asa/Code/Git/Operating_systems/HW2/curl-8.7.1/include/curl/curl.h>
#include <sys/stat.h>
#include <string.h> // Include for strdup
#define THREAD_NUMS 6

void* download_link(void* arg) {
    char* url = (char*) arg;
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error initializing curl.\n");
        free(url); // Free allocated memory before returning
        return NULL;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);
    free(url); // Free allocated memory before returning
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <links_file> <download_directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* links_file_path = argv[1];
    const char* download_dir = argv[2];

    if (mkdir(download_dir, 0777) == -1) {
        perror("Error creating directory");
        return EXIT_FAILURE;
    }

    FILE* links_file = fopen(links_file_path, "r");
    if (!links_file) {
        perror("Error opening links file");
        return EXIT_FAILURE;
    }

    pthread_t threads[THREAD_NUMS];
    char link[256]; // Assuming max URL length is 255 characters

    int i = 0;
    while (fscanf(links_file, "%255s", link) == 1 && i < THREAD_NUMS) {
        char* link_copy = strdup(link); // Allocate memory for each thread
        if (!link_copy) {
            perror("Error duplicating link");
            return EXIT_FAILURE;
        }
        if (pthread_create(&threads[i], NULL, download_link, link_copy) != 0) {
            perror("Thread creation failed");
            free(link_copy); // Free memory if thread creation fails
            return EXIT_FAILURE;
        }
        i++;
    }

    for (int j = 0; j < i; j++) {
        if (pthread_join(threads[j], NULL) != 0) {
            perror("Thread joining failed");
            return EXIT_FAILURE;
        }
    }

    fclose(links_file);
    return EXIT_SUCCESS;
}
