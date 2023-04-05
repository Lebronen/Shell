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


void touch(char* s,noeuds courant,noeuds racine){
    noeuds a;
    a.est_dossier=false;
    a.nom=s;
    a.pere=courant;
    a.racine=racine; // noeud globale
    a.fils=NULL;
    if(courant.est_dossier==true){
        if(courant.fils[0]!=NULL){
                noeud d=courant.fils[0];
            while(d.succ!=NULL){
                d=d.succ;
            }
            d.succ=a;
        }else{
            courant.fils[0]=a
        }
    }
}
void mkdir(char* s,noeuds courant,noeuds racine){
     noeuds a;
    a.est_dossier=true;
    a.nom=s;
    a.pere=courant;
    a.racine=racine; // noeud globale
    a.fils=NULL;
    if(courant.est_dossier==true){
        if(courant.fils[0]!=NULL){
                noeud d=courant.fils[0];
            while(d.succ!=NULL){
                d=d.succ;
            }
            d.succ=a;
        }else{
            courant.fils[0]=a
        }
    }
}
void ls(){
    if(courant!=NULL){
        if(courant.fils[0]!=NULL){
             int a=5;
            noeud b=courant.fils[0];
            while(b.succ!=null){
                if(a!=0){
                     printf("   %s",b.no.nom);
                     a--;
                }else{
                    printf("   %s\n",b.no.nom);
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