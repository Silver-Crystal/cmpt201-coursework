#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Before fork\n");

  fork();

  printf("Before loop start\n");

  for (int i = 0; i < 10; i++) {
    sleep(1);
    printf("Take %d nam\n", i);
  }
  printf("Done\n");
  return 0;
}
