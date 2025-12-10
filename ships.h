#ifndef SHIPS_H
#define SHIPS_H

#include "type.h"

int total_ships_count();
int can_place(char **b, int r, int c, int len, int horiz);
int place_ship_record(char **b, int len, Ship *ships, int *count);
int place_all_ships(char **b, Ship *ships, int *count);
int check_ship_hit(Ship *arr, int n, int r, int c, char *msg);

#endif
