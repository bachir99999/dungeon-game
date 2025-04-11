#include "../include/fichier.h"

int data_size = 0;

int ajout_stat(const char *name){
	/*Ajoute à data un nouvel element s il y en a moins que 10*/
	if(data_size < 25){
		strcpy(data[data_size], name);
		data_size++;
	}
	return 0;
}

int fn(const char *fpath, const struct stat *sb, int typeflag){
	/*si le type fichier lu est FTW_F alors il y a lancement de la fonction ajout_stat sur lui*/
	if(typeflag == FTW_F)
		ajout_stat(fpath);
	return 0;
}

void affiche_data(){
	int i;
	for(i = 0; i < data_size; i++){
		printf("%s\n", data[i]);
	}
}

int save(Tower *T, Player *P, int *current_level,char *name){
	if(name[11] == '\0')
		strcat(name, "default_save");

	printf("%s\n", name);

	FILE *fic = fopen(name, "wb");

	
	if(NULL == fic){
		fprintf(stderr, "fichier est null\n");
		exit(1);
	}

	fwrite(T, sizeof(Tower), 1, fic);
	fwrite(P, sizeof(Player), 1, fic);
	fwrite(current_level, sizeof(int), 1, fic);

	fclose(fic);

	return 0;
}

int load(Tower *T, Player *P, int *current_level, char *name){
	if(name[11] == '\0')
		strcat(name, "default_save");

	printf("%s\n", name);

	FILE *fic = fopen(name, "rb");
	
	if(NULL == fic){
		return 1;
	}

	fread(T, sizeof(Tower), 1, fic);
	fread(P, sizeof(Player), 1, fic);
	fread(current_level, sizeof(int), 1, fic);

	fclose(fic);

	return 0;
}