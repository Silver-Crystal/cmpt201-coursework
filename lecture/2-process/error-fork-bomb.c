#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Before loop start\n");
  while (1) {
    sleep(1);
    if (fork() == -1) {
      char *str = NULL;
      switch (errno) {
      case EAGAIN:
        str = "EAGAIN";
        break;
      case ENOMEM:
        str = "ENOMEM";
        break;
      case ENOSYS:
        str = "ENOSYS";
        break;
      default:
        break;
      }
      perror("fork");
      printf("%s\n", str);
    }
  }
  return 0;
}
