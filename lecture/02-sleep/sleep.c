#include <stdio.h>
#include <unistd.h>

int main() {

  int i = 0;
  printf("Starting program\n");
  while (1) {
    sleep(1);
    i++;
    printf("Take a nap, %d \n", i);
  }
  return 0;
}
