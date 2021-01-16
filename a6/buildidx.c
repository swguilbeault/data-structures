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

int addToHs(FILE * hs_file, int index, char toHash[STRLEN]) {
    int capacity = get_capacity(hs_file);
    int hash = hashfn(toHash, capacity);

    int foundIndex;
    for (int shift = 0; shift < capacity; shift++) { // crawl through key locations
        read_index(hs_file, hash, &foundIndex);
        if (foundIndex == -1) { // if the location is empty
            write_index(hs_file, index, hash); // write index
            // if (index % 100 == 0)
            // printf("hashed %s: %d@%d\n", toHash, index, hash);
            return 0; // stop loop
        }
        hash = (hash + 1) % capacity; // continue to next index
    }

    return -1;
}

void buildidx(char * file_prefix, int capacity) {
    char * kv_filename = malloc(sizeof(char) * strlen(file_prefix) + 4); // set up kv filename
    strcpy(kv_filename, file_prefix);
    strcat(kv_filename, ".kv");
    char * khs_filename = malloc(sizeof(char) * strlen(file_prefix) + 5); // khs filename
    strcpy(khs_filename, file_prefix);
    strcat(khs_filename, ".khs");
    char * vhs_filename = malloc(sizeof(char) * strlen(file_prefix) + 5); // vhs filename
    strcpy(vhs_filename, file_prefix);
    strcat(vhs_filename, ".vhs");

    FILE * kv = fopen(kv_filename, "rb");   //open files
    FILE * khs = fopen(khs_filename, "wb+");
    FILE * vhs = fopen(vhs_filename, "wb+");
    write_empty(khs, capacity); // create empty files
    write_empty(vhs, capacity);

    int total = 0;

    char key[STRLEN], val[STRLEN];
    for (int index = 0; read_keyval(kv, key, val) == 2; index++) { // for every value in .kv
        addToHs(khs, index, key);
        addToHs(vhs, index, val);

        total += 1;
    }

    fclose(kv); // free things
    fclose(khs);
    fclose(vhs);
    free(kv_filename);
    free(khs_filename);
    free(vhs_filename);
}

void buildidxIfMissing(char * file_prefix, int capacity) {
    char * khs_filename = malloc(sizeof(char) * strlen(file_prefix) + 5); // khs filename
    strcpy(khs_filename, file_prefix);
    strcat(khs_filename, ".khs");
    char * vhs_filename = malloc(sizeof(char) * strlen(file_prefix) + 5); // vhs filename
    strcpy(vhs_filename, file_prefix);
    strcat(vhs_filename, ".vhs");

    FILE * khs = fopen(khs_filename, "rb");
    FILE * vhs = fopen(vhs_filename, "rb");

    if (khs == NULL || vhs == NULL) { // if eithe hashed file is missing

            printf("HERE\n");
        buildidx(file_prefix, capacity);
    }

    free(khs_filename);
    free(vhs_filename);
    if (khs)
        fclose(khs);
    if (vhs)
        fclose(vhs);
}


#ifndef MAIN
#define MAIN
int main(int argc, char ** argv) {
    if (argc != 3) { // verify arguments
        fprintf( stderr, "Usage: %s filename.kv capacity\n", argv[0]);
        exit(69);
    }
    argv[1][strlen(argv[1]) - 3] = '\0'; // remove .kv
    buildidx(argv[1], atoi(argv[2]));
}
#endif
