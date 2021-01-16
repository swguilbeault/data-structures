// Samuel Guilbeault (1088129)
// CIS*2520 (0101)
// Prof. Stefan C. Kremer
// 21 November 2020

#include <stdio.h>
#include "ttt.h"

int main(int argc, char * argv[]) {
    init_boards();
    init_board(START_BOARD);
    join_graph(START_BOARD);

    int count = 0;
    for (int i = 0; i < HSIZE; i++) if (htable[i].init == 1) count++;
    printf("%d\n", count);
}
