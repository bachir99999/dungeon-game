#ifndef GAME_H
#define GAME_H

#include "gate.h"

int damage_atk(int Atk, int BoostAcc);

int player_atk(Player *P, Monster *M, int type_atk);

void drink_potion(Player *P, Potion Po);

int next_cell_action_player(Tower *T, Player *P, int next_x, int next_y, int *current_level);

void drink_potion(Player *P, Potion Po);

int end_turn(Player *P);

int magic_attaque(Player *P, Gate *G, char dir);

#endif