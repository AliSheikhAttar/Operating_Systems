#include <stdio.h>
#include <stdlib.h>   // For exit()
#include <unistd.h>   // For fork(), getpid(), and sleep()
#include <sys/wait.h> // For wait()

int main() {
    int number = 10;
    
    int f1 = fork();
    if (f1 == 0) {
        printf("I'm the child and my pid is %d\n", getpid());
        number++;
        printf("my number id: %d\n", number);
        exit(0);
    } else {
        printf("I'm the parent and my pid is %d\n", getpid());
        printf("mu number is: %d\n", number);

        wait(NULL);
        printf("Child process finished.\n");
    }
    return 0;
}
