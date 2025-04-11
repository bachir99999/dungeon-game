#ifndef GATE_H
#define GATE_H

#include "player.h"

typedef enum {WALL, ROOM, MONSTER, TREASURE, STAIR_UP, STAIR_DOWN, PLAYER} Celltype;

typedef struct{
	Celltype type;
	Entity entity;
}Cell;

typedef struct{
	Cell gate[HEIGHT][WIDTH];
}Gate;

typedef struct{
	Gate tower[10];
}Tower;

int abs(int a);

int distance_manathan(int i1, int j1, int i2, int j2);

void print_cell(Celltype C);

void print_gate(Gate G);

Gate init_gate();

int admissible(Gate G, int i, int j);

int adj_3wall(Gate G, int i, int j);

int surround_cell_by_room(Gate *G, int i, int j);

Gate generate_gate();

int adj_1room(Gate G, int i, int j, Position *pos);

void place_treasur_monster(Gate *G, int stage);

void place_player(Gate *G, Player *P, int i, int j);

void place_staire_down(Gate *G);

Position stair_down_pos(Gate G);

Tower generate_tower();


#endif