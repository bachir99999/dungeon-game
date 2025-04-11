#ifndef ENTITY_H
#define ENTITY_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {EQUIP, POTION} ObjectType;

typedef enum {HealPotion, ManaPotion, RegePotion, AccuPotion, ApprPotion} Potion;

typedef enum {SWORD, ARMOR, MAGICWAND } EquipmentType;

typedef struct{
	int Hp, Atk;
}Monster;

typedef struct {
	int quality;
	EquipmentType type;
}Equipment;

typedef union object{
	Equipment equipment;
	Potion potion;
}Object;

typedef struct{
	ObjectType type;
	Object object;
}Treasure;

typedef union entity {
	Monster monster;
	Treasure treasure;
}Entity;

Object* alloc_equip(int type, int quality);
/**
Alloue un equipement casté en object
@param type type de l'objet (1 ou 2 ou 3) epee bouclier ou armure
@param quality qualité de larme
@return renvoie un pointuer sur lequipement qui a été alloué casté en objet
**/

Object* get_potion(int potion);
/**
envoie une potion du type slectionné casté en object
@param potion type de la potion (0 à 4)
@return renvoie un pointuer sur la potion casté en objet
**/

Entity* generate_treasure(int stage, int type);
/**
Genere un tresor selon le type choisis et lui attributs des statistique coréllé au niveau dans le quel il se trouve 
@param stage niveau dans le quelle se trouve l entité
@param type type du tresor, potion ou equipement 
@return renvoie un pointuer sur la potion casté en objet
**/

Entity* alloc_monster(int Hp, int Atk);
/**
Alloue un monstre avec les attributs donnés
**/

int min(int a, int b);

int max(int a, int b);

#endif