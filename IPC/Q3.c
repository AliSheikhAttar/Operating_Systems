#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FIFO_WRITER_TO_READER "/tmp/fifo_writer_to_reader"
#define FIFO_READER_TO_LOGGER "/tmp/fifo_reader_to_logger"
#define BUFFER_SIZE 300

void reverseWords(char* str, char* reversed) {
    int length = strlen(str);
    int wordStart = length, wordEnd = length;
    int i, j = 0;

    for (i = length - 1; i >= 0; i--) {
        if (str[i] == ' ' || i == 0) {
            if (i == 0) {
                wordStart = i;
            } else {
                wordStart = i + 1;
            }
            while (wordStart < wordEnd) {
                reversed[j++] = str[wordStart++];
            }
            if (i > 0) {
                reversed[j++] = ' ';
            }
            wordEnd = i;
        }
    }
    reversed[j] = '\0';
}

void writer_process() {
    char input[BUFFER_SIZE];
    printf("Enter a message: ");
    fgets(input, BUFFER_SIZE, stdin);
    input[strcspn(input, "\n")] = '\0';  

    int fd = open(FIFO_WRITER_TO_READER, O_WRONLY);
    if (fd == -1) {
        perror("writer_process open");
        exit(EXIT_FAILURE);
    }
    write(fd, input, strlen(input) + 1);
    close(fd);
}

void reader_process() {
    int fd_reader = open(FIFO_WRITER_TO_READER, O_RDONLY);
    if (fd_reader == -1) {
        perror("reader_process open reader");
        exit(EXIT_FAILURE);
    }
    
    char buffer[BUFFER_SIZE];
    read(fd_reader, buffer, BUFFER_SIZE);
    close(fd_reader);

    char reversed[BUFFER_SIZE] = {0};
    reverseWords(buffer, reversed);
    printf("Reversed message: %s\n", reversed);

    int fd_logger = open(FIFO_READER_TO_LOGGER, O_WRONLY);
    if (fd_logger == -1) {
        perror("reader_process open logger");
        exit(EXIT_FAILURE);
    }
    write(fd_logger, reversed, strlen(reversed) + 1);
    close(fd_logger);
}

void logger_process() {
    int fd = open(FIFO_READER_TO_LOGGER, O_RDONLY);
    if (fd == -1) {
        perror("logger_process open");
        exit(EXIT_FAILURE);
    }
    
    char buffer[BUFFER_SIZE];
    read(fd, buffer, BUFFER_SIZE);
    close(fd);

    FILE *log_file = fopen("log.txt", "a");
    if (log_file == NULL) {
        perror("logger_process fopen");
        exit(EXIT_FAILURE);
    }
    fprintf(log_file, "%s\n", buffer);
    fclose(log_file);
}

int main() {
    // Create the FIFOs
    mkfifo(FIFO_WRITER_TO_READER, 0666);
    mkfifo(FIFO_READER_TO_LOGGER, 0666);

    if (fork() == 0) {
        // Child process - writer
        writer_process();
        exit(0);
    } else {
        if (fork() == 0) {
            // Child process - reader
            reader_process();
            exit(0);
        } else {
            if (fork() == 0) {
                // Child process - logger
                logger_process();
                exit(0);
            }
        }
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);

    unlink(FIFO_WRITER_TO_READER);
    unlink(FIFO_READER_TO_LOGGER);

    return 0;
}

