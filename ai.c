#include <stdio.h>
#include <stdlib.h>
#include "ai.h"
#include "board.h"
#include "ships.h"

void add_target(int r, int c) {
    for (int i = 0; i < num_targets; i++) {
        if (targets[i].r == r && targets[i].c == c) return;
    }

    if (num_targets < MAX_TARGETS) {
        targets[num_targets++] = (Coord){r, c};
    }
}

void ai_turn(char *msg) {
    int r, c;
    if (num_targets > 0) {
        num_targets--;
        r = targets[num_targets].r;
        c = targets[num_targets].c;
    } else {
        r = rand() % SIZE;
        c = rand() % SIZE;
        while (player[r][c] == HIT || player[r][c] == MISS) {
            r = rand() % SIZE;
            c = rand() % SIZE;
        }
    }

    if (player[r][c] == SHIP) {
        player[r][c] = HIT;
        char text[64];
        check_ship_hit(player_ships, num_player_ships, r, c, text);
        sprintf(msg, "AI fires at %c%d ... %s", 'A'+r, c, text);
        int dr[4] = {-1,1,0,0};
        int dc[4] = {0,0,-1,1};
        for (int i = 0; i < 4; i++){
            int nr = r + dr[i], nc = c + dc[i];
            if (nr>=0 && nr<SIZE && nc>=0 && nc<SIZE && (player[nr][nc] == EMPTY || player[nr][nc] == SHIP)) {
                add_target(nr, nc);
            }
        }
    } else {
        player[r][c] = MISS;
        sprintf(msg, "AI fires at %c%d ... miss", 'A'+r, c);
    }
}
