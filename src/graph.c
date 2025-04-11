#include "../include/graph.h"

void dessine_player(int position_x, int position_y, MLV_Keyboard_button sym, int taille){
	int cord_x[3], cord_y[3];
	
	switch(sym){
		case 'z': 
			cord_x[0] = position_x-taille/2; cord_x[1] = position_x;	cord_x[2] = position_x+taille/2;
		    cord_y[0] = position_y+taille/2; cord_y[1] = position_y-taille/2; cord_y[2] = position_y+taille/2;
			break;
		case 'd': 
			cord_x[0] = position_x-taille/2; cord_x[1] = position_x-taille/2;	cord_x[2] = position_x+taille/2;
		    cord_y[0] = position_y-taille/2; cord_y[1] = position_y+taille/2; cord_y[2] = position_y;
			break;
		case 'q': 
			cord_x[0] = position_x+taille/2; cord_x[1] = position_x+taille/2;  cord_x[2] = position_x-taille/2;
		    cord_y[0] = position_y+taille/2; cord_y[1] = position_y-taille/2;  cord_y[2] = position_y;	
			break;
		case 's': 
			cord_x[0] = position_x-taille/2; cord_x[1] = position_x;	cord_x[2] = position_x+taille/2;
		    cord_y[0] = position_y-taille/2; cord_y[1] = position_y+taille/2; cord_y[2] = position_y-taille/2;
			break;
		default : fprintf(stderr, "deplacement non reconnu, sym = %d\n", sym); exit(1);
	}
	MLV_draw_filled_polygon(cord_x, cord_y, 3, MLV_COLOR_BLUE);	
}

void dessine_cell(Cell C, int pos_x, int pos_y, int taille){/*WALL, ROOM, MONSTER, TREASURE, STAIR_UP, STAIR_DOWN*/
	switch(C.type){
		case WALL : MLV_draw_filled_rectangle(pos_x-taille/2, pos_y-taille/2, taille, taille, MLV_COLOR_BLACK); break;
		case ROOM : MLV_draw_filled_rectangle(pos_x-taille/2, pos_y-taille/2, taille, taille, MLV_COLOR_WHITE); break;
		case TREASURE : MLV_draw_filled_rectangle(pos_x-taille/2, pos_y-taille/2, taille, taille, MLV_COLOR_YELLOW); break;
		case STAIR_DOWN : MLV_draw_filled_rectangle(pos_x-taille/2, pos_y-taille/2, taille, taille, MLV_COLOR_RED); break;
		case STAIR_UP : MLV_draw_filled_rectangle(pos_x-taille/2, pos_y-taille/2, taille, taille, MLV_COLOR_GREEN); break;
		case MONSTER : MLV_draw_filled_rectangle(pos_x-taille/2, pos_y-taille/2, taille, taille, MLV_COLOR_WHITE); MLV_draw_filled_circle(pos_x, pos_y, taille/2, MLV_COLOR_RED); break;
		case PLAYER : MLV_draw_filled_rectangle(pos_x-taille/2, pos_y-taille/2, taille, taille, MLV_COLOR_WHITE); break;
		default : fprintf(stderr, "cell_type inconnu %d, pos_x = %d pos_y = %d \n", C.type, pos_x, pos_y); print_cell(C.type); exit(1);
	}
}

void dessine_gate(Gate G, Player P, MLV_Keyboard_button sym){
	int i, j;
	for(i = 0; i < HEIGHT; i++){
		for(j = 0; j < WIDTH; j++){
			dessine_cell(G.gate[i][j], (j+1) * 20, (i+1) * 20, 20);
		}
	}
	dessine_player((P.pos.x+1) * 20, (P.pos.y+1) * 20, sym, 20);
}

void dessine_pov_player(Gate G, Player P, int width, int height, MLV_Keyboard_button sym, int taille){
	int i, j;

	for(i = max(P.pos.y - 4, 0); i < min(P.pos.y + 5, HEIGHT); i++){
		for(j = max(P.pos.x - 6, 0); j < min(P.pos.x + 7, WIDTH); j++){
			dessine_cell(G.gate[i][j], (j - P.pos.x + (width/2)) * taille , (i - P.pos.y + (height/2)) * taille, taille);
		}
	}
	dessine_player(((width/2)) * taille, ((height/2)) * taille, sym, taille);
}

void dessine_Hp(int Hp, int HpMax,int width){
	MLV_draw_rectangle(width - 150, 10, 100, 10, MLV_COLOR_WHITE);
	MLV_draw_filled_rectangle(width - 150, 10, (100 * Hp) / HpMax, 10, MLV_COLOR_GREEN);
}

