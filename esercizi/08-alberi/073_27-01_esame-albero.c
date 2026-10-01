//
//  main.c
//  ESAME albero
//
//  Created by Francesco Roscio Ricon on 27/01/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define n NULL

typedef struct El {
    char c;
    struct El *left, *right;
} Nodo;


typedef Nodo *Tree;


Tree nn(char c,Tree l,Tree r){Tree t=(Tree)malloc(sizeof(Nodo));t->c=c;t->left=l;t->right=r;return t;}
Tree crea(){return nn('c',nn('i',nn('a',n,nn('o',n,n)),nn('p',n,n)),nn('s',nn('k',n,n),nn('r',n,nn('w',n,n))));}
void stampa(Tree t){if(!t)return;printf("(");if(t->left)stampa(t->left);printf(" %c ",t->c);if(t->right)stampa(t->right);printf(")");}


//aggiungere qui funzioni ausiliarie



int f(Tree albero, char parola[], int *segna, int s, int len) // arrivo da sinistra=1, arrivo da destra=0, se è il primo nodo sx=-1
    {
        if(albero==NULL)
            return 0;
        if(albero->left==NULL || albero->right==NULL)
            return 0;
        if(*segna==len)
            return 1;
        
        if(*segna<=len && albero->c==parola[(*segna)])
            {
                if(len==1)
                    return 1;
                if(albero->left==NULL && albero->right==NULL)
                    {
                        if(parola[(*segna)+1]=='\0')
                            return 1;
                        return 0;
                    }
                (*segna)++;
                if(len-1==*segna)
                    {
                        return 1;
                    }
                if(s==0)
                {
                    return f(albero->right, parola, segna, 1, len);
                }
                if(s==1)
                {
                    return f(albero->left, parola, segna, 0, len);
                }
                if(s==-1)
                    {
                        return f(albero->right, parola, segna, 1, len) + f(albero->left, parola, segna, 0, len);
                    }
            }
        return 0;
    }
int controlla(Tree albero, char parola[])
    {
    int segna=0;
    int len=strlen(parola);
    int ris=f(albero, parola, &segna, -1, len);
    return ris;
    }


int f(Tree albero, char parola[], int *segna, int s, int len);
int main(void) {
    /*
                 c
               /   \
              i     s
             / \   / \
            a   p k   r
             \         \
              o         w
    */


    Tree t = crea();
    char s[10];
    stampa(t);
    printf("\n");


    strcpy(s,"c");
    printf("%s = %d\n",s, controlla(t,s));
    strcpy(s,"ci");
    printf("%s = %d\n",s, controlla(t,s));
    strcpy(s,"cip");
    printf("%s = %d\n",s, controlla(t,s));
    strcpy(s,"cia");
    printf("%s = %d\n",s, controlla(t,s));
    strcpy(s,"ciao");
    printf("%s = %d\n",s, controlla(t,s));
    strcpy(s,"iao");
    printf("%s = %d\n",s, controlla(t,s));
    strcpy(s,"sr");
    printf("%s = %d\n",s, controlla(t,s));
    strcpy(s,"srw");
    printf("%s = %d\n",s, controlla(t,s));


    return 0;
}


