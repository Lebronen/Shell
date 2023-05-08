#include "../include/commande.h"

#include <stdio.h>

int main(void){
	noeud *courant;
	noeud *racine;
	FILE* fp = fopen("../test.txt", "r");
	racine = new_node(NULL);
	racine->est_dossier = true;
	racine->nom[0] = 0;
	racine->racine = racine;
	courant = racine;
	if(fp != NULL){
		char buffer[1024];
		while(!feof(fp)){
			if(fgets(buffer, sizeof(buffer) - 1, fp) != NULL){
				printf("%s", buffer);
			}
		}
		puts("");
		fclose(fp);
	}
	mkdir("ronen", courant);
	ls(courant);
	//courant = cd("ronen", courant);
	touch("ronen/yohan", courant);
	touch("ronen/duo_de_fou", courant);
	touch("ronen/jojo", courant);
	//ls(courant);
	//courant = cd("..", courant);
	rm(courant, "ronen/yohan");
	courant = cd("ronen", courant);
	ls(courant);
	free(racine);
	return 0;
}

noeud	*new_node(noeud *racine)
{
	noeud *n;

	n = malloc(sizeof(noeud ));

	n->est_dossier = false;
	n->pere = NULL;
	n->fils = NULL;
	n->racine = racine;
	return n;
}

char *up_str(char *s)
{
	char *t = malloc(strlen(s));
	for (int i = 0; i < strlen(s); i++)
	{
		t[i] = s[i] - 32;
	}
	return t;
}
