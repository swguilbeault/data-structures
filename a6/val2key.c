// Samuel Guilbeault (1088129)
// CIS*2520 (0101)
// Prof. Stefan C. Kremer
// 16 November 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _HELPERS_H // cannot be certain if hashfn.h or util.h will contain include guard.
#define _HELPERS_H
#include "hashfn.h"
#include "util.h"
#endif

char * val2key(char * file_prefix, char * query) {
    char * kv_filename = malloc(sizeof(char) * strlen(file_prefix) + 4); // set up kv filename
    strcpy(kv_filename, file_prefix);
    strcat(kv_filename, ".kv");
    char * vhs_filename = malloc(sizeof(char) * strlen(file_prefix) + 5); // khs filename
    strcpy(vhs_filename, file_prefix);
    strcat(vhs_filename, ".vhs");
    FILE * kv = fopen(kv_filename, "rb");   //open files
    FILE * vhs = fopen(vhs_filename, "rb");

    int capacity = get_capacity(vhs);
    int queryhash = hashfn(query, capacity);
    char * key = NULL;

    char val[STRLEN];
    int foundIndex, found = 0;
    for (int shift = 0; shift < capacity && !found; shift++) { // crawl through key locations
        read_index(vhs, queryhash, &foundIndex);
        read_val(kv, foundIndex, val);

        if (strcmp(query, val) == 0) {
            key = malloc(sizeof(char) * STRLEN);
            read_key(kv, foundIndex, key);
            found = 1;
        }

        queryhash = (queryhash + 1) % capacity; // continue to next index
    }

    fclose(kv);
    fclose(vhs);
    free(kv_filename);
    free(vhs_filename);

    return key;
}

#ifndef MAIN
#define MAIN
int main(int argc, char ** argv) {
    if (argc != 3) { // verify arguments
        fprintf( stderr, "Usage: %s filename.kv ‘search term’\n", argv[0]);
        exit(69);
    }
    argv[1][strlen(argv[1]) - 3] = '\0'; // trim .kv

    char * val = val2key(argv[1], argv[2]);

    if (val == NULL)
        printf("NOT FOUND\n");
    else
        printf("%s\n", val);

    free(val);
}
#endif
