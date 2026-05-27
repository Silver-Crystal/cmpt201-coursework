#include <stdio.h>
#include <unistd.h>

int main() {
  int a = 0;
  a++;
  fork();
  a++;
  fork();
  a++;
  printf("%d\n", a);
  return 0;
}
