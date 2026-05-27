#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char *line = NULL;
  size_t n = 0;
  while (1) {
    printf("Enter program to run: ");
    ssize_t len = getline(&line, &n, stdin);
    if (len == -1) {
      free(line);
      printf("\nNo program entered, exiting now :p\n");
      break;
    }
    printf("%s\n", line);

    line[len - 1] = '\0';

    printf("%s\n", line);

    pid_t pid = fork();
    if (pid == 0) // child
    {
      if (execl(line, line, NULL) == -1) {
        perror("execution of child process failed\n");
        free(line);
        exit(-1);
      }

    } else if (pid > 0) // parent
    {
      int status;
      if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        free(line);
        exit(-1);
      }
    }
  }
  return 0;
}
