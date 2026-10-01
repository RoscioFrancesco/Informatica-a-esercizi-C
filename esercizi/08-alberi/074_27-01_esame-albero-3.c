//
//  main.c
//  ESAME albero 3
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
int controlla(Tree albero, char parola[]);


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

int f(Tree albero, char parola[], int*segna, int len, int s, int prec) // s tiene traccia della direzione da cui si arriva arrivo da sinistra=1, arrivo da destra=0, se è il primo nodo sx=-1 e nel momento in cui trova il primo valore uguale a quello della stringa inizializzo prec;
    {
        if(albero==NULL)
            return 0;
        if((*segna)+1==len)
            return 1;
        if(albero->left==NULL && albero->right==NULL)
            {
                if(parola[(*segna)+1]=='\0')
                    return 1;
                return 0;
            }
        if(s==-1)
            {
                return f(albero->right, parola, segna, len, 2, 1) ||  f(albero->left, parola, segna, len, 2, 0);
            }
        if(albero->c==parola[*segna])
            {
                (*segna)++;
                if(s==2)
                    s=prec;
                if(s==0)
                {
                    return f(albero->right, parola, segna, len, 1, 1);
                }
                if(s==1)
                {
                    return f(albero->left, parola, segna, len, 0, 0);
                }

            }
        return 0;
    }
int controlla(Tree albero, char parola[])
    {
    int len=strlen(parola);
    int segna=0;
    if( f(albero, parola, &segna, len, -1, 2)!=0)
        return 1;
    return 0;
    }
