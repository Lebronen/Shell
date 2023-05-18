#include "../include/commande.h"

noeud *cd(char* s,noeud* courant){
    char *sub;
    if(!*s){
        courant=courant->racine;
        return courant;
    }
    if(!strncmp("..",s, 2)){
        if(courant==courant->racine) return courant;
        else{
            courant=courant->pere;
            if (!in_str(s, '/'))
                return courant;
            return cd(s + 3,courant);
        }
    }
    if(*s=='/'){
        courant=courant->racine;
        return cd(s+1,courant);
    }
    else{
        if(courant->fils!=NULL){
            liste_noeud* tmp=courant->fils;
            while(tmp!=NULL && strncmp(tmp->no->nom,s, subslash(s))){
                tmp=tmp->succ;
            }
            if(tmp && tmp->no->est_dossier){
                courant=tmp->no;
                if(!*(s+subslash(s)))
                {
                    return courant;
                }
                return cd(s+subslash(s)+1,courant);
            }else{
                printf("dossier non trouvé\n\n");
                return courant;
            }
        }else{
            return courant;
        }
    }

}

void pwd(noeud* courant){
    if (!courant)
        return ;
    if(courant!=courant->racine){
        pwd(courant->pere);
        printf("%s/",courant->nom);
    }else{
        printf("%s/",courant->nom);
    }
}
noeud *touch(char* s,noeud* courant){

    if(!courant->est_dossier){
        printf("pas un dossier\n");
        return NULL;
    }
    noeud* nouveau;
    liste_noeud *liste_fils;
    liste_noeud *liste_nouveau;
    char *dossier;
    char *nom;

    noeud* parent=courant;
    if (in_str(s, '/'))
    {
        dossier = slash(s, true);
        parent = cd(dossier, parent);
        free(dossier);
    }
    nouveau = new_node(parent->racine);
    nom = slash(s, false);
    strcpy(nouveau->nom, nom);
    free(nom);
    nouveau->pere = parent;
    liste_nouveau = malloc(sizeof(liste_noeud));
    liste_nouveau->no = nouveau;
    liste_nouveau->succ = NULL;
    if(parent->fils != NULL){
        liste_fils = parent->fils;
        while(liste_fils->succ != NULL){
            liste_fils = liste_fils->succ;
        }
        liste_fils->succ = liste_nouveau;
    }else{
        parent->fils = liste_nouveau;
    }

    return nouveau;
}
noeud *mkdir(char* s,noeud* courant){
   noeud *dossier = touch(s, courant);
   dossier->est_dossier = true;
    
    return dossier;
}

void ls(char *s, noeud *courant)
{
    noeud *tmp;

    tmp = courant;
    if (*s)
        tmp = cd(s,tmp);
    ls_courant(tmp);
}

void ls_courant(noeud* courant){

    if(courant!=NULL){
        int a=5;
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

noeud *rm(noeud *courant,char *s){
    char *tmp_slash_2;
    char *tmp_slash;
    noeud* tmp1=courant;
    tmp_slash_2 = slash(s, false);
    if (in_path(courant, tmp_slash_2))
    {
        printf("impossible de supprimer un dossier dans lequel vous êtes actuellement\n");
        free(tmp_slash_2);
        return courant;
    }
    if (in_str(s, '/'))
    {
        tmp_slash = slash(s, true);
        tmp1 = cd(tmp_slash,tmp1);
        free(tmp_slash);
    }
    liste_noeud* tmp=tmp1->fils;
    liste_noeud* tmp2= NULL;
    while(tmp && strcmp(tmp_slash_2,tmp->no->nom)){
        tmp2 = tmp;
        tmp = tmp->succ;
    }
    free(tmp_slash_2);
    if (!tmp)
        return courant;
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
{
       
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

void print(noeud* courant){
    print_suite(courant->racine);
}
void print_suite(noeud* a){
    printf("Noeud ");
    if(a==a->racine){
            printf("/");
        if(a->est_dossier){
            printf(" (d), %d fils:",nbr_fils(a));
            liste_noeud* tmp=a->racine->fils;
            while(tmp!=NULL){
                if(tmp->no->est_dossier){
                    printf(" %s (d)",tmp->no->nom);
                }else{
                    printf(" %s (f)",tmp->no->nom);
                }
                tmp=tmp->succ;
            }
            printf("\n");
            tmp=a->racine->fils;
            while(tmp!=NULL){
                print_suite(tmp->no);
                tmp=tmp->succ;
            }
        }else{
            printf(" (f), 0 fils \n"); 
        }
    }else{
          printf("%s",a->nom);

        if(a->est_dossier){
            printf(" (d), pére: %s, %d fils:",*(a->pere->nom) ? a->pere->nom : "/",nbr_fils(a));
            liste_noeud* tmp=a->fils;
            //int c=0;
            while(tmp!=NULL){
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
            while(tmp!=NULL){
                print_suite(tmp->no);
                tmp=tmp->succ;
            }
        }else{
            
            printf(" (f),pére: %s, 0 fils \n",a->pere->nom); 
        }
    }
}

void cp(noeud *courant, char *s)
{
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
            tmp_dest = cd(nom_2, tmp_dest);
            free(tmp_slash2);
    }
    tmp = tmp_src->fils;
    nom = slash(src, false);
    while (tmp && strcmp(tmp->no->nom, nom))
    {
        tmp = tmp->succ;
    }
    if (!tmp || strstr(dest, src) || in_path(tmp_dest, nom))
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

        touch(nom, tmp_dest);
    }
    else
    {
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
{
    cp(courant, s);
    rm(courant, s);
}