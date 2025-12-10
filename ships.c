#include <stdio.h>
#include <stdlib.h>
#include "ships.h"
#include "board.h"

int total_ships_count() {
    int total = 0;
    for (int i = 0; i < num_ship_types; i++) {
        total += ship_types[i].count;
    }
    return total;
}

int can_place(char **b, int r, int c, int len, int horiz) {
    for (int i = 0; i < len; i++) {
        int rr = r + (horiz ? 0 : i);
        int cc = c + (horiz ? i : 0);
        if (rr < 0 || rr >= SIZE || cc < 0 || cc >= SIZE || b[rr][cc] != EMPTY) return 0;
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                int nr = rr + dr;
                int nc = cc + dc;
                if (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE && b[nr][nc] == SHIP) return 0;
            }
        }
    }
    return 1;
}

int place_ship_record(char **b, int len, Ship *ships, int *count) {
    for (int attempt = 0; attempt < 1000; attempt++) {
        int horiz = rand() % 2;
        int r = rand() % (SIZE - (horiz ? 0 : len - 1));
        int c = rand() % (SIZE - (horiz ? len - 1 : 0));
        if (!can_place(b, r, c, len, horiz)) continue;

        Ship s = {.len = len, .hits = 0};
        for (int i = 0; i < len; i++) {
            int rr = r + (horiz ? 0 : i);
            int cc = c + (horiz ? i : 0);
            b[rr][cc] = SHIP;
            s.r[i] = rr;
            s.c[i] = cc;
        }
        ships[(*count)++] = s;
        return 1;
    }
    return 0;
}

int place_all_ships(char **b, Ship *ships, int *count) {
    *count = 0;
    for (int i = 0; i < num_ship_types; i++) {
        for (int j = 0; j < ship_types[i].count; j++) {
            if (!place_ship_record(b, ship_types[i].len, ships, count)) return 0;
        }
    }
    return 1;
}

int check_ship_hit(Ship *arr, int n, int r, int c, char *msg) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < arr[i].len; j++) {
            if (arr[i].r[j] == r && arr[i].c[j] == c) {
                arr[i].hits++;
                sprintf(msg, arr[i].hits == arr[i].len ? "Sunk! (len %d)" : "Hit!", arr[i].len);
                return 1;
            }
        }
    }
    return 0;
}
