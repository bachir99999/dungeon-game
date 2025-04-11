#include "../include/player.h"

Player alloc_player(int Hp, int HpMax, int Mp, int MpMax, int Atk, int Int, int Def, int Exp, int Lv){
	int i;
	if(Hp<=0 || Mp<0 || Atk<=0 || Int<0 || Def<0 || Exp<0 || Lv<0){
		fprintf(stderr, "Hp<=0 || Mp<0 || Atk<=0 || Int<0 || Def<0 || Exp<0 || Lv<0\n");
		exit(1);
	}

	Player P;

	P.Hp = Hp;
	P.HpMax = HpMax;
	P.Mp = Mp;
	P.MpMax = MpMax;
	P.Atk = Atk;
	P.Int = Int;
	P.Def = Def;
	P.Exp = Exp;
	P.Lv = Lv;
	P.pos.x = 0;
	P.pos.y = 0;
	P.NbObject = 0;
	for(i = 0; i < 3; i++){
		P.Boost[i] = 0;
		P.equipment[i].quality = 0;
	}

	return P;
}

Player init_player(){
	return alloc_player(100, 100, 50, 50, 10, 10, 10, 0, 0);
}

int upgrade_stat(Player *P, int stat_to_up){

	switch(stat_to_up){
		case 0 :/*up Atk*/ P->Atk++; break;
		case 1 :/*up Def*/ P->Def++; P->HpMax = P->Def * 10; break;
		case 2 :/*up Int*/ P->Int++; P->MpMax = (P->Int * 10) - 50; break;
		default :  break;
	}

	return 1;
}

void level_up(Player *P, int stat_to_up[]){
	int i, j;
	for(i = 0; i < 3; i++){
		for(j = 0; j < stat_to_up[i]; j++){
			upgrade_stat(P, i);
		}
	}
	P->Hp = P->HpMax;
	P->Mp = P->MpMax;
	P->Exp -= (350 + 50*P->Lv);
	P->Lv++;

}

int player_can_level_up(Player P){
	if(P.Exp >= (350 + 50*P.Lv))
		return 1;
	return 0;
}

int player_equipe_equimpent(Player *P, Equipment E, int pos){
	
	switch(E.type){
		case SWORD: 
			P->Atk -= P->equipment[pos].quality;
			P->Atk += E.quality;
			break;
		case ARMOR: 
			P->Def -= P->equipment[pos].quality;
			P->Def += E.quality;
			break;
		case MAGICWAND: 
			P->Int -= P->equipment[pos].quality;
			P->Int += E.quality;
			break;
		default : fprintf(stderr, "equipement type inconnu %d,\n", E.type); exit(1);
	}
	P->equipment[pos] = E;
	return 1;
}

int add_to_bag(Player *P, Treasure T){
	if(P->NbObject >= 12)
		return 1;
	
	P->Bag[P->NbObject] = T;
	P->NbObject++;
	return 0;
}

int nb_potion_in_bag(Treasure bag[], Potion Po){
	int i, res = 0;
	for(i = 0; i < 12; i++){
		if(bag[i].type == POTION && bag[i].object.potion == Po)
			res++;
	}
	return res;
}

void decalage_gauche_bag(Treasure tab[], int pos, int taille){
	int i;
	for(i = pos; i < taille - 1; i++)
		tab[i] = tab[i + 1];
}

void throw_equip(Equipment equip[], int pos){
	int i;
	for(i = pos; i < NB_MAX_EQUIP - 1; i++)
		equip[i] = equip[i + 1];

	equip[NB_MAX_EQUIP - 1].quality = 0;
}
