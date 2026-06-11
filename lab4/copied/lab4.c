#define _DEFAULT_SOURCE
#define _ISO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct header { // takes 16  bytes, then 12 bytes after header
  unit64_t size;
  struct header *next;
} header;
void handle_error(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  uint64_t val;
  memcpy(&val, data, data_size);
  ssize_t len = snprintf(buf, BUF_SIZE, format, val);
  if (len < 0) {
    handle_error("snprintf);
  }
  write(STDOUT_FILENO, buf, len);
}

void print_block(char *start) {
  for (int i = 0; i < BLOCK_SIZE - sizeof(struct header); ++i) {
    char *addr = (start + sizeof

void initial(struct header *in, int val) {
      void *start = in; }
int main() {
      void *old_program_break = sbrk(256);
      struct header *blockOne = (struct header *)old_program_break;
      // struct header blockOne, blockTwo ;
      blockOne->size = 128;
      blockOne->next = NULL;
      struct header *blockTwo = (struct header *)(old_program_break + blockOne->size);
      blockTwo->size = 128;
      blockTwo->next = old_program_break;
}
