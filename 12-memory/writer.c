

/* pshm_ucase_bounce.c

   Licensed under GNU General Public License v2 or later.
*/
#include <ctype.h>

#include "pshm_ucase.h"

int main(int argc, char *argv[]) {
  int fd;
  char *shmpath;
  // struct shmbuf *shmp;
  char *shmp;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s /shm-path\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  shmpath = argv[1];

  /* Create shared memory object and set its size to the size
     of our structure. */

  fd = shm_open(shmpath, O_CREAT | O_RDWR, 0600);
  if (fd == -1)
    errExit("shm_open");

  if (ftruncate(fd, sizeof(struct shmbuf)) == -1)
    errExit("ftruncate");

  /* Map the object into the caller's address space. */

  shmp = mmap(NULL, sizeof(char), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (shmp == MAP_FAILED)
    errExit("mmap");
  *shmp = 48;
#if 0
  /* Initialize semaphores as process-shared, with value 0. */

  if (sem_init(&shmp->sem1, 1, 0) == -1)
    errExit("sem_init-sem1");
  if (sem_init(&shmp->sem2, 1, 0) == -1)
    errExit("sem_init-sem2");

  /* Wait for 'sem1' to be posted by peer before touching
     shared memory. */

  if (sem_wait(&shmp->sem1) == -1)
    errExit("sem_wait");

  /* Convert data in shared memory into upper case. */

  for (size_t j = 0; j < shmp->cnt; j++)
    shmp->buf[j] = toupper((unsigned char)shmp->buf[j]);

  /* Post 'sem2' to tell the peer that it can now
     access the modified data in shared memory. */

  if (sem_post(&shmp->sem2) == -1)
    errExit("sem_post");

  /* Unlink the shared memory object. Even if the peer process
     is still using the object, this is okay. The object will
     be removed only after all open references are closed. */

  shm_unlink(shmpath);
#endif

  exit(EXIT_SUCCESS);
}

#if 0
/* pshm_ucase_send.c

   Licensed under GNU General Public License v2 or later.
*/
#include <string.h>

#include "pshm_ucase.h"

int main(int argc, char *argv[]) {
  int fd;
  char *shmpath, *string;
  size_t len;
  // struct shmbuf *shmp;
  char *shmp;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s /shm-path string\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  shmpath = argv[1];
#if 0
  string = argv[2];
  len = strlen(string);

  if (len > BUF_SIZE) {
    fprintf(stderr, "String is too long\n");
    exit(EXIT_FAILURE);
  }

  /* Open the existing shared memory object and map it
     into the caller's address space. */

#endif
  fd = shm_open(shmpath, O_CREAT | O_RDWR, 0600);
  if (fd == -1)
    errExit("shm_open");

  shmp = mmap(NULL, sizeof(*shmp), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (shmp == MAP_FAILED)
    errExit("mmap");

  /* Copy data into the shared memory object. */

  shmp->cnt = len;
  memcpy(&shmp->buf, string, len);

  /* Tell peer that it can now access shared memory. */

  if (sem_post(&shmp->sem1) == -1)
    errExit("sem_post");

  /* Wait until peer says that it has finished accessing
     the shared memory. */

  if (sem_wait(&shmp->sem2) == -1)
    errExit("sem_wait");

  /* Write modified data in shared memory to standard output. */

  write(STDOUT_FILENO, &shmp->buf, len);
  write(STDOUT_FILENO, "\n", 1);

  exit(EXIT_SUCCESS);
}
#endif
