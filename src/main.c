#include "../include/commande.h"

#include <stdio.h>

int main(void){
	
	noeud *courant;
	noeud *racine;
	racine = new_node(NULL);
	racine->est_dossier = true;
	racine->nom[0] = 0;
	racine->racine = racine;
	courant = racine;
	FILE* fp = fopen("test.txt", "r");
	if(fp != NULL){
		char buffer[1024];
		while(!feof(fp)){
			if(fgets(buffer, sizeof(buffer) - 1, fp) != NULL){
				courant = commande(buffer, racine, courant);
			}
		}

		fclose(fp);
	}
	
	/*
	mkdir("ronen", courant);
	//print(courant);
	//ls("ronen", courant);
	//courant = cd("ronen", courant);
	touch("ronen/yohan", courant);
	touch("ronen/duo_de_fou", courant);
	mkdir("ronen/jojo", courant);
	touch("ronen/jojo/jotaro", courant);
	//ls(courant);
	courant = cd("ronen/jojo", courant);
	ls("", courant);
	//printf("%d\n", subslash("ronen/"));
	courant = cd("..", courant);
	ls("", courant);
*/
	rm_free(racine->fils);
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

noeud *commande(char *s, noeud *racine, noeud *courant)
{
	printf("%s", s);
	if (!strncmp(s, "mkdir", 5))
		mkdir(s + 6, courant);
	else if (!strncmp(s, "ls", 2))
		ls(s + 3, courant);
	else if (!strncmp(s, "touch", 5))
		touch(s + 6, courant);
	else if (!strncmp(s, "rm", 2))
		rm(courant, s + 3);
	else if (!strncmp(s, "print", 5))
		print(courant);
	else if (!strncmp(s, "cd", 2))
		courant = cd(s + 3, courant);
	else if (!strncmp(s, "pwd", 3))
		pwd(courant);
	else
		printf("commande non reconnue\n");

	return courant;
}
