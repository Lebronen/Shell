#include "../include/commande.h"

void cd(char* s,noeud* courant){
    if(s==".."){
        if(courant==courant->racine) return;
        else{
            courant=courant->pere;
        }
    }else{
        if(courant->fils->no!=NULL){
            noeud* tmp=courant->fils->no;
            while(tmp!=NULL || !strcmp(tmp->nom,s)){
                tmp->fils->no=tmp->fils->succ->no;
            }
            if(strcmp(tmp->nom,s)){
                courant=tmp;
            }else{
                printf("%s n'existe pas \n",s);
            }
        }else{
            printf("le dossier est vide");
        }
    }

}
void cd(noeud* courant){
    courant=courant->racine;
}
void pwd(noeud* courant){//a finir!
    assert(courant!=NULL);
    if(courant!=courant->racine){
        pwd(courant->pere);
        printf("%s/",courant->nom);
    }else{
        printf("%s/",courant->nom);
    }
}
void touch(char* s,noeud* courant){
    noeud* a;
    a->est_dossier=false;
    strcpy(a->nom,s);
    a->pere=courant;
    a->racine=courant->racine; // noeud globale
    a->fils=NULL;
    if(courant->est_dossier==true){
        if(courant->fils->no!=NULL){
                noeud* d=courant->fils->no;
            while(d->fils->succ->no!=NULL){
                d=d->fils->succ->no;
            }
            d->fils->succ=a;
        }else{
            courant->fils->no=a;
        }
    }
}
void mkdir(char* s,noeud* courant){
    noeud* a;
    a->est_dossier=true;
    strcpy(a->nom,s);
    a->pere=courant;
    a->racine=courant->racine; // noeud globale
    a->fils=NULL;
    if(courant->est_dossier==true){
        if(courant->fils->no!=NULL){
                noeud* d=courant->fils->no;
            while(d->fils->succ->no!=NULL){
                d=d->fils->succ->no;
            }
            d->fils->succ=a;
        }else{
            courant->fils->no=a;
        }
    }
}

void ls(noeud* courant){
    if(courant!=NULL){
        if(courant->fils->no!=NULL){
             int a=5;
            liste_noeud* b=courant->fils;
            while(b->succ!=NULL){
                if(a!=0){
                     printf("   %s",b->no->nom);
                     a--;
                }else{
                    printf("   %s\n",b->no->nom);
                    a=5;
                }
               b=b->succ;

            } 
        } 
           
    }
}
