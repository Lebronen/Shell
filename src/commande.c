#include "../include/commande.h"

noeud *cd(char* s,noeud* courant){ // déplace le noeud courant dans le dossier donné en argument
    char *sub;

    // si aucun argument n'est donné, on retourne à la racine
    if(!*s){
        courant=courant->racine;
        return courant;
    }
    //si le chemin du dossier commence par .., on reviens en arrière dans l'arborescence puis on appelle cd sur le reste du chemin
    if(!strncmp("..",s, 2)){
        if(courant==courant->racine) return courant;
        else{
            courant=courant->pere;
            if (!in_str(s, '/'))
                return courant;
            return cd(s + 3,courant);
        }
    }
    //si le chemin commence par /, c'est un chemin absolu. On le fait donccommencer à la racine
    if(*s=='/'){
        courant=courant->racine;
        return cd(s+1,courant);
    }
    else{
        if(courant->fils!=NULL){
            liste_noeud* tmp=courant->fils;
            //on cherche le dossier dans l'arobrescence
            while(tmp!=NULL && strncmp(tmp->no->nom,s, subslash(s))){
                tmp=tmp->succ;
            }
            //s'il existe et est un dossier, on y déplace le noeud courant
            if(tmp && tmp->no->est_dossier){
                courant=tmp->no;
                if(!*(s+subslash(s)))
                {
                    return courant;
                }
                return cd(s+subslash(s)+1,courant);
            }else{ // s'il n'existe pas ou n'est pas un dossier on quitte la fonction
                printf("dossier non trouvé\n\n");
                return courant;
            }
        }else{
            return courant;
        }
    }

}

void pwd(noeud* courant){//fonction affichant le chemin absolue de la racine jusqu'au noeud courant.
    if (!courant)//si le noeud courant est NULL la fonction fait rien
        return ;
    if(courant!=courant->racine){//si le noeud courant n'est pas la racine on fait un appel récursif puis onaffiche le nom du noeud courantsuivie de "/s"
        pwd(courant->pere);
        printf("%s/",courant->nom);
    }else{// si le noeud courant est la racine on affiche juste le nom.
        printf("%s/",courant->nom);
    }
}
noeud *touch(char* s,noeud* courant){ // fonction créant un ficher dans le dossier donné en argument

    if(!courant->est_dossier){//si le noeud n'est pas un dossier on affiche un messade d'erreur et on ne fait rien
        printf("pas un dossier\n");
        return NULL;
    }
    noeud* nouveau;//on créer un nouveau noeud et on initialise ces objets
    liste_noeud *liste_fils;
    liste_noeud *liste_nouveau;
    char *dossier;
    char *nom;

    noeud* parent=courant;
    if (in_str(s, '/'))
    { //si l'argument est chemin contenant plusieurs dossiers, on y déplace d'abord le noeud courant
        dossier = slash(s, true);
        parent = cd(dossier, parent);
        free(dossier);
    }
    nouveau = new_node(parent->racine);
    nom = slash(s, false);//on s'assure que le nom soit le dernier string aprés un "/" si c'est un string chemin absolue ou chemincontenant plusieur dossier
    strcpy(nouveau->nom, nom);
    free(nom);
    nouveau->pere = parent;
    liste_nouveau = malloc(sizeof(liste_noeud));
    liste_nouveau->no = nouveau;
    liste_nouveau->succ = NULL;
    if(parent->fils != NULL){//si le courant (le pére du nouveau fichier) a des fils, on parcourt tous ces fils pour ensuite rajouter le nouveau fils.
        liste_fils = parent->fils;
        while(liste_fils->succ != NULL){
            liste_fils = liste_fils->succ;
        }
        liste_fils->succ = liste_nouveau;
    }else{//dans le cas contraire on met juste directement le nouveau fichier comme fils de courant
        parent->fils = liste_nouveau;
    }

    return nouveau;
}
noeud *mkdir(char* s,noeud* courant){ //fonction créant un dossier dans le dossier donné en argument
   noeud *dossier = touch(s, courant);
   dossier->est_dossier = true; // vu qu'on crée un dossier, on met le booléen est_dossier à true
    
    return dossier;
}

