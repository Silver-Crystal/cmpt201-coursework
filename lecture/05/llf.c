
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
struct Node {
  int data;
  struct Node *next;
};

// Create a new node with the given data

struct Node *createNode(int data) {
  struct Node *newNode = malloc(sizeof(*newNode));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

// Insert a new ndoe at the end of list
void append(struct Node **head, int data) {
  // code
  struct Node *traverse = (*head);
  if (traverse == NULL) {
    struct Node *newHead = createNode(data);
    (*head) = newHead;
    return;
  }
  for (; traverse->next != NULL; traverse->next = NULL) {
  }
  struct Node *newEnd = createNode(data);
  traverse->next = newEnd;
}

void traverse(struct Node *head) {
  // code
  if (head == NULL) {
    printf("list is empty\n");
    return;
  }
  while (head) {
    printf(" %d -> ", head->data);
    head = head->next;
  }
  printf(" NULL\n");
}

int main() {

  struct Node *head = NULL;

  // Append
  append(&head, 1);
  append(&head, 2);
  append(&head, 3);

  // traverse and pritn
  printf("Linked List: ");

  traverse(head);

  struct Node *current = head;
  while (current != NULL) {
    struct Node *temp = current;
    current = current->next;
    free(temp);
  }
  head = NULL;
}
