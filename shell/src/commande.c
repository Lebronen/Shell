#include "../include/commande.h"

void cd(char* s,noeud* courant){
    if(!*s){
        courant=courant->racine;
    }
    if(!strcmp("..",substr(s,0,2))){
        if(courant==courant->racine) return;
        else{
            courant=courant->pere;
            cd(substr(s,3,strlen(s)-1),courant);
        }
        if(*s=='/'){
            courant=courant->racine;
            cd(s+1,courant);
        }
    }else{
        if(courant->fils!=NULL){
            liste_noeud* tmp=courant->fils->succ;
            while(tmp!=NULL && !strcmp(tmp->no->nom,substr(s,0,subslash(s)))){
                tmp=tmp->succ;
            }

            if(strcmp(tmp->no->nom,substr(s,0,subslash(s)))){
                courant=tmp;
                if(!s+subslash(s)+1) return;
                cd(s+subslash(s)+1,courant);
            }else{
                printf("%s n'existe pas \n",s);
            }
        }else{
            printf("le dossier est vide");
        }
    }

}
int subslash(char* s){//fonction qui compte le nombre de charactére entre deux / ou 1 slash et la fin
    int a=0;
    while(*s!=NULL && *s!='/'){
        a++;
    }
    return a;
}
char* substr(const char *src, int m, int n){//renvoie un sous-string de s entre m et n
    // récupère la longueur de la string de destination
    int len = n - m;
 
    // alloue (len + 1) caractères pour la destination (+1 pour un caractère nul supplémentaire)
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
 
    // extrait les caractères entre le m'th et le n'th index de la string source
    // et les copier dans la string de destination
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }
 
    // null-termine la string de destination
    *dest = '\0';
 
    // renvoie la string de destination
    return dest - len;
}
void pwd(noeud* courant){
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
        if(courant->fils!=NULL){
                liste_noeud* d=courant->fils;
            while(d->succ!=NULL){
                d=d->succ;
            }
            liste_noeud* c;
            c->no=a;
            c->succ=NULL;
            d->succ=c;
        }else{
            liste_noeud* d;
            d->no=a;
            d->succ=NULL;
            courant->fils=d;
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
        if(courant->fils!=NULL){
                liste_noeud* d=courant->fils;
            while(d->succ!=NULL){
                d=d->succ;
            }
            liste_noeud* c;
            c->no=a;
            c->succ=NULL;
            d->succ=c;
        }else{
            liste_noeud* d;
            d->no=a;
            d->succ=NULL;
            courant->fils=d;
        }
    }
}
void cp(noeud* courant,char* s,char* a){

}
void rm(noeud* courant,char* s){
    noeud* tmp1=courant; 
    cd(slash(s,true),tmp1);
    liste_noeud* tmp=tmp1->fils;
    liste_noeud* tmp2;
    while(tmp!=NULL && !strcmp(slash(s,false),tmp->no->nom)){
        tmp=tmp->succ;
    }
    if(tmp==NULL){
        return;
    }
    if(!tmp->no->est_dossier){
        tmp->no=NULL;
        free(tmp->no);
    }else{
       tmp2=tmp->no->fils;
       while(tmp2!=NULL){
            rm(tmp,tmp2->no->nom);
            tmp2=tmp2->succ;
       }
       tmp->no=NULL;
       free(tmp->no);
    }
}
char* slash(char* s,bool a){// si a=true il renvoie la partie gauche et si a=false il renvoie la partie droite
    int i=strlen(s)-1;
    char* t;
    while(s[i]!='/' && i){
        i--;
    }
    if(!i){
        return s;
    }
    t=malloc(a ? strlen(s)-i : i + 1);
    if(a){
         memmove(t,s,strlen(s)-i);
    }else{
        memmove(t,s+(strelen(s)-i),i+1);
    }
   
    return t;
}
void print(noeud* a){
    if(a->)
}

int nbr_fils(noeud* a){
    int b=0;
    if(a->fils==NULL) return b;
    liste_noeud* c=a->fils;
    b=1;
    while(c->succ!=NULL){
        c=c->succ;
        b++;
    }
    return b;
}
void ls(noeud* courant){
    if(courant!=NULL){
        if(courant->fils!=NULL){
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
            if(a!=0){
                     printf("   %s",b->no->nom);
                     a--;
                }else{
                    printf("   %s\n",b->no->nom);
                    a=5;
                }
        } 
           
    }
}
