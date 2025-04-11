#include "../include/entity.h"

Object* alloc_equip(int type, int quality){
	Object *E = (Object *)malloc(sizeof(Equipment));
	if(NULL == E){
		fprintf(stderr, "depassement memoire\n");
		exit(1);
	}

	switch(type){
		case 0:/*Sword*/ E->equipment.type = SWORD; break;
		case 1:/*Armor*/ E->equipment.type = ARMOR; break;
		case 2:/*MagicWand*/ E->equipment.type = MAGICWAND; break;
		default : fprintf(stderr, "type equipement inconnu %d", type); break;
	}

	E->equipment.quality = quality;
	return E;
}

Object* get_potion(int potion){
	Object *P = (Object *)malloc(sizeof(Potion));
	if(NULL == P){
		fprintf(stderr, "depassement memoire\n");
		exit(1);
	}
	switch(potion){
		case 0: P->potion = HealPotion; break;
		case 1: P->potion = ManaPotion; break;
		case 2: P->potion = RegePotion; break;
		case 3: P->potion = AccuPotion; break;
		case 4: P->potion = ApprPotion; break;
		default: fprintf(stderr, "type potion inconnu %d", potion); exit(1);
	}

	return P;
}

Entity* generate_treasure(int stage, int type){
	Entity *T = (Entity *)malloc(sizeof(Treasure));
	if(NULL == T){
		fprintf(stderr, "depassement memoire\n");
		exit(1);
	}

	switch(type){
		case 0:/*potion*/ 
			T->treasure.type = POTION; T->treasure.object = *get_potion(rand()%5); break;
		case 1: /*equipement*/
			T->treasure.type = EQUIP; T->treasure.object = *alloc_equip(rand()%3, 1+(rand()%stage)); break;
		default: fprintf(stderr, "type inconnu %d", type); break;
	}

	return T;
}



Entity* alloc_monster(int Hp, int Atk){
	if(Hp<=0 || Atk<=0){
		fprintf(stderr, "Hp ou Atk <= 0 Hp = %d Atk = %d\n", Hp, Atk);
		exit(1);
	}
	
	Entity *M = (Entity *)malloc(sizeof(Monster));
	
	if(NULL == M){
		fprintf(stderr, "depassement memoire\n");
		exit(1);
	}

	M->monster.Hp = Hp;
	M->monster.Atk = Atk;
	return M;
}

int min(int a, int b){
	return a > b ? b : a;
}

int max(int a, int b){
	return a > b ? a : b;
}
