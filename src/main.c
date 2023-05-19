#include "../include/commande.h"

#include <stdio.h>

int main(int argc, char **argv){

	//si aucun fichier n'est donné en argument, le programme quitte directement
	if (argc <= 1) {
	printf("veuillez donner un fichier d'instructions en paramètre\n");
	return 0;
	}

	//initialisation de la racine et du noeud courant
	noeud *courant;
	noeud *racine;
	racine = new_node(NULL);
	racine->est_dossier = true;
	racine->nom[0] = 0;
	racine->racine = racine;
	courant = racine;

	//ouverture du fichier
	FILE* fp = fopen(argv[1], "r");
	// si le fichier n'est pas trouvé, le programme quitte
	if (fp < 0) {
	printf("fichier non trouvé");
	return 0;
	}
	//lecture du fichier ligne par ligne
	if(fp != NULL){
		char buffer[1024];
		while(!feof(fp)){
			if(fgets(buffer, sizeof(buffer) - 1, fp) != NULL){
				//analyse et éxécution des commandes donnés par le fichier
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
	//l'instruction est comparé aux instructions existantes puis, éxécutés si elles sont reconnues
	
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

