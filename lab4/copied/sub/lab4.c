// check cmpt201-coursework repo, cmpt201-coursework/lab4/copied/mix.c and
// cmpt201-coursework/lab4/lab4.c for reference to my other code
#define _DEFAULT_SOURCE
#define _ISOC99_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BLOCK_SIZE 128
#define HEAP_SIZE 256
#define BUF_SIZE 64

typedef struct header { // takes 16  bytes, then 12 bytes after header
  uint64_t size;
  struct header *next;
} header;

void handle_error(const char *msg);
void given_initial(struct header *in, uint64_t size, struct header *next, int fill_value);
void initial(struct header *in, int val); // initialises strucht header with value val
void print_block_bytes(struct header *in);
void given_print_out(char *format, void *data, size_t data_size);
void given_print_block(char *start);
int main() {
  char *heap_start = (char *)sbrk(0);
  if (sbrk(HEAP_SIZE) == (void *)-1) {
    handle_error("sbrk");
  }
  struct header *blockOne = (struct header *)heap_start;

  struct header *blockTwo = (struct header *)(heap_start + BLOCK_SIZE);
  given_initial(blockOne, BLOCK_SIZE, NULL, 0);
  given_initial(blockTwo, BLOCK_SIZE, blockOne, 1);
  given_print_out("first block:        %p\n", &blockOne, sizeof(blockOne));
  given_print_out("second block:       %p\n", &blockTwo, sizeof(blockTwo));
  given_print_out("first block size:   %lu\n", &blockOne->size, sizeof(blockOne->size));
  given_print_out("first block next:   %p\n", &blockOne->next, sizeof(blockOne->next));
  given_print_out("second block size:  %lu\n", &blockTwo->size, sizeof(blockTwo->size));
  given_print_out("second block next:  %p\n", &blockTwo->next, sizeof(blockTwo->next));
  given_print_block((char *)blockOne);
  given_print_block((char *)blockTwo);

  return 0;
}

void given_print_block(char *start) {
  for (int i = 0; i < BLOCK_SIZE - sizeof(struct header); ++i) {
    char *addr = (start + sizeof(struct header) + i);
    uint64_t val = (uint64_t)*addr;
    given_print_out("%lu\n", &val, sizeof(val));
  }
}

void given_print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  uint64_t val;
  memcpy(&val, data, data_size);
  ssize_t len =
      snprintf(buf, BUF_SIZE, format,
               data_size == (size_t)sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

void given_initial(struct header *in, uint64_t size, struct header *next, int fill_value) {
  in->size = size;
  in->next = next;
  memset(in + 1, fill_value, size + sizeof(struct header));
}

void handle_error(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}
