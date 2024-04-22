#include <stdio.h>
#include <unistd.h>

int main()
{
  int x = 10;
  int pid = fork();
  if(pid == 0){
    // child process
    x++;
  }
  else {
    // parent process
    sleep(1);
    printf("%d\n", x);
  }
}