void dessine_Mp(Player P, int width){
	MLV_draw_rectangle(width - 150, 25, 100, 10, MLV_COLOR_WHITE);
	MLV_draw_filled_rectangle(width - 150, 25, (100 * P.Mp) / P.MpMax, 10, MLV_COLOR_BLUE);
}

void dessine_potion(Potion Po, int pos_x, int pos_y, MLV_Color color){/*HealPotion, ManaPotion, RegePotion, AccuPotion, ApprPotion*/
	int cord_x[4], cord_y[4];
	MLV_Color colorPo;
	cord_x[0] = pos_x-5; cord_x[1] = pos_x; cord_x[2] = pos_x+5; cord_x[3] = pos_x;
    cord_y[0] = pos_y+7; cord_y[1] = pos_y+12; cord_y[2] = pos_y+7; cord_y[3] = pos_y+2;
	switch(Po){
		case HealPotion : colorPo = MLV_COLOR_RED; MLV_draw_text(pos_x+15, pos_y,"Potion de soin", color); break;
		case ManaPotion : colorPo =  MLV_COLOR_BLUE; MLV_draw_text(pos_x+15, pos_y,"Potion de mana", color); break;
		case RegePotion : colorPo =  MLV_COLOR_PINK; MLV_draw_text(pos_x+15, pos_y,"Potion de regeneration", color); break;
		case AccuPotion : colorPo =  MLV_COLOR_YELLOW; MLV_draw_text(pos_x+15, pos_y,"Potion de precision", color); break;
		case ApprPotion : colorPo =  MLV_COLOR_GREEN; MLV_draw_text(pos_x+15, pos_y,"Potion d'apprentissage", color); break;
		default : fprintf(stderr, "potion inconnu %d\n", Po); exit(1);
	}
	MLV_draw_filled_polygon(cord_x, cord_y, 4, colorPo);
}

void dessine_equip(Equipment E, int pos_x, int pos_y, MLV_Color color){/*SWORD, ARMOR, MAGICWAND*/
	int cord_x[3], cord_y[3];
	switch(E.type){
		case SWORD :
			cord_x[0] = pos_x-5; cord_x[1] = pos_x-5;	cord_x[2] = pos_x+5;
		    cord_y[0] = pos_y; cord_y[1] = pos_y+10; cord_y[2] = pos_y+5;
		    MLV_draw_filled_polygon(cord_x, cord_y, 3, quality_to_color(E.quality)); 
		    MLV_draw_text(pos_x+15, pos_y,"Epee", color);
		    break;
		case ARMOR :
			MLV_draw_filled_rectangle(pos_x-5, pos_y+5, 10, 10, quality_to_color(E.quality));
			MLV_draw_text(pos_x+15, pos_y,"Armure", color); 
			break;
		case MAGICWAND : 
			MLV_draw_filled_rectangle(pos_x-5, pos_y+5, 10, 3, quality_to_color(E.quality));
			MLV_draw_text(pos_x+15, pos_y,"Baguette magic", color); 
			break;
		default : fprintf(stderr, "equipement inconnu %d\n", E.type); exit(1);
	}
}

void dessine_treasure(Treasure T, int pos_x, int pos_y, MLV_Color color){/*EQUIP, POTION*/
	switch(T.type){
		case EQUIP : dessine_equip(T.object.equipment, pos_x, pos_y, color); break;
		case POTION : dessine_potion(T.object.potion, pos_x, pos_y, color); break;
		default : fprintf(stderr, "type inconnu %d\n", T.type); exit(1);
	}
}

void dessine_bag(Player P, int pos_x, int pos_y){
	int i;
	char nb_equip[4];
	MLV_draw_text(pos_x - 158, pos_y - 165,"Contenue du sac :", MLV_COLOR_WHITE);
	for(i = 0; i < P.NbObject; i++){
		sprintf(nb_equip, "%d.", i);
		MLV_draw_text(pos_x - 158, pos_y - 150 + (20*i), nb_equip, MLV_COLOR_WHITE);
		dessine_treasure(P.Bag[i], pos_x - 140, pos_y - 150 + (20*i), MLV_COLOR_WHITE);
	}
}

void dessine_player_equip(Player P, int pos_x, int pos_y){
	int i;
	char nb_equip[4];
	MLV_draw_text(pos_x + 40, pos_y - 165,"Equipments :", MLV_COLOR_WHITE);
	for(i = 0; i < NB_MAX_EQUIP; i++){
		if(P.equipment[i].quality > 0){
			sprintf(nb_equip, "%d.", i);
			MLV_draw_text(pos_x + 32, pos_y - 150 + (20*i), nb_equip, MLV_COLOR_WHITE);
			dessine_equip(P.equipment[i], pos_x + 50 , pos_y - 150 + (20*i), MLV_COLOR_WHITE);
		}		
	}
}

