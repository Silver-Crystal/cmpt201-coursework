#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define handle_error(msg)                                                                          \
  do {                                                                                             \
    perror(msg);                                                                                   \
    exit(EXIT_FAILURE);                                                                            \
  } while (0)

int main(int argc, char *argv[]) {
  int fd;
  char *addr;
  char *addr2;
  // off_t offset, pa_offset;
  // size_t length;
  ssize_t s;
  ssize_t s2;
  struct stat sb;

  if (argc < 2 || argc > 3) {
    fprintf(stderr, "%s file offset [length]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  fd = open(argv[1], O_RDONLY);
  if (fd == -1)
    handle_error("open");

  if (fstat(fd, &sb) == -1) /* To obtain file size */
    handle_error("fstat");
#if 0
  offset = atoi(argv[2]);
  pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
  /* offset for mmap() must be page aligned */

  if (offset >= sb.st_size) {
    fprintf(stderr, "offset is past end of file\n");
    exit(EXIT_FAILURE);
  }

  if (argc == 4) {
    length = atoi(argv[3]);
    if (offset + length > sb.st_size)
      length = sb.st_size - offset;
    /* Can't display bytes past end of file */

  } else { /* No length arg ==> display to end of file */
    length = sb.st_size - offset;
  }

#endif

  addr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  addr2 = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, STDOUT_FILENO, 0);
  if (addr == MAP_FAILED)
    handle_error("mmap");
  memcpy(addr2, addr, sb.st_size);
  // s = write(STDOUT_FILENO, addr, sb.st_size);
  //  can we map stdout to the memory and then write to it.
  //  hehe
  if (s != sb.st_size) {
    if (s == -1)
      handle_error("write");

    fprintf(stderr, "partial write");
    exit(EXIT_FAILURE);
  }

  munmap(addr, sb.st_size);
  close(fd);

  exit(EXIT_SUCCESS);
}
