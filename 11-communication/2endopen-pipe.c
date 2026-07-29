
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// create two pipes
//

int main(int argc, char *argv[]) {

  //
  int pipefd[2];
  // int pipefd2[2];
  char buf;
  char buf2;
  pid_t cpid;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <string>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
#if 0
  if (pipe(pipefd2) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
#endif
  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (cpid == 0) {
    // child reads from pipe, and writes to pipe2
    //    close(pipefd[1]);
    //   close(pipefd2[0]);

    while (read(pipefd[0], &buf, 1) > 0) {
      buf = toupper(buf);
      write(pipefd[0], &buf, 1);
    }

    // close(pipefd2[1]);
    close(pipefd[0]);
    close(pipefd[1]);

    _exit(EXIT_SUCCESS);
  } else {
    close(pipefd[0]);
    // close(pipefd2[1]);
    write(pipefd[1], argv[1], strlen(argv[1]));
    close(pipefd[1]);
    while (read(pipefd[0], &buf2, 1) > 0)
      write(STDOUT_FILENO, &buf2, 1);
    write(STDOUT_FILENO, "\n", 1);
    // close(pipefd2[0]);
    close(pipefd[1]);
    close(pipefd[0]);
    wait(NULL);
    exit(EXIT_SUCCESS);
    return 0;
  }
}
