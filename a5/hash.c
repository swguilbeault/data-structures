// Samuel Guilbeault (1088129)
// CIS*2520 (0101)
// Prof. Stefan C. Kremer
// 1 November 2020

#include "hash.h"
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

// create a new HashTable with fields instantiated appropriately
struct HashTable * createTable(struct Performance * performance, unsigned int capacity, int (*hash) (void *, int), int (*compar) (const void *, const void *)) {
  struct HashTable * table = cmalloc(sizeof(struct HashTable), NULL);

  table->capacity = capacity;
  table->nel = 0;
  table->data = cmalloc(sizeof(void*) * table->capacity, NULL);
  for (int i = 0; i < capacity; i++) table->data[i] = NULL;
  table->hash = hash;
  table->compar = compar;

  performance->reads += capacity;
  performance->mallocs++;

  return table;
}

// add the element located at src into the hash table
void addElement(struct Performance * performance, struct HashTable * table, void * src) {
  if (table->nel == table->capacity) {
      fprintf(stderr, "failed to add element to full hash table\n");
      exit(1);
  }

  int index = table->hash(src, table->capacity);
  while (table->data[index] != NULL) {
    index = (index + 1) % table->capacity;
    if (performance != NULL) performance->reads++;
  }

  table->data[index] = src;
  table->nel++;

  if (performance != NULL) performance->writes++;
}

// get the index of an element from src, -1 if not in table
int getIdx(struct Performance * performance, struct HashTable * table, void * src) {
  int index = table->hash(src, table->capacity);

  for (int i = 0; i < table->capacity; i++) {
    performance->reads++;
    if (table->data[index] == NULL ? src == NULL : table->compar(table->data[index], src) == 0)
      return index;
    index = (index + 1) % table->capacity;
  }

  return -1;
}

// free a hash table and its data
void freeTable(struct Performance * performance, struct HashTable * table) {
  free(table->data);
  free(table);

  performance->frees++;
}

// get a pointer to the element in the hash table equal to the element pointed to by src; null if missing
void * getElement(struct Performance * performance, struct HashTable * table, void * src) {
  int index = getIdx(performance, table, src);
  return index == -1 ? NULL : table->data[index];
}

void removeElement(struct Performance * performance, struct HashTable * table, void * target) {
  int index = getIdx(performance, table, target);
  if (index != -1) {
    table->data[index] = NULL;
    table->nel--;
    performance->writes++;
  }
}

// returns the total offset of elements to their expected hash index
int hashAccuracy(struct HashTable * table) {
  int out = 0;
  for (int i = 0; i < table->capacity; i++) {
    if (table->data[i] != NULL) {
      int hash = table->hash(table->data[i], table->capacity);
      out += hash > i ? (table->capacity - hash + i) : i - hash;
    }
  }

  return out;
}

// re-hash's all values in the table to update their positions
void rehash(struct HashTable * table) {
  void ** old_data = table->data;
  table->data = cmalloc(sizeof(void*) * table->capacity, "error: failed to allocate memory for rehash\n");
  for (int i = 0; i < table->capacity; i++) table->data[i] = NULL;
  table->nel = 0;
  for (int i = 0; i < table->capacity; i++)
    if (old_data[i] != NULL)
      addElement(NULL, table, old_data[i]);
  free(old_data);
}
