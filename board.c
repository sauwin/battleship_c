#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

char **alloc_board() {
    char **board = malloc(SIZE * sizeof(char*));
    for (int i = 0; i < SIZE; i++) {
        board[i] = malloc(SIZE);
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
    return board;
}

void free_board(char **board) {
    for (int i = 0; i < SIZE; i++) {
        free(board[i]);
    }
    free(board);
}

void print_board(char **b, int hide) {
    printf("   ");
    for (int i = 0; i < SIZE; i++) printf("%d ", i);
    printf("\n");

    for (int r = 0; r < SIZE; r++) {
        printf("%c  ", 'A' + r);
        for (int c = 0; c < SIZE; c++) {
            char ch = b[r][c];
            if (hide && ch == SHIP) {
                ch = EMPTY;
            }
            printf("%c ", ch);
        }
        printf("\n");
    }
}

int parse_coord(const char *s, int *r, int *c) {
    if (!s || strlen(s) < 2) return 0;
    char row = s[0];
    if (row >= 'a' && row <= 'j') row -= 32;
    if (row < 'A' || row > 'J') return 0;
    *r = row - 'A';
    *c = atoi(&s[1]);
    if (*c >= 0 && *c < SIZE) return 1;
}

int all_sunk(char **b) {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (b[r][c] == SHIP) return 0;
        }
    }
    return 1;
}
