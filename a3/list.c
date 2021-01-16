// Samuel Guilbeault (1088129)
// CIS*2520 (0101)
// Prof. Stefan C. Kremer
// 15 October 2020

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// allocate memory of size bytes and check if it failed
void * cmalloc(unsigned int bytes, char * errmsg) {
  void * ptr = malloc(bytes);
  if (ptr == NULL) { // check if memory failed to be allocated
    fprintf(stderr, errmsg == NULL ? "error: failed allocating memory\n" : errmsg);
    exit(1);
  }
  return ptr;
}

// create and return pointer to struct Performance with fields set to 0
struct Performance * newPerformance() {
  struct Performance * ptr = cmalloc(sizeof(struct Performance), NULL);
  ptr->reads = 0;
  ptr->writes = 0;
  ptr->mallocs = 0;
  ptr->frees = 0;
  return ptr;
}

// copy data from src into new node at head of list
void push(struct Performance * performance, struct Node ** list_ptr, void * src, unsigned int width) {
  struct Node * node = cmalloc(sizeof(struct Node), NULL);
  node->next = *list_ptr;
  node->data = cmalloc(width, NULL);
  memcpy(node->data, src, width);
  *list_ptr = node;

  performance->mallocs++;
  performance->writes++;
}

// copy data from head node to dest
void readHead(struct Performance * performance, struct Node ** list_ptr, void * dest, unsigned int width) {
  if (isEmpty(performance, list_ptr)) {
    fprintf(stderr, "error: attempting to read empty list\n");
    exit(2);
  }

  memcpy(dest, (*list_ptr)->data, width);
  performance->reads++;
}

// copies data from head node to dest, frees head node, assigns new head node to list_ptr
void pop(struct Performance * performance, struct Node ** list_ptr, void * dest, unsigned int width) {
  readHead(performance, list_ptr, dest, width);
  struct Node * temp = (*list_ptr)->next;
  free((*list_ptr)->data);
  free(*list_ptr);
  *list_ptr = temp;

  performance->frees++;
}

// returns ptr to a ptr to second node in list
struct Node ** next(struct Performance * performance, struct Node ** list_ptr) {
  if (isEmpty(performance, list_ptr)) {
    fprintf(stderr, "error: attempting to read empty list\n");
    exit(2);
  }
  performance->reads++;
  return &((*list_ptr)->next);
}

// returns true if list is empty, else false
int isEmpty(struct Performance * performance, struct Node ** list_ptr) {
  return (*list_ptr) == NULL;
}

// frees all nodes in list and frees all their data fields
void freeList(struct Performance * performance, struct Node ** list_ptr) {
  while (!isEmpty(performance, list_ptr)) { // crawl through whole list
    pop(performance, list_ptr, NULL, 0);
  }
}

// copies data from node at specified index to dest
void readItem(struct Performance * performance, struct Node ** list_ptr, unsigned int index, void * dest, unsigned int width) {
  for (; index > 0; index--) // crawl to specified index
      list_ptr = next(performance, list_ptr);
  readHead(performance, list_ptr, dest, width);
}

// copy data from src into new node at end of list
void appendItem(struct Performance * performance, struct Node ** list_ptr, void * src, unsigned int width) {
  while (!isEmpty(performance, list_ptr)) // crawl to specified index
    list_ptr = next(performance, list_ptr);
  push(performance, list_ptr, src, width);
}

// copy data from src into new node at inserted at specified index in list
void insertItem(struct Performance * performance, struct Node ** list_ptr, unsigned int index, void * src, unsigned int width) {
  for (; index > 0; index--) // crawl to specified index
    list_ptr = next(performance, list_ptr);
  push(performance, list_ptr, src, width);
}

// copy data from src into new node at head of list
void prependItem(struct Performance * performance, struct Node ** list_ptr, void * src, unsigned int width) {
  insertItem(performance, list_ptr, 0, src, width);
}

void deleteItem(struct Performance * performance, struct Node ** list_ptr, unsigned int index) {
  for (; index > 0; index--)
      list_ptr = next(performance, list_ptr);
  pop(performance, list_ptr, NULL, 0);
}

// walks through array to find an element which satisfies compar with target,
// returns index of item first item found or -1 if no nodes satisfy compar
int findItem(struct Performance * performance, struct Node ** list_ptr, int (*compar)(const void *, const void *), void * target, unsigned int width) {
  int index = 0;
  void * temp = malloc(width);
  while (!isEmpty(performance, list_ptr)) { // crawl throught whole list
    readHead(performance, list_ptr, temp, width);
    if (compar(temp, target) == 0) {
      free(temp);
      return index;
    }
    index++;
    list_ptr = next(performance, list_ptr);
  }
  free(temp);
  return -1;
}
