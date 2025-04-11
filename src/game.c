#include "../include/game.h"

int damage_atk(int Atk, int BoostAcc){
	int prba_cc = 5;
	float res, coef_atk = (rand() % 41);
	coef_atk = (coef_atk / 100) + 0.8;
	res = coef_atk * Atk;
	if(BoostAcc > 0)
		prba_cc = (rand()%10) + 5;
	if((rand()%100)<prba_cc)
		res = res * 3;
	return (int)res;
}

int player_atk(Player *P, Monster *M, int type_atk){
	int exp_win;
	switch(type_atk){
		case 1:/*attque de melee*/
			M->Hp -= damage_atk(P->Atk, P->Boost[1]); 
			break;
		case 2:/*attaque magique*/ 
			M->Hp -= damage_atk(P->Int * 2, P->Boost[1]);
			break;
		default: fprintf(stderr, "type_atk inconnu %d\n", type_atk);  exit(1); break;
	}
	if(M->Hp <= 0){
		exp_win = 50;
		if(P->Boost[2] > 0)
			exp_win = exp_win*1.3;
		P->Exp += exp_win;
		return 2;/*renvoie 2 si le monstre est mort*/
	}

	return 0;
}

int next_cell_action_player(Tower *T, Player *P, int next_x, int next_y, int *current_level){
	Position tmp;
	int i;
	switch(T->tower[*current_level].gate[next_y][next_x].type){
		case WALL : return 2;
		case ROOM : 
			T->tower[*current_level].gate[P->pos.y][P->pos.x].type = ROOM;
			T->tower[*current_level].gate[next_y][next_x].type = PLAYER; 
			P->pos.y = next_y;
			P->pos.x = next_x;
			break;
		case TREASURE : 
			if(T->tower[*current_level].gate[next_y][next_x].entity.treasure.type == EQUIP)
				for(i = 0; i < NB_MAX_EQUIP; i++){
					if(P->equipment[i].quality == 0 || (P->equipment[i].type == T->tower[*current_level].gate[next_y][next_x].entity.treasure.object.equipment.type && P->equipment[i].quality < T->tower[*current_level].gate[next_y][next_x].entity.treasure.object.equipment.quality)){
						player_equipe_equimpent(P, T->tower[*current_level].gate[next_y][next_x].entity.treasure.object.equipment, i);
						T->tower[*current_level].gate[next_y][next_x].type = ROOM; 
						return 0;
					}
				}
			if(add_to_bag(P, T->tower[*current_level].gate[next_y][next_x].entity.treasure)) 
				return 1;
			T->tower[*current_level].gate[next_y][next_x].type = ROOM; 
			break;
		case STAIR_DOWN : 
			if(*current_level < 10){
				T->tower[*current_level].gate[P->pos.y][P->pos.x].type = ROOM;
				*current_level += 1;
				place_player(&(T->tower[*current_level]), P, HEIGHT/2, WIDTH/2);
			}
			break;
		case STAIR_UP : 
			if(*current_level > 1){
				T->tower[*current_level].gate[P->pos.y][P->pos.x].type = ROOM;
				*current_level -= 1;
				tmp = stair_down_pos(T->tower[*current_level]);
				place_player(&(T->tower[*current_level]), P, tmp.y, tmp.x);
			}
		break;
		case MONSTER : 
			P->Hp -= damage_atk(T->tower[*current_level].gate[next_y][next_x].entity.monster.Atk, 0);
			if(player_atk(P, &T->tower[*current_level].gate[next_y][next_x].entity.monster, 1) == 2)
				T->tower[*current_level].gate[next_y][next_x].type = ROOM;
			break;
		default : fprintf(stderr, "cell_ type inconnu %d, pos_x = %d pos_y = %d \n", T->tower[*current_level].gate[next_y][next_x].type, next_x, next_y);  exit(1);
	}
	return 0;
}


void drink_potion(Player *P, Potion Po){
	switch(Po){
		case HealPotion: P->Hp = min(P->HpMax, ((P->HpMax * 0.1) + P->Hp)); break;
		case ManaPotion: P->Mp = min(P->MpMax, ((P->MpMax * 0.1) + P->Mp)); break;
		case RegePotion: P->Boost[0] += 30; break;
		case AccuPotion: P->Boost[1] += 30; break;
		case ApprPotion: P->Boost[2] += 30; break;
		default : break;
	}
}

int end_turn(Player *P){
	int i;
	if(P->Boost[0] > 0 && (P->Boost[0]-1)%3 == 0){
		P->Hp = min(P->HpMax, P->Hp + 20);
		P->Mp = min(P->MpMax, P->Mp + 10);
	}

	for(i = 0; i < 3; i++){
		if(P->Boost[i] > 0)
			P->Boost[i]--;
	}
	return 0;
}

int magic_attaque(Player *P, Gate *G, char dir){
	int x, y, i = P->pos.y, j = P->pos.x;
	
	if(P->Mp < 2)
		return 1;/*renvoie 1 si le joueur n'a pas assez de mana*/
			
	P->Mp -= 2;
	
	switch(dir){
		case 'z': x = 0; y = -1; break;
		case 's': x = 0; y = 1; break;
		case 'd': x = 1; y = 0; break;
		case 'q': x = -1; y = 0; break;
		default : fprintf(stderr, "direction inconnue \n"); exit(1);
	}

	while(G->gate[i][j].type != WALL){
		if(G->gate[i][j].type == MONSTER){
			if(player_atk(P, &G->gate[i][j].entity.monster, 2) == 2)
				G->gate[i][j].type = ROOM;
		}
		j+=x;
		i+=y;
	}

	return 0;
}