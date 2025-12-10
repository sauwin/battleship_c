#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "type.h"
#include "board.h"
#include "ships.h"
#include "ai.h"
#include "save.h"

ShipType ship_types[] = {
    {5,1},
    {4,1},
    {3,2},
    {2,3},
    {1,4}
};
int num_ship_types = sizeof(ship_types)/sizeof(ship_types[0]);

char **player;
char **ai;
Ship *player_ships = NULL;
Ship *ai_ships = NULL;
int num_player_ships=0;
int num_ai_ships=0;

Coord targets[MAX_TARGETS];
int num_targets=0;

int main(int argc, char *argv[]) {
    unsigned int seed;
    if (argc >= 2) {
        seed = (unsigned int)atoi(argv[1]);
    } else {
        seed = (unsigned int)time(NULL);
    }
    srand(seed);

    printf("==========================================[ Lodky by MAKSYM DRUZIUK THE W ]==========================================\n");
    printf("Seed: %u\n", seed);

    FILE *log_file = fopen("game_log.txt", "w");
    if (!log_file) {
        printf("Cannot open log file!\n");
        return 1;
    }

    player = alloc_board();
    ai = alloc_board();

    int total = total_ships_count();
    player_ships = malloc(sizeof(Ship) * total);
    ai_ships = malloc(sizeof(Ship) * total);

    num_player_ships = 0;
    num_ai_ships = 0;

    place_all_ships(player, player_ships, &num_player_ships);
    place_all_ships(ai, ai_ships, &num_ai_ships);

    fprintf(log_file, "Player ships:\n");
    for (int i = 0; i < num_player_ships; i++) {
        fprintf(log_file, "Ship %d (len=%d): ", i, player_ships[i].len);
        for (int j = 0; j < player_ships[i].len; j++)
            fprintf(log_file, "(%d,%d) ", player_ships[i].r[j], player_ships[i].c[j]);
        fprintf(log_file, "\n");
    }
    fprintf(log_file, "AI ships:\n");
    for (int i = 0; i < num_ai_ships; i++) {
        fprintf(log_file, "Ship %d (len=%d): ", i, ai_ships[i].len);
        for (int j = 0; j < ai_ships[i].len; j++)
            fprintf(log_file, "(%d,%d) ", ai_ships[i].r[j], ai_ships[i].c[j]);
        fprintf(log_file, "\n");
    }

    char input[64];
    while (1) {
        printf("\nYour board:\n");
        print_board(player, 0);

        printf("\nAI board:\n");
        print_board(ai, 1);

        printf("\nPrint A0 to fire, or 'save', 'load', 'final':\n> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "final") == 0) break;

        if (strcmp(input, "save") == 0) {
            char save_name[64];
            printf("Enter save name: ");
            fgets(save_name, sizeof(save_name), stdin);
            save_name[strcspn(save_name, "\n")] = 0;

            if (save_game(save_name)) printf("Saved as '%s'\n", save_name);
            else printf("Save failed.\n");
            continue;
        }

        if (strcmp(input, "load") == 0) {
            char save_name[64];
            printf("Enter load name: ");
            fgets(save_name, sizeof(save_name), stdin);
            save_name[strcspn(save_name, "\n")] = 0;

            if (load_game(save_name)) printf("Loaded '%s'\n", save_name);
            else printf("Load failed.\n");
            continue;
        }

        int r, c;
        if (!parse_coord(input, &r, &c)) {
            printf("Invalid!\n");
            continue;
        }

        if (ai[r][c] == HIT || ai[r][c] == MISS) {
            printf("Already fired.\n");
            continue;
        }

        char msg[64];
        if (ai[r][c] == SHIP) {
            ai[r][c] = HIT;
            check_ship_hit(ai_ships, num_ai_ships, r, c, msg);
            printf("You hit! %s\n", msg);
            fprintf(log_file, "Player fires at %c%d: HIT! %s\n", 'A'+r, c, msg);
        } else {
            ai[r][c] = MISS;
            printf("You missed!\n");
            fprintf(log_file, "Player fires at %c%d: MISS\n", 'A'+r, c);
        }

        if (all_sunk(ai)) {
            printf("You win!\n");
            fprintf(log_file, "Player wins!\n");
            break;
        }

        char ai_msg[128];
        ai_turn(ai_msg);
        printf("%s\n", ai_msg);
        fprintf(log_file, "AI: %s\n", ai_msg);

        if (all_sunk(player)) {
            printf("AI wins!\n");
            fprintf(log_file, "AI wins!\n");
            break;
        }
    }

    free_board(player);
    free_board(ai);
    free(player_ships);
    free(ai_ships);
    fclose(log_file);

    return 0;
}
