// Samuel Guilbeault (1088129)
// CIS*2520 (0101)
// Prof. Stefan C. Kremer
// 21 November 2020

#include <stdlib.h>
#include "ttt.h"

int main(int argc, char * argv[]) {
    init_boards();
    init_board(START_BOARD);
    join_graph(START_BOARD);
    compute_score();

    for (int i = 1; i < argc; i++) {
        print_node(htable[atoi(argv[i])]);
    }
}
