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

noeud	*new_node(noeud *racine);
char *up_str(char *s);
noeud *cd(char* s,noeud* courant);
noeud *touch(char* s,noeud* courant);
void pwd(noeud* courant);
noeud *mkdir(char* s,noeud* courant);
void ls(char *s, noeud* courant);
void ls_courant(noeud* courant);
int subslash(char* s);
char* slash(char* s,bool a);
noeud *rm(noeud *courant,char* s);
bool in_str(char *s, char c);
void    rm_free(liste_noeud *tmp);
void print(noeud* courant);
void print_suite(noeud* a);
int nbr_fils(noeud* a);
noeud *commande(char *s, noeud *racine, noeud *courant);
void cp(noeud *courant, char *s);
void cp_bis(noeud *tmp, noeud *tmp2, char *nom);
int argument(char *s);
void mv(noeud *courant, char *s);
bool in_path(noeud *courant, char *s);

#endif
