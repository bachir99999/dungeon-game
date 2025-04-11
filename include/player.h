#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "position.h"

#define NB_MAX_EQUIP 3

typedef struct{
	int Hp, HpMax, Mp, MpMax, Atk, Int, Def, Exp, Lv, NbObject, 
	Boost[3]/*bonus du joueur 0 Regen 1 Prec 2 Exp*/;
	Treasure Bag[12];
	Equipment equipment[NB_MAX_EQUIP];/*equiment du joueur*/
	Position pos;/*position du joueur dans le donjon*/
}Player;

Player alloc_player(int Hp, int HpMax, int Mp, int MpMax, int Atk, int Int, int Def, int Exp, int Lv);
/**
Alloue une structure Player
@param Hp point de vie actuelle du joueur
@param HpMax point de vie maximum du joueur
@param Mp point de magie actuelle du joueur
@param MpMax point de magie maximum du joueur
@param Atk point d attaque du joueur
@param Int point d intelligence du joueur
@param Def point de defense du joueur
@param Exp point d experience du joueur
@param Lv niveau du joueur
@return une structure Player
**/

Player init_player();
/**
Initialise la structure player avec des attribus cohérent pour le joueur au niveau 1 
@return une structure Player
**/

int upgrade_stat(Player *P, int stat_to_up);
/**
Ajoute un points dans la statistique selectionné au joueur
@param P pointeur sur la structure du Joueur contenant ses attributs, ses possesions et son etat
@param stat_to_up statistique qui sera incrementé (0 -> attaque / 1 -> defense / 2 -> intelligence)
@return 1
**/

void level_up(Player *P, int stat_to_up[]);
/**
Ajoute les points dans les statistiques selectionné du joueur
@param P pointeur sur la structure du Joueur contenant ses attributs, ses possesions et son etat
@param stat_to_up tableau contenant le nombre de fois que la statistique sera incrementé (0 -> attaque / 1 -> defense / 2 -> intelligence)
@return 1
**/

int player_can_level_up(Player P);
/**
Permet de savoir si le joueur peut gagner en niveau
@param P structure du Joueur contenant ses attributs, ses possesions et son etat
@return Revoie 1 si le joueur a assez dexperience pour gagner en niveau
**/

int player_equipe_equimpent(Player *P, Equipment E, int pos);
/**
equipe un equipement au joueur
@param P pointeur sur la structure du Joueur contenant ses attributs, ses possesions et son etat
@param E structure equipement contenant les statistique de lequipement 
@param pos position à la quelle se trouve lequipement dans les equipements du joueur
@return 1
**/

int add_to_bag(Player *P, Treasure T);
/**
ajoute un tresor à l'inventaire du joueur
@param P pointeur sur la structure du Joueur contenant ses attributs, ses possesions et son etat
@param T structure representant un tresor (equipement ou potion)
@return 1 si le sac est plein 0 sinon
**/

int nb_potion_in_bag(Treasure bag[], Potion Po);
/**
donne le nombre de potion de meme genre que Po dans le inventaire du personnage
@param bag tableau de structure representant un tresor (equipement ou potion)
@param Po enum des diffrentes potion
@return le nombre de potion trouvé
**/

void decalage_gauche_bag(Treasure tab[], int pos, int taille);
/**
Decale un tabelau de tresor vers la gauche à partir sune positio choisie
@param tab tableau de structure representant un tresor (equipement ou potion)
@param pos postion à partir du quelle le tableau sera decalé
@param taille taille du tableau
**/

void throw_equip(Equipment equip[], int pos);
/**
Suprimme un equiment du tableau des equipement à la position pos
@param equip tableau de structure d equipement contenant les statistique dun equipement 
@param pos position de lelement qui sera jeté
**/

#endif