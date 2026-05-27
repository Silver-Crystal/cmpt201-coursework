
#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Before fork\n");

  fork();

  printf("Before loop start\n");

  while () {
    fork();
    sleep(1);
    printf("Take %d nam\n", i);
  }
  printf("Done\n");
  return 0;
}
