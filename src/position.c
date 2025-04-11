#include "../include/position.h"

int in_gate(int i, int j){
	if(i <= 0 || j <= 0 || i >= (HEIGHT - 1) || j >= (WIDTH - 1))
		return 0;
	return 1;
} 

ListePosition alloc_position(int x, int y){
	ListePosition Pos = (Position*)malloc(sizeof(Position));
	if(NULL == Pos){
		fprintf(stderr, "depassement memoire\n");
		exit(1);
	}

	Pos->y = y;
	Pos->x = x;
	Pos->suivant = NULL;
	return Pos;
}

int add_position(ListePosition *toexpand, int x, int y){
	if(!in_gate(y, x)){
		return 2;
	}
	ListePosition tmp = *toexpand, pos = alloc_position(x, y);
	if(NULL == *toexpand){
		*toexpand = pos;
		return 1;
	}
	for(; tmp->suivant != NULL; tmp = tmp->suivant);
	tmp->suivant = pos;
	return 0;
}

int delete_position(ListePosition *toexpand, int x, int y){
	ListePosition tmp = *toexpand, tmp2;
	if(NULL == tmp){
		fprintf(stderr, "toextand est null\n");
		exit(1);
	}
	if(tmp->x == x && tmp->y == y){
		*toexpand = (*toexpand)->suivant;
		free(tmp);
		return 1;
	}
	for(; tmp->suivant != NULL; tmp = tmp->suivant){
		if(tmp->suivant->x == x && tmp->suivant->y == y){
			tmp2 = tmp->suivant;
			tmp->suivant = tmp->suivant->suivant;
			free(tmp2);
			return 2;
		}
	}

	fprintf(stderr, "position non trouvé dans la liste x = %d y = %d\n", x, y);
	return 0;
}

int free_lst(ListePosition *lst){

	if(*lst == NULL)
		return 0;

	if((*lst)->suivant == NULL){
		free(*lst);
		*lst=NULL;
		return 1;
	}
	else
		free_lst(&((*lst)->suivant));

	free(*lst);
	*lst = NULL;
	return 1;
}

ListePosition dist_x(int dist, int x, int y){
	ListePosition lst = alloc_position(x, y);
	int i, j;
	for(i = (-1) * dist; i <= dist; i++){
		for(j = (-1) * dist; j <= dist; j++){
			if(abs(i) + abs(j) == dist)
				add_position(&lst, j + x, y + i);
		}
	}
	delete_position(&lst, x, y);

	return lst;
}

Position rand_position(ListePosition *lst, int size){
	ListePosition tmp;
	int tmp_pos, i;
	if(size <= 0){
		fprintf(stderr, "size <= 0, size = %d rand position erreur \n", size);
		exit(1);
	}
	tmp = *lst;
	if(NULL == tmp){
		fprintf(stderr, "lst est vide\n");
		exit(1);
	}
	tmp_pos = rand()%size;

	for(i = 0; i < tmp_pos; i++)
		tmp = tmp->suivant;

	return *tmp;
}

int in_toexpand(ListePosition toexpand, Position P){
	for(; toexpand != NULL; toexpand = toexpand->suivant)
		if(P.x == toexpand->x && P.y == toexpand->y)
			return 1;
	return 0;
}

void print_list(ListePosition lst){
	int i = 0;
	if(NULL == lst)
		printf("pile nulle");
	for(; lst != NULL; lst = lst->suivant){
		printf("x = %d, y = %d--->", lst->x, lst->y);
		i++;
	}
	printf("\n");
	printf("nbelem in lst = %d\n", i);
}
