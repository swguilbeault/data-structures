// Samuel Guilbeault (1088129)
// CIS*2520 (0101)
// Prof. Stefan C. Kremer
// 26 October 2020

#include "tree.h"
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

// attach a new node with value src to memory at node_ptr
void attachNode(struct Performance * performance, struct Node ** node_ptr, void * src, unsigned int width) {
  struct Node * node = cmalloc(sizeof(struct Node), NULL);
  node->lt = NULL;
  node->gte = NULL;
  node->data = cmalloc(width, NULL);
  memcpy(node->data, src, width);

  *node_ptr = node;

  performance->mallocs++;
  performance->writes++;
}

// compares value of node to specified target as defined by compar
int comparNode(struct Performance * performance, struct Node ** node_ptr, int (*compar)(const void *,const void *), void * target) {
  performance->reads++;
  return compar(target, (*node_ptr)->data);
}

// returns less-than or greater-than-equal node double pointer based on direction
struct Node ** next(struct Performance * performance, struct Node ** node_ptr, int direction) {
  if (isEmpty(performance, node_ptr)) {
    fprintf(stderr, "error: null pointer\n");
    exit(2);
  }

  performance->reads++;
  return (direction < 0 ? &((*node_ptr)->lt) : &((*node_ptr)->gte));
}

// reads the value pointed to by node_ptr double pointer and copies it into dest
void readNode(struct Performance * performance, struct Node ** node_ptr, void * dest, unsigned int width) {
  if (isEmpty(performance, node_ptr)) {
    fprintf(stderr, "error: null pointer\n");
    exit(3);
  }

  memcpy(dest, (*node_ptr)->data, width);
  performance->reads++;
}

// removes node pointed to by double pointer node_ptr
void detachNode(struct Performance * performance, struct Node ** node_ptr) {
  if (isEmpty(performance, node_ptr)) {
    fprintf(stderr, "error: null pointer");
    exit(4);
  }

  free((*node_ptr)->data);
  free(*node_ptr);
  *node_ptr = NULL;

  performance->frees++;
}

// returns true if node_ptr points to a NULL value, else false
int isEmpty(struct Performance * performance, struct Node ** node_ptr) {
  return *node_ptr == NULL;
}

// finds correct spot for a new node based off src value and compar and attaches new node
void addItem(struct Performance * performance, struct Node ** node_ptr, int (*compar)(const void *, const void *), void * src, unsigned int width) {
  while (isEmpty(performance, node_ptr) == 0) {
    node_ptr = next(performance, node_ptr, comparNode(performance, node_ptr, compar, src));
  }
  attachNode(performance, node_ptr, src, width);
}

// recursively frees the tree at node_ptr
void freeTree(struct Performance * performance, struct Node ** node_ptr) {
  for (int i = -1; i < 1; i++) { // for each branch
    struct Node ** branch = next(performance, node_ptr, i);
    if (isEmpty(performance, branch) == 0) {
      freeTree(performance, branch); // recursive call
    }
  }

  detachNode(performance, node_ptr); // remove current node
}

// find item based on compar and target and copies the found value into target
// returns 1 if item is found, else 0
int searchItem(struct Performance * performance, struct Node ** node_ptr, int (*compar)(const void *, const void *), void * target, unsigned int width) {
  while (isEmpty(performance, node_ptr) == 0) { // continue until after leaf
    int direction = comparNode(performance, node_ptr, compar, target);

    if (direction == 0) { // found match
      readNode(performance, node_ptr, target, width);
      return 1;
    }
    node_ptr = next(performance, node_ptr, direction); // step throught
  }

  return 0;
}
