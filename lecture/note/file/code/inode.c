#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  struct stat sb;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  if (stat(argv[1], &sb) == -1) {
    perror("lstat");
    exit(EXIT_FAILURE);
  }

  //  ino_t st_ino = sb.st_ino;
  // mode_t st_mode = sb.st_mode;
  if (S_ISREG(sb.st_mode)) {
    printf("Regular file\n");
  } else if (S_ISDIR(sb.st_mode)) {
    printf("Directory\n");
  } else {
    printf("Other\n");
  }
  return 0;
}