void dessine_header(Player P, int current_level){
	char tmp[25] = "sac : ";
	char nb_object[25];
	dessine_Hp(P.Hp, P.HpMax, TAILLE_X);
    dessine_Mp(P, TAILLE_X);
	sprintf(nb_object, "%d/12", P.NbObject);
	MLV_draw_text(20, 20, strcat(tmp, nb_object), MLV_COLOR_WHITE);
	strcpy(tmp, "potion de soin : ");
	sprintf(nb_object, "%d", nb_potion_in_bag(P.Bag, HealPotion));
	MLV_draw_text(100, 20, strcat(tmp, nb_object), MLV_COLOR_WHITE);
	if(player_can_level_up(P))
		MLV_draw_text(TAILLE_X - 300, 20, "P : augmenter niveau", MLV_COLOR_GREEN);
	
	MLV_draw_text(TAILLE_X - 550, 20, "etage : %d niveau : %d exp : %d/%d", MLV_COLOR_WHITE, current_level,P.Lv, P.Exp, 350 + 50*P.Lv);
	MLV_draw_text(5, TAILLE_Y - 20, "esapce : attque magique      P : menu personnage      I : Inventaire     M : sauvegarder     C : charger     L : QUITTER", MLV_COLOR_WHITE);
}

int use_treasure_in_bag(Player *P, int pos_treasure, int pos_x, int pos_y, int *dec){
	int pos_equip = -1, i;
	switch(P->Bag[pos_treasure].type){
		case POTION : 
			drink_potion(P, P->Bag[pos_treasure].object.potion); 
			dessine_treasure(P->Bag[pos_treasure], 50, TAILLE_Y - ((*dec)*15 + 100), MLV_COLOR_GREEN);
			*dec+=1;
			break;
		case EQUIP : 
			for(i = 0; i < NB_MAX_EQUIP; i++){
				if(P->equipment[i].quality <= 0){
					player_equipe_equimpent(P, P->Bag[pos_treasure].object.equipment, i); 
					return 1;
				}
			}
			pos_equip = select_equip(*P, pos_x, pos_y);
			if(pos_equip < 0) return 0;
			player_equipe_equimpent(P, P->Bag[pos_treasure].object.equipment, pos_equip); 
			break;
		default : fprintf(stderr, "type inconnu %d\n", P->Bag[pos_treasure].type); exit(1);
	}
	return 1;
}

