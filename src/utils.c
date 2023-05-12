#include "../include/commande.h"

int subslash(char* s){//fonction qui compte le nombre de charactere entre deux / ou 1 slash et la fin
    int a=0;
    while(*s++ && *s!='/'){
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
    if(!i){
        return s;
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
    while (*s++)
    {
        if (*s == c)
            return true;
    }
    return false;
}