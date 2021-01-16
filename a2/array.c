#include "array.h"
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

// create and return pointer to new struct Array with appropriate fields
struct Array * newArray(struct Performance * performance, unsigned int width, unsigned int capacity) {
  struct Array * ptr = cmalloc(sizeof(struct Array), NULL);
  ptr->width = width;
  ptr->nel = 0;
  ptr->capacity = capacity;

  ptr->data = cmalloc(ptr->width * ptr->capacity, NULL);
  performance->mallocs++;

  return ptr;
}

// navigate to data in array located at index i and copies it to dest
void readItem(struct Performance * performance, struct Array *array, unsigned int index, void * dest) {
  if (index >= array->nel) { // check if index in valid range, assumed positive
     fprintf(stderr, "error: array index %u [0:%u]\n", index, array->nel - 1);
     exit(2);
  }

  memcpy(dest, ((char *) array->data) + array->width * index, array->width);
  performance->reads++;
}

// copies data from src into array at specified index
void writeItem(struct Performance * performance, struct Array * array, unsigned int index, void * src) {
  if (index > array->nel || index >= array->capacity) { // check if index in valid range, assumed positive
    fprintf(stderr, "error: array index %u out of range [0:%u]\n", index, array->nel - 1);
    exit(3);
  }

  memcpy( ((char *) array->data) + array->width * index, src, array->width); // copy src to array
  if (index == array->nel) array->nel++; // update size as necessary
  performance->writes++;
}

// reduces size of array by one, if possible
void contract(struct Performance * performance, struct Array * array) {
  if (array->nel == 0) { // check that list is not empty
    fprintf(stderr,"error: cannot contract array of size 0");
    exit(3);
  }

  array->nel--;
}

// frees entire array structure
void freeArray(struct Performance * performance, struct Array * array) {
  free(array->data);
  free(array);
  performance->frees++;
}

// adds item to end of array from src
void appendItem(struct Performance * performance, struct Array * array, void * src) {
  writeItem(performance, array, array->nel, src);
}

// inserts item at src in array at specified index and shifts subsequent elements
void insertItem(struct Performance * performance, struct Array * array, unsigned int index, void * src) {
  void * temp = cmalloc(array->width, NULL);
  for (unsigned int i = array->nel; i > index; i--) { // copy items from right to left to save information
    readItem(performance, array, i - 1, temp);
    writeItem(performance, array, i, temp);
  }
  free(temp);
  writeItem(performance, array, index, src); // write new element
}


// inserts item at src at the start of the array and shifts subsequent elements
void prependItem(struct Performance * performance, struct Array * array, void * src) {
  insertItem(performance, array, 0, src);
}

// removes the element at the specifed index and shifts subsequent elements
void deleteItem(struct Performance * performance, struct Array * array, unsigned int index) {
  void * temp = cmalloc(array->width, NULL);
  for (unsigned int i = index; i < array->nel - 1; i++) { // copy items from left to right to save information
    readItem(performance, array, i + 1, temp);
    writeItem(performance, array, i, temp);
  }
  free(temp);
  contract(performance, array); // reduce size of array, removes duplicate final element
}

// walks through array to find an element which satisfies compar with target
int findItem(struct Performance * performance, struct Array * array, int (* compar)(const void *, const void *), void * target) {
  void * temp = cmalloc(array->width, NULL);
  for (unsigned int i = 0; i < array->nel; i++) { // walk through indeces
    readItem(performance, array, i, temp);
    if (compar(temp, target) == 0) { // check for match
      free(temp);
      return i;
    }
  }
  free(temp);
  return -1;
}

// performs binary search through array to find an element which satsifies
// compar with target
int searchItem(struct Performance * performance, struct Array * array, int (* compar)(const void *, const void *), void * target) {
  unsigned int min = 0, max = array->nel - 1;
  int result;
  void * temp = cmalloc(array->width, NULL);

  while (min <= max) { // until list has been effectively searched
    readItem(performance, array, (min + max) / 2, temp);

    if ((result = compar(temp, target)) == 0) { // check for match
      free(temp);
      return (min + max) / 2;
    } else if (result < 0)
      min = (min + max) / 2 + 1; // search higher indeces
    else if ((min + max) / 2 > 0)    // check for underflow cases
      max = (min + max) / 2 - 1; // search lower indeces
    else //when target is smaller than all elements in array
      min = max + 1; // break out of loop as target is smaller than all elements
  }
  free(temp);
  return -1;
}
