// Samuel Guilbeault (1088129)
// CIS*2520 (0101)
// Prof. Stefan C. Kremer
// 1 November 2020

#ifndef _HASH_H
#define _HASH_H

struct HashTable {
  unsigned int capacity;
  unsigned int nel;
  void ** data;
  int (*hash) (void *, int);
  int (*compar) (const void *, const void *);
};

struct Performance {
  unsigned int reads;
  unsigned int writes;
  unsigned int mallocs;
  unsigned int frees;
};

void * cmalloc(unsigned int bytes, char * errmsg);
struct Performance * newPerformance();

struct HashTable * createTable(struct Performance * performance, unsigned int capacity, int (*hash) (void *, int), int (*compar) (const void *, const void *));
void addElement(struct Performance * performance, struct HashTable * table, void * src);
int getIdx(struct Performance * performance, struct HashTable * table, void * src);
void freeTable(struct Performance * performance, struct HashTable * table);

void * getElement(struct Performance * performance, struct HashTable * table, void * src);
void removeElement(struct Performance * performance, struct HashTable * table, void * target);

int hashAccuracy(struct HashTable * table);
void rehash(struct HashTable * table);

#endif
