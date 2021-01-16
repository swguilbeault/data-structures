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
#define NAME_TEXT_KV "name.basics"
#define NAME_TEXT_KV_CAP 10000

int main(int argc, char ** argv) {
    if (argc != 2) { // verify arguments
        fprintf( stderr, "Usage: %s ‘movie name’\n", argv[0]);
        exit(69);
    }

    buildidxIfMissing(TITLE_TEXT_KV, TITLE_TEXT_KV_CAP);
    buildidxIfMissing(NAME_TEXT_KV, NAME_TEXT_KV_CAP);

    char * bacon_code = val2key(NAME_TEXT_KV, "Kevin Bacon");

    FILE * movies = fopen(TITLE_NAME_KV, "rb");
    FILE * bacon_movies = fopen("bacon_movies.khs", "wb+");
    write_empty(bacon_movies, NAME_TEXT_KV_CAP);
    char key[STRLEN], val[STRLEN];
    int counter = 0;
    while (read_keyval(movies, key, val) == 2) { // for every movie
        if (strcmp(val, bacon_code) == 0) { // if kevin bacon in movie
            fseek(bacon_movies, counter * sizeof(char) * STRLEN, SEEK_SET); // go to pos in file
            fwrite(key, sizeof(char), STRLEN, bacon_movies); // write movie id to file
            counter += 1;
        }
    }
    fseek(movies, 0, SEEK_SET);
    free(bacon_code);

    char * actor_code = val2key(NAME_TEXT_KV, argv[1]);
    int found = 0;
    while (read_keyval(movies, key, val) == 2 && !found) { // for each movie
        if (strcmp(val, actor_code) == 0) { // if movie contains actor
            for (int i = 0; i < counter; i++) { // for each kevin bacon movie
                fseek(bacon_movies, i * sizeof(char) * STRLEN, SEEK_SET);
                fread(val, sizeof(char), STRLEN, bacon_movies);
                if (strcmp(key, val) == 0) { // if movies have the same id
                    char * movie_name = key2val(TITLE_TEXT_KV, key);
                    printf("%s\n", movie_name);
                    free(movie_name);
                    found = 1;
                }
            }
        }
    }

    free(actor_code);
    fclose(bacon_movies);
    fclose(movies);
}
