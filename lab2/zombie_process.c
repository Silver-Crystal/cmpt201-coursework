#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  pid_t pid = fork();
  if (pid == 0) // child
  {
    printf("Child PID:%d\n", getpid());
    _exit(-1);
  } else // parent process
  {
    printf("parent PID:%d\n", getpid());
    getchar();
  }
  return 0;
}
