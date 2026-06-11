#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct header { // takes 16  bytes, then 12 bytes after header
  uint64_t size;
  struct header *next;
} header;

void initial(struct header *in, int val); // initialises strucht header with value val
void print_block_bytes(struct header *in);
void given_print_out(char *format, void *data, size_t data_size);
int main() {
  void *old_program_break = sbrk(256);
  struct header *blockOne = (struct header *)old_program_break;
  // struct header blockOne, blockTwo ;
  blockOne->size = 128;
  blockOne->next = NULL;
  struct header *blockTwo = (struct header *)(old_program_break + blockOne->size);
  blockTwo->size = 128;
  blockTwo->next = old_program_break;
  initial(blockOne, 0);
  initial(blockTwo, 1);

  printf("first block:        %p\n", blockOne);
  printf("second block:       %p\n", blockTwo);
  printf("first block size:   %lu\n", blockOne->size);
  printf("first block next:   %p\n", blockOne->next);
  printf("second block size:  %lu\n", blockTwo->size);
  printf("sedond block next:  %p\n", blockTwo->next);
  print_block_bytes(blockOne);
  given_print_out(
  //given_print_out("
  print_block_bytes(blockTwo);
}

#define BUF_SIZE 128 - sizeof(struct header)
void given_print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len =
      snprintf(buf, BUF_SIZE, format,
               data_size == (size_t)sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    perror("snprintf");
    exit(1);
    // handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

void print_block_bytes(struct header *in) {
  ssize_t writtenBytes =
      write(1, ((char *)(in)) + sizeof(struct header), in->size - sizeof(struct header));
  if (writtenBytes < (in->size - sizeof(struct header))) {
    perror("Bytes not written properly!");
    exit(1);
  }
  return;
}

void initial(struct header *in, int val) {
  void *start = in;
  /*char *after = (char *)(start + sizeof(struct header));

  for (int i = 0; i < size; ++i) {
    after[i] = val;
  }
  */
  memset(start + sizeof(struct header), 0, in->size - sizeof(struct header));

  return;
}
