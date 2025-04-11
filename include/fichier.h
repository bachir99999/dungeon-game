#ifndef FICHIER_H
#define FICHIER_H
#include <ftw.h>
#include <string.h>

char data[25][150];/*stock le nom des fichiers dans le repertoire sauvegarde*/
extern int data_size; /*le nombre de fichier stocké dans data*/

#include "game.h"

int ajout_stat(const char *name);
/**
Ajoute le nom d'un fichier dans le tableau de tableau de char data
@param name nom du fichier
@return 0
**/

int fn(const char *fpath, const struct stat *sb, int typeflag);
/**
Apelle ajout_stat si le typeflag est celui d un fichier
@param fpath chemin du fichier recontré
@param sb structure corellé à ftw voir man ftw
@param typeflag type de fichier rencontré
@return 0
**/

void affiche_data();
/**
Affiche le tableau de tableau data sur stdout
**/


int save(Tower *T, Player *P, int *current_level,char *name);
/**
Sauvegarde l etat des structures Tower et Player ainsi l etage dans le quel se trouve le joueur dans un fichier name 
@param T structure de la Tour correspondant à un tableau de 10 structure Gate
@param P structure du Joueur contenant ses attributs, ses possesions et son etat
@param current_level le niveau dans le quel se trouve le joueur
@param name nom du fichier dans le quel il sera sauvegardé
@return 0
**/


int load(Tower *T, Player *P, int *current_level, char *name);
/**
Charge l etat des structures Tower et Player ainsi l etage dans le quel se trouve le joueur dans un fichier name sil existe sinon ne fait rien
@param T structure de la Tour correspondant à un tableau de 10 structure Gate
@param P structure du Joueur contenant ses attributs, ses possesions et son etat
@param current_level le niveau dans le quel se trouve le joueur
@param name nom du fichier dans le quel la fonction essaiyera de trouver la sauvegarde
@return 0 si le chargmeent a été effectué sinon 1
**/

#endif