// string tokenizer, takes in a line via getline(through stdin) and then uses strtok_r to tokenize
// Silver-Crystal
// Ifixit
// 2026/05/25
// used https://opencoursehub.cs.sfu.ca/cmpt201/grav/labs/lab1-getline as reference
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>

#include <stdlib.h>

int main(void) {
  printf("Entered main\n");
  char *line1 = NULL;
  size_t len1 = 0;
  ssize_t nread;

  printf("Calling getline\n");
  nread = getline(&line1, &len1, stdin);
  printf("Returned from getline\n");
  if (nread == -1) {
    perror("getline failed\n");
    exit(EXIT_FAILURE);
  }
  printf("print line and length\n");
  printf("Read line of length %zd:\n", nread);
  printf("Print line time, calling fwrite\n");
  fwrite(line1, nread, 1, stdout);

  char *saveptr;
  char *ret = strtok_r(line1, " ", &saveptr);
  if (ret == NULL)
    return 0;
  else if (ret == -1) {
    perror("first call on srtok_r failed\n");
    exit(EXIT_FAILURE);
  }
  printf("%s\n", ret);
  char *ret2 = NULL;

  while (1) {
    ret2 = strtok_r(NULL, " ", &saveptr);
    if (ret2 == NULL)
      break;
    else if (ret2 == -1) {
      perror("srtok_r failed\n");
      exit(EXIT_FAILURE);
    }
    printf("%s\n", ret2);
  }

  free(line1);
  printf("Hello World.\n");
  return 0;
}
