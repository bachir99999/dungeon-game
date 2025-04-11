#include "../include/graph.h"

int main(void){
	
	int current_level = 1, stat_action, res_menu;
	char name[50];
	srand(time(NULL));
	Tower T;
	Player P;
	MLV_Keyboard_button sym = MLV_KEYBOARD_NONE, last_depl = 'z';
	MLV_Button_state state;

	ftw("sauvegarde/", fn, 25);
	MLV_create_window("Gate","GATE", (WIDTH+1) * 20, (HEIGHT+1) * 20);	
     Majin_vegeta();
	res_menu = menu(&T, &P, &current_level);

	if(res_menu == 1){
		T = generate_tower();
		P = init_player();
		place_player(&(T.tower[current_level]), &P, HEIGHT/2, WIDTH/2);
	}

	if(res_menu != 0){
	dessine_gate(T.tower[current_level], P, 'z');
	MLV_draw_text(TAILLE_X/2 - 125, TAILLE_Y/2 - 5, "CLIQUER POUR CONTINUER", MLV_COLOR_RED); 
	MLV_actualise_window();
	MLV_wait_mouse(NULL , NULL);
	

	MLV_clear_window(MLV_COLOR_BLACK);
     dessine_pov_player(T.tower[current_level], P, WIDTH/3, HEIGHT/3, 'z', 60);
     dessine_header(P, current_level);
	MLV_actualise_window();
	
	while(1){

		if(P.Hp <= 0){
			MLV_clear_window(MLV_COLOR_BLACK);
			MLV_draw_text(TAILLE_X/2 - 25, TAILLE_Y/2 - 5, "PERDUE", MLV_COLOR_RED); 
			MLV_draw_text(TAILLE_X/2 - 115, TAILLE_Y/2 + 10, "CLIQUER POUR CONTINUER", MLV_COLOR_RED);
			MLV_actualise_window(); 
			MLV_wait_mouse(NULL , NULL);
			break;
		}

		MLV_get_event(&sym, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);

     	if((sym == 'z' || sym == 's' || sym == 'q' || sym == 'd') && state == 0){
     		stat_action = deplace_player(&T, &P, sym, &current_level);
     		if(stat_action == 1){
				MLV_draw_text(20, 70, "sac plein", MLV_COLOR_RED); 
				MLV_actualise_window();
				continue;
     		}
     		else if(stat_action == 2) continue;

     		MLV_clear_window(MLV_COLOR_BLACK);
     		dessine_pov_player(T.tower[current_level], P, WIDTH/3, HEIGHT/3, sym, 60);
     		dessine_header(P, current_level);
     		MLV_actualise_window();
     		MLV_wait_milliseconds(100);
     		end_turn(&P);
     		last_depl = sym;
     		
     	}

     	else if((sym == 'p' || sym == MLV_KEYBOARD_SPACE || sym == 'm' || sym == 'i' || sym == 'c' || sym == 'l') && state == 0){

     		if(sym == 'i' && state == 0){
     			MLV_clear_window(MLV_COLOR_BLACK);
     			dessine_bag(P, TAILLE_X/2, TAILLE_Y/2);
     			dessine_player_equip(P, TAILLE_X/2, TAILLE_Y/2);
     			MLV_actualise_window();

     			select_item_in_inventory(&P, TAILLE_X/2, TAILLE_Y/2);
     			sym = MLV_KEYBOARD_NONE;

     		}

     		if(sym == 'p'){
     			MLV_clear_window(MLV_COLOR_BLACK);
     			select_upgrade(&P, TAILLE_X/4, TAILLE_Y/4);
     			sym = MLV_KEYBOARD_NONE;
     		}

     		if(sym == MLV_KEYBOARD_SPACE){
     			if(magic_attaque(&P, &(T.tower[current_level]), last_depl))
     				continue;
     			dessine_magic_attaque(P, T.tower[current_level], last_depl, 60, HEIGHT/3, WIDTH/3);
     			MLV_actualise_window();
     			MLV_wait_milliseconds(100);
     		}

     		if(sym == 'm'){
     			MLV_clear_window(MLV_COLOR_BLACK);
     			MLV_draw_text(150, 125, "NOM DES SAUVEGARDE(S) : ", MLV_COLOR_WHITE);
     			dessine_data(150, 150);
     			MLV_draw_text(TAILLE_X/2 - 75, 10, "MENU DE SAUVEGARDE", MLV_COLOR_GREEN);
     			if(!enter_name(name)){
     				save(&T, &P, &current_level, name);
     				data_size = 0;
     				ftw("sauvegarde/", fn, 25);
     			}
     			
     			sym = MLV_KEYBOARD_NONE;
     		}

     		if(sym == 'c'){
     			MLV_clear_window(MLV_COLOR_BLACK);
     			MLV_draw_text(150, 125, "NOM DES SAUVEGARDE(S) : ", MLV_COLOR_WHITE);
     			dessine_data(150, 150);
     			MLV_draw_text(TAILLE_X/2 - 75, 10, "MENU DE CHARGEMENT", MLV_COLOR_GREEN);
     			do{
     				if(enter_name(name) || !load(&T, &P, &current_level, name))
     					break;
     				
     				MLV_draw_text(10, 10, "Chargement echoué aucune sauvegarde de ce nom",MLV_COLOR_RED);

     			}while(1);
     			sym = MLV_KEYBOARD_NONE;
     		}

     		if(sym == 'l')
     			break;
     		
     		MLV_clear_window(MLV_COLOR_BLACK);
     		dessine_pov_player(T.tower[current_level], P, WIDTH/3, HEIGHT/3, last_depl, 60);
     		dessine_header(P, current_level);
     		MLV_actualise_window();
     	}
	}
	}

	MLV_free_window();

	return 0;
}