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

void cd(char* s,noeud courant){
    if(s==".."){
        if(courant==courant->racine) return;
        else{
            courant=courant->pere;
        }
    }else{
        if(courant->fils->no!=NULL){
            noeud tmp=courant->fils->no;
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
void cd(noeud courant){
    courant=courant->racine;
}
void pwd(noeud courant){//a finir!
    noeud tmp=courant;
    char* s;
    while(tmp!=racine){
        str;
    }
}
void touch(char* s,noeud courant){
    noeud a;
    a->est_dossier=false;
    strcpy(a->nom,s);
    a->pere=courant;
    a->racine=courant->racine; // noeud globale
    a->fils=NULL;
    if(courant->est_dossier==true){
        if(courant->fils->no!=NULL){
                noeud d=courant->fils->no;
            while(d->succ->no!=NULL){
                d=d->succ->no;
            }
            d->succ=a;
        }else{
            courant->fils->no=a
        }
    }
}
void mkdir(char* s,noeud courant){
    noeud a;
    a->est_dossier=true;
    strcpy(a->nom,s);
    a->pere=courant;
    a->racine=courant->racine; // noeud globale
    a->fils=NULL;
    if(courant->est_dossier==true){
        if(courant->fils->no!=NULL){
                noeud d=courant->fils->no;
            while(d->succ->no!=NULL){
                d=d->succ->no;
            }
            d->succ=a;
        }else{
            courant->fils->no=a
        }
    }
}

void ls(noeud courant){
    if(courant!=NULL){
        if(courant->fils[0]!=NULL){
             int a=5;
            noeud b=courant->fils[0];
            while(b->succ!=null){
                if(a!=0){
                     printf("   %s",b->no->nom);
                     a--;
                }else{
                    printf("   %s\n",b->no->nom);
                    a=5;
                }
               b=b.succ;

            } 
        } 
           
    }
}
int main(){
    touch("test");
}