void ls(char *s, noeud *courant)
{
    //si l'argument est chemin contenant plusieurs dossiers, on y déplace d'abord le noeud courant
    noeud *tmp;

    tmp = courant;
    if (*s)
        tmp = cd(s,tmp);
    ls_courant(tmp);
}

void ls_courant(noeud* courant){ // commande affichant le contenu d'un dossier

    if(courant!=NULL){
        int a=5; // on n'affiche que cinq éléments par ligne pour rendre l'affichage plus lisible
        liste_noeud* b=courant->fils;
        while(b!=NULL){
            
            printf("   %s",b->no->nom);
            if(a){
                    a--;
            }else{
                a=5;
                printf("\n");
            }
            b=b->succ;

        }
        printf("\n");
    }
}

noeud *rm(noeud *courant,char *s){ // fonction supprimant l'élément donné
    char *tmp_slash_2;
    char *tmp_slash;
    noeud* tmp1=courant;
    tmp_slash_2 = slash(s, false);
    if (in_path(courant, tmp_slash_2)) // si la commande tente de supprimer un dossier dans le quel se trouve le noeud courant, on
    // quitte la fonction
    {
        printf("impossible de supprimer un dossier dans lequel vous êtes actuellement\n");
        free(tmp_slash_2);
        return courant;
    }
    if (in_str(s, '/'))
    {  //si l'argument est chemin contenant plusieurs dossiers, on y déplace d'abord le noeud courant
        tmp_slash = slash(s, true);
        tmp1 = cd(tmp_slash,tmp1);
        free(tmp_slash);
    }
    liste_noeud* tmp=tmp1->fils;
    liste_noeud* tmp2= NULL;
    //on cherche l'élément à supprimer dans l'arborescence
    while(tmp && strcmp(tmp_slash_2,tmp->no->nom)){
        tmp2 = tmp;
        tmp = tmp->succ;
    }
    free(tmp_slash_2);
    if (!tmp)
        return courant;
    //avant de supprimer définitivement l'élément, on refait les liens entre ses noeuds voisins
    if (!tmp2)
    {
        tmp1->fils = tmp->succ;
    }
    else
    {
        tmp2->succ = tmp->succ;
    }
    rm_free(tmp);
    
    return courant;
}


void    rm_free(liste_noeud *tmp)
{ // suppression du noeud et libération de son emplacement mémoire
       
    liste_noeud *fils = tmp->no->fils;
    liste_noeud *suc;
    while (fils)
    {
        suc = fils->succ;
        rm_free(fils);
        fils = suc;
    }
    free(tmp->no);
    free(tmp);
}

void print(noeud* courant){//on rapelle la fonction a la racine
    print_suite(courant->racine);
}
void print_suite(noeud* a){//fonction qui affiche tous l'arborescence
    printf("Noeud ");
    if(a==a->racine){//si le noeud est la racine on ne met pas de nom aprés le noeud
            printf("/");
        if(a->est_dossier){// si a est un dossier on affiche (d) et son nombre de fils
            printf(" (d), %d fils:",nbr_fils(a));
            liste_noeud* tmp=a->racine->fils;
            while(tmp!=NULL){//on parcours tous les fils du dossier et on affiche si c'est un fichier (avec (f)) ou si c'est un dossier (avec (d))
                if(tmp->no->est_dossier){
                    printf(" %s (d)",tmp->no->nom);
                }else{
                    printf(" %s (f)",tmp->no->nom);
                }
                tmp=tmp->succ;
            }
            printf("\n");
            tmp=a->racine->fils;
            while(tmp!=NULL){//ensuite on rapelle la fonction avec tous ces fils 
                print_suite(tmp->no);
                tmp=tmp->succ;
            }
        }else{// si a n'est pas un dossier onrenvoie que c'est un fichier et qu'il a 0 fils
            printf(" (f), 0 fils \n"); 
        }
    }else{// quand ce a n'est pas la racine 
          printf("%s",a->nom);

        if(a->est_dossier){// quand a est un dossier on a l'affichage avec (d) son pére et son fils 
            printf(" (d), pére: %s, %d fils:",*(a->pere->nom) ? a->pere->nom : "/",nbr_fils(a));
            liste_noeud* tmp=a->fils;
            //int c=0;
            while(tmp!=NULL){//on parcours ensuite ces fils en affichant leur om en fonction de si c'est un fichier ou un dossier
                //c++;
                if(tmp->no->est_dossier){
                    printf(" %s  (d)",tmp->no->nom);
                }else{
                    printf(" %s (f)",tmp->no->nom);
                }
                tmp=tmp->succ;
            }
            printf("\n");
            tmp=a->fils;
            while(tmp!=NULL){//on rapelle la fonction récursivement sur ces fils aussi
                print_suite(tmp->no);
                tmp=tmp->succ;
            }
        }else{//quand a n'est qu'un fichier onrenvoie juste l'affichage  dans le cas d'un fichier et on saute la ligne.
            
            printf(" (f),pére: %s, 0 fils \n",a->pere->nom); 
        }
    }
}

