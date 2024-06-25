#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

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

    int fd;
    while ((fd = open(FIFO_WRITER_TO_READER, O_WRONLY | O_NONBLOCK)) == -1) {
        if (errno == ENXIO || errno == EAGAIN) {
            usleep(500000); // 0.5 second delay
        } else {
            perror("writer_process open");
            exit(EXIT_FAILURE);
        }
    }
    write(fd, input, strlen(input) + 1);
    close(fd);
}

void reader_process() {
    int fd_reader;
    while ((fd_reader = open(FIFO_WRITER_TO_READER, O_RDONLY | O_NONBLOCK)) == -1) {
        if (errno == ENXIO || errno == EAGAIN) {
            usleep(500000); // 0.5 second delay
        } else {
            perror("reader_process open reader");
            exit(EXIT_FAILURE);
        }
    }
    
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    while ((bytes_read = read(fd_reader, buffer, BUFFER_SIZE)) == -1) {
        if (errno == EAGAIN) {
            usleep(500000); // 0.5 second delay
        } else {
            perror("reader_process read");
            close(fd_reader);
            exit(EXIT_FAILURE);
        }
    }
    buffer[bytes_read] = '\0'; // Null-terminate the string
    close(fd_reader);

    char reversed[BUFFER_SIZE] = {0};
    reverseWords(buffer, reversed);
    printf("Reversed message: %s\n", reversed);

    int fd_logger;
    while ((fd_logger = open(FIFO_READER_TO_LOGGER, O_WRONLY | O_NONBLOCK)) == -1) {
        if (errno == ENXIO || errno == EAGAIN) {
            usleep(500000); // 0.5 second delay
        } else {
            perror("reader_process open logger");
            exit(EXIT_FAILURE);
        }
    }
    write(fd_logger, reversed, strlen(reversed) + 1);
    close(fd_logger);
}

void logger_process() {
    int fd;
    while ((fd = open(FIFO_READER_TO_LOGGER, O_RDONLY | O_NONBLOCK)) == -1) {
        if (errno == ENXIO || errno == EAGAIN) {
            usleep(500000); // 0.5 second delay
        } else {
            perror("logger_process open");
            exit(EXIT_FAILURE);
        }
    }
    
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) == -1) {
        if (errno == EAGAIN) {
            usleep(500000); // 0.5 second delay
        } else {
            perror("logger_process read");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }
    buffer[bytes_read] = '\0'; // Null-terminate the string
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

    pid_t writer_pid = fork();
    if (writer_pid == 0) {
        writer_process();
        exit(0);
    } else if (writer_pid == -1) {
        perror("fork writer");
        exit(EXIT_FAILURE);
    }

    pid_t reader_pid = fork();
    if (reader_pid == 0) {
        reader_process();
        exit(0);
    } else if (reader_pid == -1) {
        perror("fork reader");
        exit(EXIT_FAILURE);
    }

    pid_t logger_pid = fork();
    if (logger_pid == 0) {
        logger_process();
        exit(0);
    } else if (logger_pid == -1) {
        perror("fork logger");
        exit(EXIT_FAILURE);
    }

    // Wait for child processes to finish
    waitpid(writer_pid, NULL, 0);
    waitpid(reader_pid, NULL, 0);
    waitpid(logger_pid, NULL, 0);

    // Remove the FIFOs
    unlink(FIFO_WRITER_TO_READER);
    unlink(FIFO_READER_TO_LOGGER);

    return 0;
}
