#ifndef POSITION_H
#define POSITION_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 63
#define HEIGHT 43

typedef struct position{
	int x;
	int y;
	struct position* suivant;
}Position, *ListePosition;

int in_gate(int i, int j);

ListePosition alloc_position(int x, int y);

int add_position(ListePosition *toexpand, int x, int y);

int delete_position(ListePosition *toexpand, int x, int y);

int free_lst(ListePosition *lst);

ListePosition dist_x(int dist, int x, int y);

Position rand_position(ListePosition *lst, int size);

int in_toexpand(ListePosition toexpand, Position P);

void print_list(ListePosition lst);

#endif