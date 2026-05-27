#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int num = 10;
  pid_t pid = fork();
  if (pid > 0) // parent
  {
    while (1) {
      printf("parent process: %d - num: %d\n", getpid(), num);
      sleep(1);
    }
  } else if (pid == 0) // child
  {
    while (1) {
      printf("child process: %d - num:%d\n", getpid(), num);
      num++;
      sleep(1);
    }
  }

  return 0;
}
