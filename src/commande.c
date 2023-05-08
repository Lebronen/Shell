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
        if(*s=='/'){
            courant=courant->racine;
            return cd(s+1,courant);
        }
    }else{
        if(courant->fils!=NULL){
            liste_noeud* tmp=courant->fils;
            while(tmp!=NULL && strncmp(tmp->no->nom,s, subslash(s) - 1)){
                //printf("%s\n", tmp->no->nom);
                tmp=tmp->succ;
            }
            //printf("fin while\n");
            //printf("%s %s\n", tmp->no->nom, substr(s,0,subslash(s)));
            if(tmp && tmp->no->est_dossier){
               // printf("%s\n",tmp->no->nom);
            
                courant=tmp->no;
                if(!s+subslash(s)+1) return courant;
                printf("return pas\n");
                return cd(s+subslash(s)+1,courant);
            }else{
                printf("%s n'existe pas \n",s);
                return courant;
            }
        }else{
            printf("le dossier est vide");
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
void touch(char* s,noeud* courant){

    if(!courant->est_dossier){
        printf("pas un dossier\n");
        return ;
    }
    noeud* a;
    liste_noeud *d;
    liste_noeud *c;

    noeud* tmp=courant;
    if (in_str(s, '/'))
        tmp = cd(slash(s,true),tmp);
    a = new_node(tmp->racine);
    strcpy(a->nom,slash(s, false));
    a->pere=tmp;
    a->racine=tmp->racine; // noeud globale
    a->fils=NULL;
    if(tmp->fils!=NULL){
        d=tmp->fils;
        while(d->succ!=NULL){
            d=d->succ;
        }
        c = malloc(sizeof(liste_noeud));
        c->no = a;
        c->succ = NULL;
        d->succ = c;
    }else{
        d = malloc(sizeof(liste_noeud));
        d->no = a;
        d->succ = NULL;
        tmp->fils = d;
    }
}
void mkdir(char* s,noeud* courant){
    if(!courant->est_dossier){
        printf("pas un dossier\n");
        return ;
    }
    noeud* a;
    liste_noeud *d;
    liste_noeud *c;

    noeud* tmp=courant;
    if (in_str(s, '/'))
        tmp = cd(slash(s,true),tmp);
    a = new_node(tmp->racine);
    strcpy(a->nom,slash(s, false));
    a->est_dossier = true;
    a->pere=tmp;
    a->racine=tmp->racine; // noeud globale
    a->fils=NULL;
    if(tmp->fils!=NULL){
        d=tmp->fils;
        while(d->succ!=NULL){
            d=d->succ;
        }
        c = malloc(sizeof(liste_noeud));
        c->no = a;
        c->succ = NULL;
        d->succ = c;
    }else{
        d = malloc(sizeof(liste_noeud));
        d->no = a;
        d->succ = NULL;
        tmp->fils = d;
    }
}

void ls(noeud* courant){
    if(courant!=NULL){
        if(courant->fils!=NULL){
             int a=5;
            liste_noeud* b=courant->fils;
            while(b!=NULL){
                
                printf("   %s",b->no->nom);
                if(a){
                     a--;
                }else{
                    a=5;
                }
               b=b->succ;

            }
            printf("\n");
        }  
    }
}

noeud *rm(noeud *courant,char* s){
    noeud* tmp1=courant;
    if (in_str(s, '/'))
        tmp1 = cd(slash(s,true),tmp1);
    liste_noeud* tmp=tmp1->fils;
    liste_noeud* tmp2= NULL;
    while(tmp && strcmp(slash(s,false),tmp->no->nom)){
        tmp2 = tmp;
        tmp = tmp->succ;
    }
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
    
    if (tmp->no->est_dossier)
    {
        liste_noeud *fils = tmp->no->fils;
        liste_noeud *suc;
        while (fils)
        {
            suc = fils->succ;
            rm_free(fils);
            fils = suc;
        }
    }
    free(tmp->no);
    free(tmp);
}