void cp(noeud *courant, char *s)
{ // fonction copiant un noeud
    liste_noeud *tmp;
    char *tmp_slash;
    char *tmp_slash2;
    liste_noeud *tmp_2 = NULL;
    char *nom;
    char *nom_2;
    int i;

    noeud *tmp_src = courant;
    noeud *tmp_dest = courant;
    i = argument(s);
    if(!s[i])
    {
        printf("argument manquant\n\n");
        return ;
    }
    // parsing de la chaine de caractère
    char *dest = s + i + 1;
    s[i] = '\0';
    char *src = s;
    if (!src || !dest)
        return ;
    if (in_str(src, '/'))
    {
        tmp_slash = slash(src, true);
        tmp_src = cd(tmp_slash, courant);
        free(tmp_slash);
    }
    if (*dest)
    {
        tmp_slash2 = slash(dest, true);
        tmp_dest = cd(tmp_slash2, courant);
        tmp_2 = tmp_dest->fils;
        nom_2 = slash(dest, false);
        while (tmp_2 && strcmp(tmp_2->no->nom, nom_2))
        {
            tmp_2 = tmp_2->succ;
        }
        if (tmp_2)
            tmp_dest = cd(nom_2, tmp_dest); // si la destination esxiste, on y déplace tmp_dest, sinon on créera une copie
            // de la source en la renommant comme la destination
            free(tmp_slash2);
    }
    tmp = tmp_src->fils;
    nom = slash(src, false);
    while (tmp && strcmp(tmp->no->nom, nom))
    {
        tmp = tmp->succ;
    }
    if (!tmp || strstr(dest, src) || in_path(tmp_dest, nom)) //si la commande tente de copier un élément dans un dossier
    //qu'il contient, on quitte la fonction
    {
        free(nom);
        free(nom_2);
        printf("fichier ou dossier introuvable\n\n");
        return ;
    }
    if (tmp_2)
        cp_bis(tmp->no, tmp_dest, tmp->no->nom);
    else
        cp_bis(tmp->no, tmp_dest, nom_2);
    free(nom_2);
    free(nom);
}

void cp_bis(noeud *tmp, noeud *tmp_dest, char *nom)
{ 
    if (!tmp->est_dossier)
    {

        touch(nom, tmp_dest); // si le noeud est un fichier, on le crée simplement avec touch
    }
    else
    { // si c'est un dossier, on le crée avec mkdir puis on appelle récursivement la fonction sur ses enfants
        noeud *dest =  mkdir(nom, tmp_dest);
        liste_noeud * fils = tmp->fils;
        while (fils)
        {
            cp_bis(fils->no, dest, fils->no->nom);
            fils = fils->succ;
        }
    }
}

void mv(noeud *courant, char *s)
{ // fonction déplacaant un élément
// on copie d'abord l'élément au bon endriot, puis on le supprime de son acien emplacement
    cp(courant, s);
    rm(courant, s);
}