#define _GNU_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/stat.h>

#define MAX_PATH_LENGTH 1024
#define MAX_THREADS 10

char filename[MAX_PATH_LENGTH]; 
int flag = 0; 

void *searchFile(void *arg) {
    char *search_path = (char *)arg;
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(search_path)) == NULL) {
        // perror("opendir");
        pthread_exit(NULL);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (strcmp(entry->d_name, filename) == 0) {
            printf("File found: %s/%s\n", search_path, entry->d_name);
            flag = 1;
        }

        if (entry->d_type == DT_DIR) {
            char new_path[MAX_PATH_LENGTH];
            snprintf(new_path, sizeof(new_path), "%s/%s", search_path, entry->d_name);

            pthread_t thread;
            pthread_create(&thread, NULL, searchFile, (void *)new_path);
            pthread_join(thread, NULL); 
        }
    }

    closedir(dir);
    pthread_exit(NULL);
}

int main() {
    printf("Enter the filename to search: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0'; 

    pthread_t main_thread;
    pthread_create(&main_thread, NULL, searchFile, "/home/asa/Code/"); // enter address

    pthread_join(main_thread, NULL);

    if (flag == 0) {
        printf("No directory or file found.\n");
    }

    return 0;
}
