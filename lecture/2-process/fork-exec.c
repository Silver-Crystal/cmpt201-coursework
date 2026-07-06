#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Hi\n");
  fork();
  char *argv[] = {"ls", " ", NULL};
  execlp("/bin/ls", *argv);
  printf("Bye\n");
  return 0;
}
