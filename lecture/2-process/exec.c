#include <stdio.h>
#include <unistd.h>

int main() {
  char *argv1[] = {"ls", ".", "-a"};

  pid_t pid = fork();
  if (pid == 0) {
    execp("/bin/ls", *argv1, NULL);
  } else {
    char *argv2[] = {"-l", "-h", NULL};
    execlp("/bin/ls", *argv1, *argv2);
  }
  return 0;
}
