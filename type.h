#ifndef TYPE_H
#define TYPE_H

#define SIZE 10
#define EMPTY '.'
#define SHIP 'O'
#define HIT 'X'
#define MISS '*'
#define MAX_TARGETS 200

typedef struct {
    int len;
    int count;
} ShipType;

typedef struct {
    int r[5];
    int c[5];
    int len;
    int hits;
} Ship;

typedef struct {
    int r;
    int c;
} Coord;

extern ShipType ship_types[];
extern int num_ship_types;

extern char **player;
extern char **ai;

extern Ship *player_ships;
extern Ship *ai_ships;
extern int num_player_ships;
extern int num_ai_ships;

extern Coord targets[];
extern int num_targets;

#endif
