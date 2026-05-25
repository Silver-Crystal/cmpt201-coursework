
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  char *message = "Hello world!\n";
  for (int i = 0; i < strlen(message); i++) {
    printf("%c", message[i]);
    fflush(stdout);
    sleep(2);
  }
  printf("\n");
  printf("Done\n");
}
