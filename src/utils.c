#include "../include/commande.h"

int subslash(char* s){//fonction qui compte le nombre de charactere entre deux / ou 1 slash et la fin
    int a=0;
    while(s[a] && s[a]!='/'){
        a++;
    }
    return a;
}

char* slash(char* s,bool a){// si a=true il renvoie la partie gauche et si a=false il renvoie la partie droite
    int i=strlen(s)-1;
    char* t;
    while(s[i]!='/' && i){
        i--;
    }
    if(s[i] != '/'){
        return strdup(s);
    }
    t=malloc(a ? i + 1 : strlen(s) - i);
    if(a){
         memmove(t,s,i);
         t[i] = '\0';
    }else{
        memmove(t,s + i + 1,strlen(s) - i);
    }
   
    return t;
}

bool in_str(char *s, char c)
{
    while (*s)
    {
        if (*s == c)
            return true;
        s++;
    }
    return false;
}

int nbr_fils(noeud* a){
    liste_noeud* c=a->fils;
    if(c==NULL) return 0;
    int b=1;
    while(c->succ){
        c=c->succ;
        b++;
    }
    return b;
}

int argument(char *s)
{
    int i = 0;
    char *arg;
    while (s[i] && s[i] != ' '){
        i++;
    }
    return i;
}

bool in_path(noeud *courant, char *s)
{
    if (courant == courant->racine)
        return false;
    if (!strcmp(courant->nom, s))
        return true;
    return in_path(courant->pere, s);
    
}