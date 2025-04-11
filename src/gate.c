#include "../include/gate.h"

int abs(int a){
	return a > 0 ? a : a * (-1);
}

int distance_manathan(int i1, int j1, int i2, int j2){
	return abs(i1 - i2) + abs(j1 - j2);
} 

void print_cell(Celltype C){
	switch(C){
		case WALL : printf("W"); break;
		case ROOM : printf("R"); break;
		case PLAYER : printf("P"); break;
		case MONSTER : printf("M"); break;
		case TREASURE : printf("T"); break;
		case STAIR_UP : printf("U"); break;
		case STAIR_DOWN : printf("D"); break; 
		default :fprintf(stderr, "type inconnu %d", C); break;
	}
}

void print_gate(Gate G){
	int i, j;
	for(i = 0; i < HEIGHT; i++){
		for(j = 0; j < WIDTH; j++){
			print_cell(G.gate[i][j].type);
		}
		printf("\n");
	}
}

Gate init_gate(){
	int i, j;
	Gate tmp;
	for(i = 0; i < HEIGHT; i++){
		for(j = 0; j < WIDTH; j++){
			tmp.gate[i][j].type = WALL;
		}
	}
	tmp.gate[HEIGHT/2][WIDTH/2].type = STAIR_UP;
	return tmp;
}

int admissible(Gate G, int i, int j){
	/*renvoie 0 si la case n'est pas admissible 1 sinon*/
	ListePosition lst_dist1, lst_dist2, tmp;
	int cmp = 0;
	if(G.gate[i][j].type != WALL)
		return 0;
	
	lst_dist1 = dist_x(1, j, i);
	
	for(tmp = lst_dist1; tmp != NULL; tmp = tmp->suivant)
		if(in_gate(tmp->y, tmp->x) && G.gate[tmp->y][tmp->x].type != WALL)
			cmp++;
	free_lst(&lst_dist1);
	if(cmp != 1)
		return 0;
	
	lst_dist2 = dist_x(2, j, i);
	cmp = 0;

	for(tmp = lst_dist2; tmp != NULL; tmp = tmp->suivant)
		if(in_gate(tmp->y, tmp->x) && G.gate[tmp->y][tmp->x].type != WALL)
			cmp++;
	free_lst(&lst_dist2);
	if(cmp > 2)
		return 0;

	return 1;
}

int adj_3wall(Gate G, int i, int j){
	int cnt = 0;
	ListePosition tmp_lst;

	for(tmp_lst = dist_x(1, j, i); tmp_lst != NULL; tmp_lst = tmp_lst->suivant){
		if(G.gate[tmp_lst->y][tmp_lst->x].type == WALL) cnt++;
	}
	return cnt == 3 ? 1 : 0;
}

int surround_cell_by_room(Gate *G, int i, int j){
	int x, y;
	ListePosition surround = NULL, tmp;
	for(y = -1; y < 2; y++){
		for(x = -1; x < 2; x++)
			add_position(&surround, j + x, i + y);
	}
	delete_position(&surround, j, i);

	for(tmp = surround; tmp != NULL; tmp = tmp->suivant){
		if(in_gate(tmp->y, tmp->x) && G->gate[tmp->y][tmp->x].type == WALL)
			G->gate[tmp->y][tmp->x].type = ROOM;
	}

	free_lst(&surround);

	return 0;
}

Gate generate_gate(){
	int size, i, j, quit = 0;
	ListePosition tmp_lst, toexpand = dist_x(1, WIDTH/2, HEIGHT/2);
	Position tmp;
	size = 4;
	Gate G = init_gate();
	
	while(1){
		do{
			if(size == 0){
				quit = 1;
				break;
			}
			tmp = rand_position(&toexpand, size);
			delete_position(&toexpand, tmp.x, tmp.y);
			size--;
		}while(!admissible(G, tmp.y, tmp.x));

		if(quit) break;

		G.gate[tmp.y][tmp.x].type = ROOM;
		
		for(tmp_lst = dist_x(1, tmp.x, tmp.y); tmp_lst != NULL; tmp_lst = tmp_lst->suivant)
			if(in_gate(tmp_lst->y, tmp_lst->x) && !in_toexpand(toexpand, *tmp_lst) && admissible(G, tmp_lst->y, tmp_lst->x)){
				add_position(&toexpand, tmp_lst->x, tmp_lst->y);
				size++;
			}
		
		if(NULL != toexpand)
			continue;
		
		break;
	}
	
	for(i = 0; i < HEIGHT; i++){
		for(j = 0; j < WIDTH; j++){
			if(G.gate[i][j].type == ROOM && adj_3wall(G, i, j))
					G.gate[i][j].type = WALL;
		}
	}

	surround_cell_by_room(&G, HEIGHT/2, WIDTH/2);

	free_lst(&tmp_lst);
	free_lst(&toexpand);

	return G;
}


