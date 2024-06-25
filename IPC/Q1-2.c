#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

#define FIFO_NAME "/tmp/my_os_ta_fifo"
#define BUFFER_SIZE 300

void writer_process(const char *message) {
    int fd = open(FIFO_NAME, O_WRONLY);
    write(fd, message, strlen(message) + 1);
    close(fd);
}

void reader_process() {
    int fd = open(FIFO_NAME, O_RDONLY);
    char buffer[BUFFER_SIZE];
    while (read(fd, buffer, BUFFER_SIZE) > 0) {
        printf("Received: %s\n", buffer);
    }
    close(fd);
}

int main() {
    // Create the FIFO
    mkfifo(FIFO_NAME, 0666);

    if (fork() == 0) {
        // Child process - writer
        writer_process("Hello from child!");
        exit(0);
    } else {
        // Parent process - reader
        reader_process();
        // Remove the FIFO
        unlink(FIFO_NAME);
    }

    return 0;
}
