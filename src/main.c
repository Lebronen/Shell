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
	FILE* fp = fopen("test-err2.txt", "r");
	if(fp != NULL){
		char buffer[1024];
		while(!feof(fp)){
			if(fgets(buffer, sizeof(buffer) - 1, fp) != NULL){
				courant = commande(buffer, racine, courant);
			}
		}

		fclose(fp);
	}
	liste_noeud *fils = racine->fils;
	liste_noeud *tmp;
	while (fils)
	{
		tmp = fils->succ;
		rm_free(fils);
		fils = tmp;
	}
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

noeud *commande(char *s, noeud *racine, noeud *courant)
{
	if (in_str(s, '\n'))
		s[strlen(s) - 1] = 0;
	//printf("%s\n", s);
	if (!strncmp(s, "mkdir", 5))
		mkdir(s + 6, courant);
	else if (!strncmp(s, "ls", 2))
	{
		ls(s + 3, courant);
		puts("");
	}
	else if (!strncmp(s, "touch", 5))
		touch(s + 6, courant);
	else if (!strncmp(s, "rm", 2))
	{
		rm(courant, s + 3);
	}
	else if (!strncmp(s, "print", 5))
	{
		print(courant);
		puts("");
	}
	else if (!strncmp(s, "cd", 2))
		courant = cd(s + 3, courant);
	else if (!strncmp(s, "pwd", 3))
	{
		pwd(courant);
		printf("\n\n");
	}
	else if (!strncmp(s, "cp", 2))
	{
		cp(courant, s + 3);
	}
	else if (!strncmp(s, "mv", 2))
	{
		mv(courant, s + 3);
	}
	else if (!*s)
		return courant;
	else
		printf("commande non reconnue\n");
	return courant;
}

