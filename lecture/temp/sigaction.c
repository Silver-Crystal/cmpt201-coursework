#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *message = "CTRL-C Pressed\n";

void our_defined_sigint_handler(int signum) { write(STDOUT_FILENO, message, strlen(message)); }

int main() {

  struct sigaction oldact = {0};

  oldact.sa_handler = &our_defined_sigint_handler;
  oldact.sa_flags = 0;          // No special flags;
  sigemptyset(&oldact.sa_mask); // intiialises the signal set given by set to empty

  int ret = sigaction(SIGINT, &oldact, NULL);
  // int ret = sigaction(SIGINT, NULL, NULL);

  if (ret == -1) {
    perror("Sigaction() failed");
    exit(EXIT_FAILURE);
  }

  printf("Press CTRL-C to trigger the signal handler...\n");

  while (1) {
    sleep(4);
  }
  return 0;
}
