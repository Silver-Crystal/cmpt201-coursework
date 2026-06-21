#define _GNU_SOURCE

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int len = 0;

void *thread(void *args) {
  char *arprint = (char *)args;
  len = strlen(arprint);
  printf("Message is: %s\n", arprint);
  printf("Thread ID is: %d\n", gettid());

  return (void *)&len;
  return (void *)(long long)strlen(arprint);
  return NULL;
}

int main() {
  void *result;
  pthread_t mythread;
  int ret = pthread_create(&mythread, NULL, thread, "Hello from main thread.");

  pthread_join(mythread, &result);
  // long long size = (long long)result;

  printf("Min: the return value is: %lld\n", size);
  return 0;
}