int select_object_in_bag(Player P, int pos_x, int pos_y){
	int pos = 0;
	MLV_Keyboard_button sym = MLV_KEYBOARD_NONE;
	MLV_Button_state state;

	if(P.NbObject >= 1){
		dessine_treasure(P.Bag[pos], pos_x - 140, pos_y - 150 + (20*pos), MLV_COLOR_RED);
		MLV_actualise_window();
	}
	do{
     	MLV_wait_event(&sym, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
     	if(state == 0){
     	switch(sym){
     		case 'd': if(P.NbObject >= 1) dessine_treasure(P.Bag[pos], pos_x - 140, pos_y - 150 + (20*pos), MLV_COLOR_WHITE); return -1;
     		case 'z':
     			if(pos > 0){
					dessine_treasure(P.Bag[pos], pos_x - 140, pos_y - 150 + (20*pos), MLV_COLOR_WHITE);
					pos--;
					dessine_treasure(P.Bag[pos], pos_x - 140, pos_y - 150 + (20*pos), MLV_COLOR_RED);
					MLV_actualise_window();
     			} 
     			break;
     		case 's': 
     			if(pos < P.NbObject - 1){
					dessine_treasure(P.Bag[pos], pos_x - 140, pos_y - 150 + (20*pos), MLV_COLOR_WHITE);
					pos++;
					dessine_treasure(P.Bag[pos], pos_x - 140, pos_y - 150 + (20*pos), MLV_COLOR_RED);
					MLV_actualise_window();
     			} 
     			break;
     		case MLV_KEYBOARD_RETURN: 
     			if(P.NbObject >= 1){
     				dessine_treasure(P.Bag[pos], pos_x - 140, pos_y - 150 + (20*pos), MLV_COLOR_WHITE); 
     				return pos;
     			}
     			break;
     		default : break;
     	}
     }
    }while(sym != 'e');

    return -2;
}

int select_equip(Player P, int pos_x, int pos_y){
	int pos = 0;
	MLV_Keyboard_button sym = MLV_KEYBOARD_NONE;
	MLV_Button_state state;
	
	if(P.equipment[pos].quality == 0)
		return -3;
	
	else{
		dessine_equip(P.equipment[pos], pos_x + 50 , pos_y - 150 + (20*pos), MLV_COLOR_RED);
		MLV_actualise_window();
	}
	
	do{
     	MLV_wait_event(&sym, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
     	if(state == 0){
     	switch(sym){
     		case 'q': 
     			if(P.NbObject > 0){
     				dessine_equip(P.equipment[pos], pos_x + 50 , pos_y - 150 + (20*pos), MLV_COLOR_WHITE); 
     				return -3;
     			}
     			break;
     		break;
     		case 'z':
     			if(pos > 0){
					dessine_equip(P.equipment[pos], pos_x + 50 , pos_y - 150 + (20*pos), MLV_COLOR_WHITE);
					pos--;
					dessine_equip(P.equipment[pos], pos_x + 50 , pos_y - 150 + (20*pos), MLV_COLOR_RED);
					MLV_actualise_window();
     			} 
     			break;
     		case 's': 
     			if(pos < NB_MAX_EQUIP && P.equipment[pos + 1].quality != 0){
					dessine_equip(P.equipment[pos], pos_x + 50 , pos_y - 150 + (20*pos), MLV_COLOR_WHITE);
					pos++;
					dessine_equip(P.equipment[pos], pos_x + 50 , pos_y - 150 + (20*pos), MLV_COLOR_RED);
					MLV_actualise_window();
     			} 
     			break;
     		case MLV_KEYBOARD_RETURN: dessine_equip(P.equipment[pos], pos_x + 50 , pos_y - 150 + (20*pos), MLV_COLOR_WHITE); return pos;
     		default : break;
     	}
     }
    }while(sym != 'e');

    return -2;
}

void dessine_option_use(char *option[], int nb_opt, int pos_x, int pos_y){
	int i;
	for(i = 0; i < nb_opt; i++){
		MLV_draw_filled_rectangle(pos_x, pos_y + i*25, 70, 15, MLV_COLOR_GREY);
		MLV_draw_text(pos_x + 15, pos_y + i*25, option[i], MLV_COLOR_WHITE); 
	}
	MLV_actualise_window();
}

int select_option(char *option[], int nb_opt, int pos_x, int pos_y){
	int pos = 0;
	MLV_Keyboard_button sym = MLV_KEYBOARD_NONE;
	MLV_Button_state state;
	MLV_draw_text(pos_x+15, pos_y, option[pos], MLV_COLOR_RED);
	MLV_actualise_window();
	do{
     MLV_wait_event(&sym, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
     if(state == 0){
     	switch(sym){
     		case 'z':
     			if(pos > 0){
					MLV_draw_text(pos_x+15, pos_y + pos*25, option[pos], MLV_COLOR_WHITE); 
					pos--;
					MLV_draw_text(pos_x+15, pos_y + pos*25, option[pos], MLV_COLOR_RED); 
					MLV_actualise_window();
     			} 
     			break;
     		case 's': 
     			if(pos < nb_opt){
					MLV_draw_text(pos_x+15, pos_y + pos*25, option[pos], MLV_COLOR_WHITE); 
					pos++;
					MLV_draw_text(pos_x+15, pos_y + pos*25, option[pos], MLV_COLOR_RED);
					MLV_actualise_window();
     			} 
     			break;
     		case MLV_KEYBOARD_RETURN: 
     			MLV_draw_filled_rectangle(pos_x, pos_y, 70, 15 + 25*nb_opt, MLV_COLOR_BLACK); 
     			return pos;
     		default : break;
     	}
     }
    }while(1);

    return 2;
}

void select_item_in_inventory(Player *P, int pos_x, int pos_y){
	char *option_bag[] = {"Utiliser", "Jeter", "Retour"}, *option_equip[] = {"Stocker", "Jeter", "Retour"};
	Treasure T;
	int dec = 0, res_opt,
	tmp = -3; /*-1 select equip , -2 exit , -3 select bag */
	MLV_draw_text(5, TAILLE_Y - 20, "zqsd : deplacement      entrer : valider      E : quitter ", MLV_COLOR_WHITE);
	MLV_actualise_window();
	do{
		if(tmp == -3)
	 		tmp = select_object_in_bag(*P, pos_x, pos_y);
	 	if(tmp >= 0){	 		
	 		dessine_option_use(option_bag, 3, pos_x - 250, pos_y - 175+(20*tmp));
	 		res_opt = select_option(option_bag, 3, pos_x - 250, pos_y- 175+(20*tmp));
	 		if(res_opt != 1 && ( res_opt == 2 || use_treasure_in_bag(P, tmp, pos_x, pos_y, &dec) == 0)){
	 			tmp = -3;
	 			continue;	
	 		}
	 		MLV_draw_filled_rectangle(pos_x - 300 , pos_y - 300, 600, 600, MLV_COLOR_BLACK);
	 		decalage_gauche_bag(P->Bag, tmp, P->NbObject);
	 		P->NbObject--;
     		dessine_bag(*P, pos_x, pos_y);
     		dessine_player_equip(*P, pos_x, pos_y);	 		
	 		MLV_actualise_window();
	 		tmp = -3;
	 	}

	 	if(tmp == -1){
	 		tmp = select_equip(*P, pos_x, pos_y);
	 		if(tmp >= 0){
	 			dessine_option_use(option_equip, 3, pos_x + 200, pos_y - 175+(20*tmp));
	 			res_opt = select_option(option_equip, 3, pos_x + 200, pos_y - 175+(20*tmp));
	 			if(res_opt == 2){
	 				tmp = -1;
	 				continue;	
	 			}
	 			else if(res_opt == 0){
	 				T.type = EQUIP;
	 				T.object.equipment = P->equipment[tmp];
	 				if(add_to_bag(P, T)){
	 					tmp = -1;
	 					continue;
	 				}
	 			}
	 			throw_equip(P->equipment, tmp);
	 			MLV_draw_filled_rectangle(pos_x - 300 , pos_y - 300, 600, 600, MLV_COLOR_BLACK);
     			dessine_bag(*P, pos_x, pos_y);
     			dessine_player_equip(*P, pos_x, pos_y);	 		
	 			MLV_actualise_window();
	 			tmp = -1;
	 		}
	 	}
    }while(tmp != -2);
}

void dessine_boost(Player P, int pos_x, int pos_y){
	int i;
	char *name_boost[] = {"Regeneration", "Precision", "Experience"};
	for(i = 0; i < 3; i++)
		MLV_draw_text(pos_x , pos_y + i*25, "Bonus de %s actifs pendant %d tour(s)" ,MLV_COLOR_WHITE, name_boost[i],P.Boost[i]); 
	
}

void dessine_stat(char *name_stat[], int stat[], int nbelem, int pos_x, int pos_y){
	int i;
	char buffer[150];
	for(i = 0; i < nbelem; i++){
		sprintf(buffer, ": %d", stat[i]);
		MLV_draw_text(pos_x, pos_y + i*20, name_stat[i], MLV_COLOR_WHITE);
		MLV_draw_text(pos_x + 150, pos_y + i*20, buffer, MLV_COLOR_WHITE); 
	}
	
	MLV_draw_filled_rectangle(pos_x + 40, pos_y + (nbelem + 1)*20, 95, 15, MLV_COLOR_GREY);
	MLV_draw_text(pos_x + 55, pos_y + (nbelem+1)*20, "UPGRADE", MLV_COLOR_RED); 
}

int select_stat(Player *P, int pos_x, int pos_y, char *name_stat[]){
	MLV_Keyboard_button sym = MLV_KEYBOARD_NONE;
	MLV_Button_state state;
	int pos = 3;

	MLV_draw_text(pos_x, pos_y + pos*20, name_stat[pos], MLV_COLOR_RED);
	MLV_actualise_window();
	do{	
		MLV_wait_event(&sym, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
    	if(state == 0){
			switch(sym){
				case 'z' :
					if(pos > 3){
						MLV_draw_text(pos_x, pos_y + pos*20, name_stat[pos], MLV_COLOR_WHITE);
						pos--;
						MLV_draw_text(pos_x, pos_y + pos*20, name_stat[pos], MLV_COLOR_RED);
					}
					break;

				case 's' :
					if(pos < 5){
						MLV_draw_text(pos_x, pos_y + pos*20, name_stat[pos], MLV_COLOR_WHITE);
						pos++;
						MLV_draw_text(pos_x, pos_y + pos*20, name_stat[pos], MLV_COLOR_RED);
					}
					break;

				case MLV_KEYBOARD_RETURN : 
					MLV_draw_text(pos_x, pos_y + pos*20, name_stat[pos], MLV_COLOR_WHITE);
					MLV_actualise_window();
					return pos;

				default : break;
			}
			MLV_actualise_window();
		}

	}while(!(sym == 'e' && state == 0));

	return -1;
}

void dessine_stat_to_up(int stat_to_up[], int pos_x, int pos_y){
	char buffer[5];
	int i;
	MLV_draw_filled_rectangle(pos_x + 175 , pos_y + 3*18, 25, 3*25, MLV_COLOR_BLACK);
	for(i = 0; i < 3; i++){
		sprintf(buffer, "+ %d", stat_to_up[i]);
		MLV_draw_filled_rectangle(pos_x + 172 , pos_y + (i+3)*20, 5, 5, MLV_COLOR_BLACK);
		MLV_draw_text(pos_x + 175, pos_y + (i+3)*20, buffer, MLV_COLOR_RED); 
	}
	MLV_actualise_window();
}

void select_upgrade(Player *P, int pos_x, int pos_y){
	char *name_stat[] = {"NIVEAU", "HPMAX", "MPMAX", "ATTAQUE", "DEFENSE", "INTELLIGENCE"}, *option[] = {"Plus", "Moins", "Retour"};
	int stat[] = {P->Lv, P->HpMax, P->MpMax, P->Atk, P->Def, P->Int}, cmp = 0, pos, opt, stat_to_up[3] = {0, 0, 0};
	MLV_Keyboard_button sym = MLV_KEYBOARD_NONE;
	MLV_Button_state state;
	
	dessine_boost(*P, pos_x + 250, pos_y);
	dessine_stat(name_stat, stat, 6, pos_x, pos_y);
	MLV_draw_text(5, TAILLE_Y - 20, "zqsd : deplacement      entrer : valider      E : quitter ", MLV_COLOR_WHITE);
	MLV_actualise_window();

	while(1){
		MLV_wait_event(&sym, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		if(sym == MLV_KEYBOARD_RETURN && player_can_level_up(*P)){
			MLV_draw_text(pos_x + 55, pos_y + 7*20, "UPGRADE", MLV_COLOR_WHITE);
			MLV_draw_text(pos_x + 35, pos_y - 20, "Points restants %d", MLV_COLOR_GREEN, 5-cmp);
			MLV_actualise_window();
			
			do{
				if((pos = select_stat(P, pos_x, pos_y, name_stat)) > 0){
					dessine_option_use(option, 3, pos_x - 90, pos_y + (pos-1)*20);
					opt = select_option(option, 3, pos_x - 90, pos_y + (pos-1)*20);
					
					if(opt == 0 && cmp < 5){
						stat_to_up[pos-3]++;
						cmp++;
					}
					
					if(opt == 1 && cmp > 0 && stat_to_up[pos-3] > 0){
						stat_to_up[pos-3]--;
						cmp--;
					}
				}
				
				dessine_stat_to_up(stat_to_up, pos_x, pos_y);
				MLV_draw_filled_rectangle(pos_x + 141 , pos_y  - 17, 10, 10, MLV_COLOR_BLACK);
				MLV_draw_text(pos_x + 35, pos_y - 20, "Points restants %d", MLV_COLOR_GREEN, 5-cmp);

				if(cmp == 5){
					MLV_draw_text(pos_x + 55, pos_y + 7*20, "UPGRADE", MLV_COLOR_RED);
					MLV_actualise_window();
					do{
						MLV_wait_event(&sym, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
						if(sym == MLV_KEYBOARD_RETURN && state == 0){
							level_up(P, stat_to_up);
							MLV_clear_window(MLV_COLOR_BLACK);
							return select_upgrade(P, pos_x, pos_y);
						}
					}while(!(sym == 'e' && state == 0));
					cmp = 0;
					stat_to_up[0] = 0;stat_to_up[1] = 0;stat_to_up[2] = 0;
					dessine_stat_to_up(stat_to_up, pos_x, pos_y);
					MLV_draw_filled_rectangle(pos_x + 141 , pos_y  - 17, 10, 10, MLV_COLOR_BLACK);
					MLV_draw_text(pos_x + 35, pos_y - 20, "Points restants %d", MLV_COLOR_GREEN, 5-cmp);
					MLV_draw_text(pos_x + 55, pos_y + 7*20, "UPGRADE", MLV_COLOR_WHITE);
					MLV_actualise_window();
				}

			}while(pos > 0);

			break;

		}
		else if(sym == 'e')
			break;
	}
}

void dessine_magic_attaque(Player P, Gate G, char dir, int width_cell, int height, int width){
	int x, y, i = 0, j = 0;
	char proj;
	
	switch(dir){
		case 'z': x = 0; y = -1; proj = '^'; break;
		case 's': x = 0; y = 1; proj = 'v'; break;
		case 'd': x = 1; y = 0; proj = '>'; break;
		case 'q': x = -1; y = 0; proj = '<'; break;
		default : fprintf(stderr, "direction inconnue \n"); exit(1);
	}

	while(G.gate[P.pos.y + i][P.pos.x + j].type != WALL ){
		MLV_draw_text(((width/2) + j) * width_cell , ((height/2) + i) * width_cell, "%c", MLV_COLOR_CYAN, proj);
		j+=x;
		i+=y;
	}
}

void dessine_data(int pos_x, int pos_y){
	int i;
	for(i = 0; i < data_size; i++){
		MLV_draw_text(pos_x, pos_y + i*25, data[i], MLV_COLOR_WHITE); 
	}
}

int enter_name(char *name){
	MLV_Input_box *input_box;
	MLV_Event event;
	char *tmp,*tmp2;
	tmp2 =(char*) malloc(50*sizeof(char));
	*tmp2 = '\0';
	int x=-1,y=-1;
	MLV_Button_state state;

	input_box = MLV_create_input_box( (TAILLE_X/2) + 50 ,(TAILLE_Y/2) -50, 200, 30, MLV_COLOR_WHITE, MLV_COLOR_WHITE,MLV_COLOR_BLACK, "NOM : ");
	MLV_draw_filled_rectangle((TAILLE_X/2) - 30,(TAILLE_Y/2)+50, 60 , 30,MLV_COLOR_WHITE);
	MLV_draw_text((TAILLE_X/2)-30,(TAILLE_Y/2)+57,"VALIDER",MLV_COLOR_BLACK);
	MLV_draw_filled_rectangle((TAILLE_X/2) - 30,(TAILLE_Y/2)+150, 60 , 30,MLV_COLOR_WHITE);
	MLV_draw_text((TAILLE_X/2)-30,(TAILLE_Y/2)+157,"QUITTER",MLV_COLOR_BLACK);
	MLV_draw_text( (TAILLE_X/2)+65 , (TAILLE_Y/2) ,"Nom saisie : ", MLV_COLOR_WHITE);

	do{
		MLV_draw_filled_rectangle((TAILLE_X/2) + 150,(TAILLE_Y/2), 200 , 30,MLV_COLOR_BLACK);
		MLV_draw_text(TAILLE_X/2 + 150 , (TAILLE_Y/2),tmp2, MLV_COLOR_WHITE);
		MLV_draw_all_input_boxes();
		event = MLV_get_event( NULL, NULL, NULL,&tmp, &input_box, &x, &y, NULL,&state );
		
		if((x >= (TAILLE_X/2)-30 && x <= (TAILLE_X/2)+30) && ( y >= (TAILLE_Y/2)+50 && y <= (TAILLE_Y/2)+80 ))
			MLV_draw_text((TAILLE_X/2)-30,(TAILLE_Y/2)+57,"VALIDER",MLV_COLOR_RED);
		
		else
			MLV_draw_text((TAILLE_X/2)-30,(TAILLE_Y/2)+57,"VALIDER",MLV_COLOR_BLACK);
		
		if((x >= (TAILLE_X/2)-30 && x <= (TAILLE_X/2)+30) && ( y >= (TAILLE_Y/2)+150 && y <= (TAILLE_Y/2)+180 ))
			MLV_draw_text((TAILLE_X/2)-30,(TAILLE_Y/2)+157,"QUITTER",MLV_COLOR_RED);
		
		else
			MLV_draw_text((TAILLE_X/2)-30,(TAILLE_Y/2)+157,"QUITTER",MLV_COLOR_BLACK);
		
		MLV_actualise_window();
		
		if(event == MLV_INPUT_BOX){
			free(tmp2);			
			tmp2 = tmp;
		}

		if(event == MLV_MOUSE_BUTTON &&  ((x >= (TAILLE_X/2)-30 && x <= (TAILLE_X/2)+30) && ( y >= (TAILLE_Y/2)+50 && y <= (TAILLE_Y/2)+80)))
			break;

		if(event == MLV_MOUSE_BUTTON &&  ((x >= (TAILLE_X/2)-30 && x <= (TAILLE_X/2)+30) && ( y >= (TAILLE_Y/2)+150 && y <= (TAILLE_Y/2)+180))){
			MLV_free_input_box(input_box);
			free(tmp2);
			return 1;
		}

	}while(1);

	strcpy(name, "sauvegarde/");
	strcat(name, tmp2);
	MLV_free_input_box(input_box);
	free(tmp2);

	return 0;
}

int menu(Tower *T, Player *P, int *current_level){
	int x,y;
	char name[50];
	MLV_Event event;
	MLV_Button_state state;

	MLV_draw_text((TAILLE_X/2)-25,(TAILLE_Y/2)-25,"JOUER",MLV_COLOR_WHITE);
	MLV_draw_text((TAILLE_X/2)-25,(TAILLE_Y/2),"CHARGER",MLV_COLOR_WHITE);
	MLV_draw_text((TAILLE_X/2)-25,(TAILLE_Y/2)+25,"QUITTER",MLV_COLOR_WHITE);
	
	MLV_actualise_window();

	while(1){

		event = MLV_get_event( NULL, NULL, NULL,NULL,NULL, &x, &y, NULL,&state);
		if((x>=(TAILLE_X/2)-25) && (x<=(TAILLE_X/2)+40) && (y>=(TAILLE_Y/2)-35) && (y<=(TAILLE_Y/2)-15)){
			MLV_draw_text((TAILLE_X/2)-25,(TAILLE_Y/2)-25,"JOUER",MLV_COLOR_RED);
			if(event == MLV_MOUSE_BUTTON && state == 0 ){
				MLV_clear_window(MLV_COLOR_BLACK);
				return 1;
			}
		}
	
		else{

			if((x>=(TAILLE_X/2)-25) && (x<=(TAILLE_X/2)+40) && (y>=(TAILLE_Y/2)+15) && (y<=(TAILLE_Y/2)+35)){
				MLV_draw_text((TAILLE_X/2)-25,(TAILLE_Y/2)+25,"QUITTER",MLV_COLOR_RED);
				if(event == MLV_MOUSE_BUTTON && state == 0){
					MLV_clear_window(MLV_COLOR_BLACK);
					return 0;
				}
			}
			else{

				if((x>=(TAILLE_X/2)-25) && (x<=(TAILLE_X/2)+100) && (y>=(TAILLE_Y/2)-10) && (y<=(TAILLE_Y/2)+10)){
					MLV_draw_text((TAILLE_X/2)-25,(TAILLE_Y/2),"CHARGER",MLV_COLOR_RED);
					if(event == MLV_MOUSE_BUTTON && state == 0){
						MLV_clear_window(MLV_COLOR_BLACK);
     				    MLV_draw_text(150, 125, "NOM DES SAUVEGARDE(S) : ", MLV_COLOR_WHITE);
     					dessine_data(150, 150);
     				do{
     					if(enter_name(name))
     						break;
     					if(!load(T, P, current_level, name))
     						return 2;
     					MLV_draw_text(10, 10, "Chargement echoué aucune sauvegarde de ce nom", MLV_COLOR_RED);
     				}while(1);							
						MLV_clear_window(MLV_COLOR_BLACK);
						MLV_draw_text((TAILLE_X/2)-25,(TAILLE_Y/2)-25,"JOUER",MLV_COLOR_WHITE);
						MLV_draw_text((TAILLE_X/2)-25,(TAILLE_Y/2),"CHARGER",MLV_COLOR_WHITE);
						MLV_draw_text((TAILLE_X/2)-25,(TAILLE_Y/2)+25,"QUITTER",MLV_COLOR_WHITE);
					}
				}
				else{
					MLV_draw_text((TAILLE_X/2)-25,(TAILLE_Y/2)-25,"JOUER",MLV_COLOR_WHITE);
					MLV_draw_text((TAILLE_X/2)-25,(TAILLE_Y/2),"CHARGER",MLV_COLOR_WHITE);
					MLV_draw_text((TAILLE_X/2)-25,(TAILLE_Y/2)+25,"QUITTER",MLV_COLOR_WHITE);
				}
			}
		}
		MLV_actualise_window();
	}
}

int deplace_player(Tower *T, Player *P, MLV_Keyboard_button sym, int *current_level){
	switch(sym){
		case 'z': 
			return next_cell_action_player(T, P, P->pos.x, P->pos.y - 1, current_level);
		case 'd': 
			return next_cell_action_player(T, P, P->pos.x + 1, P->pos.y, current_level);			
		case 'q': 
			return next_cell_action_player(T, P, P->pos.x - 1, P->pos.y, current_level);			
		case 's': 
			return next_cell_action_player(T, P, P->pos.x, P->pos.y + 1, current_level);		
		default : fprintf(stderr, "deplacement non reconnu, sym = %d\n", sym); exit(1);
	}
}

MLV_Color quality_to_color(int quality){
	if(quality <=  3)
		return MLV_COLOR_CYAN;
	if(quality <= 6)
		return MLV_COLOR_RED;
	if(quality <= 9)
		return MLV_COLOR_PURPLE;
	
	return MLV_COLOR_WHITE;
}

int Majin_vegeta(){

	int i;
	char chemin[50]="vegeta/x.png";
	MLV_Image *image;
	MLV_Sound* sound;
	
	MLV_init_audio();
	sound = MLV_load_sound( "vegeta/vegetassj.ogg" );
	MLV_play_sound(sound,4);
	MLV_wait_milliseconds(20);

	for(i = 0; i < 16; i++){
		chemin[7]=i+'a';
		image = MLV_load_image(chemin);
		MLV_resize_image_with_proportions(image, TAILLE_X, TAILLE_Y);
		MLV_draw_image(image, 0, 100);
		MLV_actualise_window();
		MLV_wait_milliseconds(120);
		MLV_free_image( image );
	}	

	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_stop_all_sounds();
	MLV_free_sound( sound );
	MLV_free_audio();
	MLV_actualise_window();

	return 1;
}