int adj_1room(Gate G, int i, int j, Position *pos){
	/*renvoie 1 si pos est adjacent a une seul case room 0 sinon*/
	if(G.gate[i][j].type == WALL) return 0;
	int cnt = 0;
	ListePosition lst = dist_x(1, j, i);
	for(; lst != NULL; lst = lst->suivant){
		if(in_gate(lst->y, lst->x) && G.gate[lst->y][lst->x].type != WALL){
			pos->x = lst->x;
			pos->y = lst->y;
			cnt++;
		}
	}
	if(cnt == 1)return 1; 

	return 0;
}

void place_treasur_monster(Gate *G, int stage){
	ListePosition lst_tres = dist_x(1, WIDTH/2, HEIGHT/2), lst_mons = NULL, tmp_lst = NULL;
	Position tmp_pos;
	int i, j, size = 4;
	do{
		if(size == 0){
			fprintf(stderr, "Aucune case ROOM autour de l'escalier montant\n");
			exit(1);
		}
		tmp_pos = rand_position(&lst_tres, size);
		delete_position(&lst_tres, tmp_pos.x, tmp_pos.y);
		size--;
	}while(G->gate[tmp_pos.y][tmp_pos.x].type == WALL);
	G->gate[tmp_pos.y][tmp_pos.x].type = TREASURE;
	G->gate[tmp_pos.y][tmp_pos.x].entity = *generate_treasure(stage, rand()%2);
	free_lst(&lst_tres);
	lst_tres = NULL;

	for(i = 1; i < HEIGHT - 1; i++){
		for(j = 1; j < WIDTH - 1; j++){
			if(adj_1room(*G, i, j, &tmp_pos)){
				add_position(&lst_tres, j, i);
				add_position(&lst_mons, tmp_pos.x, tmp_pos.y);
			}
		}
	}
	for(tmp_lst = lst_tres; tmp_lst != NULL; tmp_lst = tmp_lst->suivant){
		G->gate[tmp_lst->y][tmp_lst->x].type = TREASURE;
		G->gate[tmp_lst->y][tmp_lst->x].entity = *generate_treasure(stage, rand()%2);
	}
	for(tmp_lst = lst_mons; tmp_lst != NULL; tmp_lst = tmp_lst->suivant){
		G->gate[tmp_lst->y][tmp_lst->x].type = MONSTER;
		G->gate[tmp_lst->y][tmp_lst->x].entity = *alloc_monster(1 + (rand()%10)*stage, 1 + (rand()%10)*stage);
	}
	free_lst(&lst_tres);
	free_lst(&lst_mons);
}

void place_player(Gate *G, Player *P, int i, int j){
	ListePosition tmp_lst = dist_x(1, j, i);
	Position tmp_pos;
	int size = 4;
	do{
		if(size == 0){
			fprintf(stderr, "Aucune case ROOM autour de l'escalier montant\n");
			exit(1);
		}
		tmp_pos = rand_position(&tmp_lst, size);
		delete_position(&tmp_lst, tmp_pos.x, tmp_pos.y);
		size--;
	}while(G->gate[tmp_pos.y][tmp_pos.x].type != ROOM);
	G->gate[tmp_pos.y][tmp_pos.x].type = PLAYER;
	free_lst(&tmp_lst);
	P->pos.x = tmp_pos.x;
	P->pos.y = tmp_pos.y;
}

void place_staire_down(Gate *G){
	int i, j;
	while(1){
		i = rand()%HEIGHT;
		j= rand()%WIDTH;
		if(in_gate(i, j) && distance_manathan(i, j, HEIGHT/2, WIDTH/2) >= 25 && G->gate[i][j].type == ROOM){
			G->gate[i][j].type = STAIR_DOWN;
			surround_cell_by_room(G, i, j);
			break;
		}
	}
}

Position stair_down_pos(Gate G){
	int i, j;
	Position pos;
	for(i = 0; i < HEIGHT; i++){
		for(j = 0; j < WIDTH; j++){
			if(G.gate[i][j].type == STAIR_DOWN){
				pos.x = j;
				pos.y = i;
				return pos;
			}
		}
	}
	fprintf(stderr, "pas de stair down dans la gate\n");
	exit(1);
}

Tower generate_tower(){
	Gate G;
	Tower T;
	int i;

	for(i = 1; i < 11; i++){
		G = generate_gate();
		place_treasur_monster(&G, i);
		place_staire_down(&G);
		T.tower[i] = G;
	}

	return T;
}