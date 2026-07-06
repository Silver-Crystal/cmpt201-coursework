
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define ASSERT(expr)                                                                               \
  {                                                                                                \
    fprintf(stderr, "%s: Line %d\n", __FILE__, __LINE__);                                          \
    if (!(expr)) {                                                                                 \
      fprintf(stderr, "Assertion failed: %s\n", #expr);                                            \
      exit(1);                                                                                     \
    } else {                                                                                       \
      fprintf(stderr, "Assertion passed: %s\n", #expr);                                            \
    }                                                                                              \
  }

#define TEST(expr)                                                                                 \
  {                                                                                                \
    if (!(expr)) {                                                                                 \
      fprintf(stderr, "Test failed: %s\n", #expr);                                                 \
      exit(1);                                                                                     \
    } else {                                                                                       \
      printf("Test passed: %s\n", #expr);                                                          \
    }                                                                                              \
  }

typedef struct node {
  uint64_t data;
  struct node *next;
} node_t;

typedef struct info {
  uint64_t sum;
} info_t;

node_t *head = NULL;
info_t info = {0};

void insert_sorted(uint64_t data) {
  node_t *new_node = malloc(sizeof(node_t));
  new_node->data = data;
  new_node->next = NULL;

  if (head == NULL) {
    head = new_node;
  } else if (data < head->data) {
    new_node->next = head;
    head = new_node;
  } else {
    node_t *curr = head;
    node_t *prev = NULL;

    bool inserted = false;
    while (curr != NULL && !inserted) {
      if (data < curr->data) {
        if (prev == NULL) {
          head = new_node;
          new_node->next = curr;
        } else {
          prev->next = new_node;
          new_node->next = curr;
        }
        inserted = true;
      }
      prev = curr;
      curr = curr->next;
    }
    if (inserted == false) {
      prev->next = new_node;
    }
    if (curr != NULL && !inserted) {
      // new_node->next = curr->next;
      new_node->next = curr;
    }
  }
  info.sum += data;
}

int index_of(uint64_t data) {
  node_t *curr = head;
  int index = 0;

  while (curr != NULL) {
    if (curr->data == data) {
      return index;
    }

    curr = curr->next;
    index++;
  }

  return -1;
}

int sumList() {
  if (head == NULL) {
    return 0;
  }
  int sum = 0;
  node_t *curr = head;
  while (curr != NULL) {
    sum += curr->data;
    curr = curr->next;
  }
  return sum;
}
int main() {
  ASSERT(sumList() == info.sum);
  fprintf(stdout, "info.sum is: %lu\nsumList() is: %d\n", info.sum, sumList());
  insert_sorted(1);
  ASSERT(sumList() == info.sum);
  fprintf(stdout, "info.sum is: %lu\nsumList() is: %d\n", info.sum, sumList());
  insert_sorted(3);
  ASSERT(sumList() == info.sum);
  fprintf(stdout, "info.sum is: %lu\nsumList() is: %d\n", info.sum, sumList());
  insert_sorted(5);
  fprintf(stdout, "info.sum is: %lu\nsumList() is: %d\n", info.sum, sumList());
  ASSERT(sumList() == info.sum);
  insert_sorted(2);
  fprintf(stdout, "info.sum is: %lu\nsumList() is: %d\n", info.sum, sumList());
  ASSERT(sumList() == info.sum);

  TEST(info.sum == 1 + 3 + 5 + 2);
  TEST(index_of(2) == 1);

  fprintf(stdout, "info.sum is: %lu\nsumList() is: %d\n", info.sum, sumList());
  ASSERT(sumList() == info.sum);
  return 0;
}
