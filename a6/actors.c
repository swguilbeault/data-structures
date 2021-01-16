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

#define MAIN // this is the main file.
#include "buildidx.c"
#include "key2val.c"
#include "val2key.c"

#define TITLE_TEXT_KV "title.basics"
#define TITLE_TEXT_KV_CAP 10000
#define TITLE_NAME_KV "title.principals.kv"
#define TITLE_NAME_KV_CAP 10000
#define NAME_TEXT_KV "name.basics"
#define NAME_TEXT_KV_CAP 10000

int main(int argc, char ** argv) {
    if (argc != 2) { // verify arguments
        fprintf( stderr, "Usage: %s actor name’\n", argv[0]);
        exit(69);
    }

    buildidxIfMissing(TITLE_TEXT_KV, TITLE_TEXT_KV_CAP);
    buildidxIfMissing(NAME_TEXT_KV, NAME_TEXT_KV_CAP);

    char * movie_code = val2key(TITLE_TEXT_KV, argv[1]);

    FILE * pairs = fopen(TITLE_NAME_KV, "rb");
    char * name = NULL;
    char key[STRLEN], val[STRLEN];
    for (int index = 0; read_keyval(pairs, key, val) == 2; index++) { // for every movie
        if (strcmp(key, movie_code) == 0) { // if movie is correct
            name = key2val(NAME_TEXT_KV, val);
            printf("%s\n", name); // print actor
            free(name);
        }
    }

    fclose(pairs);
    free(movie_code);
}
