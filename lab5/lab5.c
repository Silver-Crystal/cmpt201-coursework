// github.com/Silver-Crystal/cmpt201-coursework/tree/lab1/lab5/lab5.c
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/// Jneed to implement :
// # first-fit block selection
// # best fit
// # worst fit
struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}
void zero(struct header *cur_head) {
  cur_head->size = 0;
  cur_head->next = NULL;
  cur_head->id = 0;
  free(cur_head);
}
void free_list(struct header *free_list_ptr) {
  struct header *temp = free_list_ptr;
  if (temp == NULL) {
    return;
  }
  // for (; temp->next != NULL; temp=temp->next) {
  //}
  while (temp->next != NULL) {

    struct header *cur_head = temp;
    temp = temp->next;
    zero(cur_head);
  }
  zero(temp);
}

void handle_error(char *argv1, char *argv2, struct header *fre_list_ptr) {
  printf("error in %s function, %s\n,", argv1, argv2);
  free_list(fre_list_ptr);
  exit(-1);
}
void check_empty(struct header *temp, char *argv) {
  if (temp == NULL) {
    handle_error(argv, "list not initialised", temp);
    return;
  }
}
int alloc(char *argv1, struct header *free_list_ptr, struct header *temp, int size) {
  struct header *new = (struct header *)malloc(sizeof(struct header));
  if (new == NULL) {
    handle_error(argv1, "couldn't allocate memory", free_list_ptr);
  }
  initialize_block(temp, temp->size, new, temp->id);
  initialize_block(new, size, NULL, temp->id + 1);
  return new->id;
}
int cn3(int a1, int a2) {
  if (a1 >= a2) {
    // printf("returning from check\n");
    return 1;
  }
  return 0;
}
int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: Implement first fit
  struct header *temp = free_list_ptr;
  check_empty(temp, "find_first_fit");
  // while (temp->next != NULL) {
  // int i = 1;
  for (; temp->next != NULL; temp = temp->next) {
    // printf("\tloop no: %d\n", i);
    // printf("\t\ttemp->id: %d\n", temp->id);
    // printf("\t\ttemp->size: %lu\n", temp->size);
    // i++;
    if (cn3(temp->size, size)) {
      return temp->id;
    }
    //    temp = temp->next;
  }
  return (cn3(temp->size, size) ? temp->id : alloc("find_first_fit", free_list_ptr, temp, size));
  // return alloc("find_first_fit", free_list_ptr, temp, size);
}

int c1(int a1, int a2, int a3) {
  // basically this retrun (temp->size - szie < closest - szie)
  // if (a1 == INT_MIN) {
  // printf("a1 is %d and a1 - 7 is %d\n", a1, a1 - a2);
  // }
  return (a1 - a2 < a3 - a2);
}
int c3(int a1, int a2) { return (a1 > a2); }
int c2(int a1, int a2) {
  // (temp->size - size > 0) , checks if its positive or not
  return c3((a1 - a2), 0);
}
int cn2(int a1, int a2, int a3) { return (c1(a1, a2, a3) && c2(a1, a2)); }
int find_best_fit(struct header *free_list_ptr, uint64_t szie) {
  int best_fit_id = -1;
  // TODO: Implement best fit
  struct header *temp = free_list_ptr;
  check_empty(temp, "find_best_fit");
  int closest = INT_MAX;
  // int i = 1;
  for (; temp->next != NULL; temp = temp->next) {
    // printf("\tloop no: %d\n", i);
    // printf("\t\ttemp->id: %d\n", temp->id);
    // printf("\t\ttemp->size: %lu\n", temp->size);
    // i++;
    // closest = inf, szie = 5
    // temp->size = 2, temp->size - szie = -3, add check for -ve
    if (cn2(temp->size, szie, closest)) {
      // closest = temp->size - szie;
      closest = temp->size;
      best_fit_id = temp->id;
    }
  }
  return (cn2(temp->size, szie, closest)
              ? temp->id
              : ((best_fit_id == -1) ? alloc("find_best_fit", free_list_ptr, temp, szie)
                                     : best_fit_id));
  if (cn2(temp->size, szie, closest)) {
    return temp->id;
  }
  if (best_fit_id == -1) {
    return alloc("find_best_fit", free_list_ptr, temp, szie);
  }
  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: Implement worst fit
  check_empty(free_list_ptr, "find_worst_fit");
  struct header *temp = free_list_ptr;
  // kekw, i am crying, INT_MIN leads to underflow, careful
  // int worst = INT_MIN;
  int worst = 0;
  int worst_fit_id = -1;

  // int i = 1;
  for (; temp->next != NULL; temp = temp->next) {
    // printf("yes, we ARE looping\n");
    // printf("\tloop no: %d\n", i);
    // printf("\t\ttemp->id: %d\n", temp->id);
    // printf("\t\ttemp->size: %lu\n", temp->size);
    // i++;
    // closest = -inf, size = .... 4
    // temp->size = 2
    //      a1 - a2 < a3 - a2)
    // input is 7 for our case, we should enter check at least in 2, 3 and 4, and it's a given 3
    // with 24 is going to be the 'worst',
    //    -inf - 7 < 24 - 7
    //    a1 - a2 < a3 - a2
    //    worst - size < temp->size - size
    // printf("value returned from c1(worst, size, temp->size) i.e c1(%d, %d, %lu) is %d\n", worst,
    //      size, temp->size, c1(worst, size, temp->size));
    if (c1(worst, size, temp->size)) {
      // printf("check triggered\n");
      worst = temp->size;
      // worst = temp->size - size;
      worst_fit_id = temp->id;
    }
  }
  if (!c2(worst, size)) {
    return alloc("find_worst_fit", free_list_ptr, temp, size);
  }
  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);

  // printf("\t\tfree_block1->id: %d\n", free_block1->id);
  // printf("\t\tfree_block1->size: %lu\n", free_block1->size);

  initialize_block(free_block2, 12, free_block3, 2);

  // printf("\t\tfree_block2->id: %d\n", free_block2->id);
  // printf("\t\tfree_block2->size: %lu\n", free_block2->size);

  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // TODO: Print out the IDs
  printf("The ID for First-Fit algorithm is: %d\n", first_fit_id);
  printf("The ID for Best-Fit algorithm is: %d\n", best_fit_id);
  printf("The ID for Worst-Fit algorithm is: %d\n", worst_fit_id);

  free_list(free_block1);
  return 0;
}
