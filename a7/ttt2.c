// Samuel Guilbeault (1088129)
// CIS*2520 (0101)
// Prof. Stefan C. Kremer
// 21 November 2020

#include "ttt.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

void init_boards() { // initializes boards in hashmap
    for (int i = 0; i < HSIZE; i++) {
        htable[i].init = 0;
    }
}

int depth(Board board) { // returns how many turns have passed
    int out = 0;
    for (int i = 0; i < 9; i++) {
        out += board[pos2idx[i]] == 'O' || board[pos2idx[i]] == 'X';
    }
    return out;
}

char winner(Board board) { // determines the winner in the board
    for (int i = 0; i < 8; i++)
        if (board[pos2idx[WINS[i][0]]] == board[pos2idx[WINS[i][1]]]
        &&  board[pos2idx[WINS[i][0]]] == board[pos2idx[WINS[i][2]]])
            return board[pos2idx[WINS[i][0]]]; // return winning character

    if (depth(board) == 9) return '-'; // full board means draw
    return '?'; // no winner
}

char turn(Board board) { // determines who's turn it is
    if (depth(board) == 9 || isalpha(winner(board))) return '-'; // full board means draw
    if (depth(board) % 2 == 0) return 'X'; // X goes on even turns
    return 'O'; // O plays on odd turns
}

void init_board(Board board) {
    int board_index = board_hash(board); // index of board in hashtable
    htable[board_index].init = 1;
    htable[board_index].turn = turn(board);
    htable[board_index].depth = depth(board);
    strcpy(htable[board_index].board, board);
    htable[board_index].winner = winner(board);
    htable[board_index].score = 2; // signal score has not been assigned
}

void join_graph(Board board) {
    int board_index = board_hash(board);
    for (int i = 0; i < 9; i++)
        if (board[pos2idx[i]] != 'X' && board[pos2idx[i]] != 'O') { // if tile is empty
            Board next;
            strcpy(next, board); // copy board string
            next[pos2idx[i]] = turn(board); // place move at new location
            int next_index = board_hash(next); // hash new board
            htable[board_index].move[i] = next_index; // set pointer to next element
            if (htable[next_index].init == 0) { // if this is a new board combination
                init_board(next); // create new board combination
                join_graph(next); // recusively add board graphs
            }
        } else { // tile is already occupied
            htable[board_index].move[i] = -1;
        }
}

int imax(int a, int b) { // returns the larger of a and b
    return (a > b ? a : b);
}

int imin(int a, int b) { // returns the smaller of a and b
    return (a < b ? a : b);
}

void assign_score(struct BoardNode * this) {
    if (this->winner == '?') { // recursive case
        this->score = (this->turn == 'X' ? -1 : 1); // set appropriate starting min/max value
        int (*compar) (int, int) = (this->turn == 'X' ? &imax : &imin); // function pointer to appropriate min/max function
        for (int i = 0; i < 9; i++) { // for every possible move
            if (this->move[i] != -1) { // if move is possible
                if (htable[this->move[i]].score > 1 || htable[this->move[i]].score < -1) // if move's score is invalid
                    assign_score(&htable[this->move[i]]); // recusively assign move's score
                this->score = compar(this->score, htable[this->move[i]].score); // store new best move
            }
        }
    } else if (this->winner == 'X') this->score = 1; // leaf node base cases
    else if (this->winner == 'O') this->score = -1;
    else if (this->winner == '-') this->score = 0;
}

void compute_score() {
    assign_score(&htable[board_hash(START_BOARD)]);
}

int best_move(int board) {
    struct BoardNode this = htable[board];
    for (int i = 0; i < 9; i++) // check for move to win
        if (this.move[i] != -1 && this.turn == htable[this.move[i]].winner)
                return i;

    for (int i = 0; i < 9; i++)  // check for best possible movee
        if (this.move[i] != -1 && this.score == htable[this.move[i]].score)
            return i;

    return 0;
}
