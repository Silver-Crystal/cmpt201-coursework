#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
static pthread_mutex_t A = PTHREAD_MUTEX_INITIALIZER;

static pthread_mutex_t B = PTHREAD_MUTEX_INITIALIZER;

// static void *func(void *arg) { pthread_exit(0); }

static void *thread0(void *arg) {
  pthread_mutex_lock(&A);
  printf("0: mutex A\n");
  pthread_mutex_lock(&B);
  printf("0: mutex B\n");
  pthread_mutex_unlock(&B);
  printf("0: mutex unlock B\n");
  pthread_mutex_unlock(&A);
  printf("0: mutex unlock A\n");
  printf("Thread 0 finish.\n");
  pthread_exit(NULL);
}

static void *thread1(void *arg) {
  pthread_mutex_lock(&B);
  printf("1: mutex B\n");
  pthread_mutex_lock(&A);
  printf("1: mutex A\n");
  pthread_mutex_unlock(&A);
  printf("1: mutex unlock A\n");
  pthread_mutex_unlock(&B);
  printf("1: mutex unlock B\n");
  printf("Thread 1 finish.\n");
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t t0;
  pthread_t t1;
  if (pthread_create(&t0, NULL, thread0, NULL) != 0)
    perror("pthread_create 0");

  if (pthread_create(&t1, NULL, thread1, NULL) != 0)
    perror("pthread_create 1");

  if (pthread_join(t0, NULL) != 0)
    perror("pthread_join 0");
  if (pthread_join(t1, NULL) != 0)
    perror("pthread_join 1");

  // pthread_create(&t1, NULL, func, NULL);

  // pthread_join(t1, NULL);
  exit(EXIT_SUCCESS);
}
