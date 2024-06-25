#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2]; 
    char message[] = "msg az pedar";
    char buffer[100];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        
        close(pipefd[1]); 

        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer));
        if (bytesRead == -1) {
            perror("read");
            return 1;
        }

        buffer[bytesRead] = '\0';
        printf("Child received: %s\n", buffer);

        close(pipefd[0]); 
    } else {
        
        close(pipefd[0]); 

        ssize_t bytesWritten = write(pipefd[1], message, strlen(message));
        if (bytesWritten == -1) {
            perror("write");
            return 1;
        }

        close(pipefd[1]);

        wait(NULL); 
    }

    return 0;
}

