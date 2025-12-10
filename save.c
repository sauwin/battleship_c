#include <stdio.h>
#include <string.h>
#include "save.h"
#include "board.h"
#include "ships.h"

int save_game(const char *name) {
    char path[256];
    sprintf(path, "saves/%s.dat", name);
    FILE *f = fopen(path, "wb");
    if(!f) return 0;

    fwrite("LODE", 1, 4, f);

    for(int r=0;r<SIZE;r++) fwrite(player[r], 1, SIZE, f);
    for(int r=0;r<SIZE;r++) fwrite(ai[r], 1, SIZE, f);

    fwrite(&num_player_ships, sizeof(int), 1, f);
    fwrite(player_ships, sizeof(Ship), num_player_ships, f);

    fwrite(&num_ai_ships, sizeof(int), 1, f);
    fwrite(ai_ships, sizeof(Ship), num_ai_ships, f);

    fwrite(&num_targets, sizeof(int), 1, f);
    fwrite(targets, sizeof(Coord), num_targets, f);

    fclose(f);
    return 1;
}

int load_game(const char *name){
    char path[256];
    sprintf(path, "saves/%s.dat", name);
    FILE *f=fopen(path, "rb");
    if(!f) return 0;

    char magic[5] = {0};
    fread(magic, 1, 4, f);
    if(strncmp(magic, "LODE", 4) != 0){
        fclose(f);
        return 0;
    }

    for(int r=0; r<SIZE; r++) fread(player[r], 1, SIZE, f);
    for(int r=0; r<SIZE; r++) fread(ai[r], 1, SIZE, f);

    fread(&num_player_ships, sizeof(int), 1, f);
    fread(player_ships, sizeof(Ship), num_player_ships, f);

    fread(&num_ai_ships, sizeof(int), 1, f);
    fread(ai_ships, sizeof(Ship), num_ai_ships, f);

    fread(&num_targets, sizeof(int), 1, f);
    fread(targets, sizeof(Coord), num_targets, f);

    fclose(f);
    return 1;
}
