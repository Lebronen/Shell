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
    char *tmp_slash_1;
    char *tmp_slash_2;

    noeud* tmp=courant;
    if (in_str(s, '/'))
    {
        tmp_slash_1 = slash(s, true);
        tmp = cd(tmp_slash_1,tmp);
    }
    a = new_node(tmp->racine);
    tmp_slash_2 = slash(s, false);
    strcpy(a->nom,tmp_slash_2);
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
    if (in_str(s, '/'))
    {
        free(tmp_slash_1);
        free(tmp_slash_2);
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
    char *tmp_slash;
    char *tmp_slash_2;

    noeud* tmp=courant;
    if (in_str(s, '/'))
    {
        tmp_slash = slash(s, true);
        tmp = cd(tmp_slash,tmp);
    }
    a = new_node(tmp->racine);
    tmp_slash_2 = slash(s, false);
    strcpy(a->nom,tmp_slash_2);
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
    if (in_str(s, '/'))
    {
        free(tmp_slash);
    }
    if (strcmp(s, tmp_slash_2))
        free(tmp_slash_2);
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
    char *tmp_slash;
    char *tmp_slash_2;
    noeud* tmp1=courant;
    if (in_str(s, '/'))
    {
        tmp_slash = slash(s, true);
        tmp1 = cd(tmp_slash,tmp1);
        free(tmp_slash);
    }
    liste_noeud* tmp=tmp1->fils;
    liste_noeud* tmp2= NULL;
    tmp_slash_2 = slash(s, false);
    while(tmp && strcmp(tmp_slash_2,tmp->no->nom)){
        tmp2 = tmp;
        tmp = tmp->succ;
    }
    if (strcmp(tmp_slash_2, s))
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

void print(noeud* courant){
    print_suite(courant->racine);
}
void print_suite(noeud* a){
    if(a==a->racine){
            printf("%s",a->nom);
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
            printf(" (d),pére: %s, %d fils:",a->pere->nom,nbr_fils(a));
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
            
            printf(" (f),pére: %s, 0 fils \n",a->pere->nom); 
        }
    }
    
    
    
}