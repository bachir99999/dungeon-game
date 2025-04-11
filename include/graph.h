#ifndef GRAPH_H
#define GRAPH_H
#include <MLV/MLV_all.h>

#include "fichier.h"

#define TAILLE_X (WIDTH+1) * 20
#define TAILLE_Y (HEIGHT+1) * 20

void dessine_player(int position_x, int position_y, MLV_Keyboard_button sym, int taille);

void dessine_cell(Cell C, int pos_x, int pos_y, int taille);

void dessine_gate(Gate G, Player P, MLV_Keyboard_button sym);

void dessine_pov_player(Gate G, Player P, int width, int height, MLV_Keyboard_button sym, int taille);

void dessine_Hp(int Hp, int HpMax,int width);

void dessine_Mp(Player P, int width);

void dessine_potion(Potion Po, int pos_x, int pos_y, MLV_Color color);

void dessine_equip(Equipment E, int pos_x, int pos_y, MLV_Color color);

void dessine_treasure(Treasure T, int pos_x, int pos_y, MLV_Color color);

void dessine_bag(Player P, int pos_x, int pos_y);

void dessine_player_equip(Player P, int pos_x, int pos_y);

void dessine_header(Player P, int current_level);

int use_treasure_in_bag(Player *P, int pos_treasure, int pos_x, int pos_y, int *dec);

int select_object_in_bag(Player P, int pos_x, int pos_y);

int select_equip(Player P, int pos_x, int pos_y);

void dessine_option_use(char *option[], int nb_opt, int pos_x, int pos_y);

int select_option(char *option[], int nb_opt, int pos_x, int pos_y);

void select_item_in_inventory(Player *P, int pos_x, int pos_y);

void dessine_boost(Player P, int pos_x, int pos_y);

void dessine_stat(char *name_stat[], int stat[], int nbelem, int pos_x, int pos_y);

int select_stat(Player *P, int pos_x, int pos_y, char *name_stat[]);

void dessine_stat_to_up(int stat_to_up[], int pos_x, int pos_y);

void select_upgrade(Player *P, int pos_x, int pos_y);

void dessine_magic_attaque(Player P, Gate G, char dir, int width_cell, int height, int width);

void dessine_data(int pos_x, int pos_y);

int enter_name(char *name);

int menu(Tower *T, Player *P, int *current_level);

int deplace_player(Tower *T, Player *P, MLV_Keyboard_button sym, int *current_level);

MLV_Color quality_to_color(int quality);

int Majin_vegeta();

#endif