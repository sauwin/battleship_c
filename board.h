#ifndef BOARD_H
#define BOARD_H

#include "type.h"

char **alloc_board();
void free_board(char **board);
void print_board(char **b, int hide);
int parse_coord(const char *s, int *r, int *c);
int all_sunk(char **b);

#endif
