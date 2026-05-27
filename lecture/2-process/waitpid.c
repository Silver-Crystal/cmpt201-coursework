#include <stdio.h>
#include <unistd.h>

int main() {
  char *argv1[] = {"ls", ".", "-a"};

  pid_t pid = fork();
  if (pid == 0) {
    printf("Child process: sleep\n");
    sleep(3);
    exit();
    // int *p = NULL; // crashes segfault
    // char *argv2[] = {"-l", NULL};
    // execlp("/bin/ls", *argv1, *argv2);
    // execp("/bin/ls", *argv1, NULL);
  } else if (pid > 0) {
    int wstat;

    printf("parent process: wait for child process\n");

    if (waitpid(pid, &wstat, 0) == -1) {
      printf("perror\n");
      exit(EXIT_FAILURE);
    }
    if (WIFEXITED(wstatus) {
      printf("Child process exited normally
      printf("Status: %d", wstat);
    }
  }
  return 0;
}
