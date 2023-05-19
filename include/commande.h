#ifndef COMMANDE_H
#define COMMANDE_H

#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

struct noeud ;
struct liste_noeud ;
struct noeud {
bool est_dossier ;
char nom [100];
struct noeud * pere ;
struct noeud * racine ;
struct liste_noeud * fils ;
};
struct liste_noeud {
struct noeud * no ;
struct liste_noeud * succ ;
};
typedef struct noeud noeud ;
typedef struct liste_noeud liste_noeud ;

//fonctions simulant les commandes linux

noeud *cd(char* s,noeud* courant);
noeud *touch(char* s,noeud* courant);
void pwd(noeud* courant);
noeud *mkdir(char* s,noeud* courant);
void ls(char *s, noeud* courant);
void ls_courant(noeud* courant);
noeud *rm(noeud *courant,char* s);
void    rm_free(liste_noeud *tmp);
void print(noeud* courant);
void print_suite(noeud* a);
void cp(noeud *courant, char *s);
void cp_bis(noeud *tmp, noeud *tmp2, char *nom);
void mv(noeud *courant, char *s);

//fonctions d'aide

int subslash(char* s);
char* slash(char* s,bool a);
bool in_str(char *s, char c);
int nbr_fils(noeud* a);
int argument(char *s);
bool in_path(noeud *courant, char *s);

//fonctions principales appelés dans le main

noeud	*new_node(noeud *racine);
noeud *commande(char *s, noeud *racine, noeud *courant);

#endif
