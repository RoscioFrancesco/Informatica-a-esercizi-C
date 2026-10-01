//
//  main.c
//  ESAME ES 2
//
//  Created by Francesco Roscio Ricon on 19/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct E {
    char c;
    struct E *left,*right;
} Nodo;
typedef Nodo* Tree;
Tree crea();
Tree nn(char c,Tree left,Tree right);
int esisteLivelloConParola(Tree t,const char *parola);
int contanodi(Tree t);
int depth(Tree t);
void riempilivello(Tree t, int l_target, int liv, char parola[], int *segna);
int f(Tree t, const char parola[]);
int main(void) {
    Tree t=crea();
    int i;
    const char *tests[]={"A","BC","DEF","G","DG","EF","XYZ"};
    for (i=0; i<7; i++)
        printf("Parola %s: %d\n",tests[i],esisteLivelloConParola(t,tests[i]));
}
int esisteLivelloConParola(Tree t,const char *parola) {
    return f(t, parola);
}
void riempilivello(Tree t, int l_target, int liv, char parola[], int *segna) // liv tiene traccia del livello a cui mi trovo, quando combacia con il target allora inserisco la lettera, *segna indica dove inserire il carattere e tiene il numero di caratteri nella stringa, parola è la stringa che sto riempiendo
    {
        if(t==NULL)
            return;
        if(l_target==liv)
            {
                parola[*segna]=t->c;
                (*segna)++;
            }
    riempilivello(t->left, l_target, liv+1, parola, segna); // chiamando prima la funzione su t->left e poi su t->right mantengo l'ordine di scrittura della lettere nella stringa dinamica da sinistra a destra
    riempilivello(t->right, l_target, liv+1, parola, segna);
    }
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int depth(Tree t) // trova la profondità massima dell'albero cosi per ogni livello cerco la parola
    {
        if(t==NULL)
            return 0;
    int sx=depth(t->left);
    int dx=depth(t->right);
    return 1+max(sx, dx);
    }
int contanodi(Tree t)
    {
        if(t==NULL)
            return 0;
    return 1+contanodi(t->left)+contanodi(t->right);
    }
int f(Tree t, const char parola[]) // metto constant per fare sparire il warning quando chiamo f dentro esisteLivelloConParola
    {
    if(t==NULL)
        return 0;
    int prof=depth(t);
    Tree root=t;
    int num=contanodi(t);
    for(int i=0; i<prof; i++) // considero la radice a profondità 0 e verifico ogni livello
        {
            int len=0;
            char *p=malloc(sizeof(char)*(num+1)); // faccio una stringa dinamica con tanti caratteri quanti i nodi dell'albero +1(per il tarminatore di stringa, anche se è impossibile avere un albero di tot nodi tutti allo stesso livello)(sono sicuro di starci dentro, tengo traccia della lunghezzza della parola ed inserisco il terminatore di stringa per confrontarla con la parola di partenza)
            riempilivello(root, i, 0, p, &len); // ogni volta parto dalla radice e per ogni livello formo la parola formata dalla lettura da sinistra a destra
            p[len]='\0';
//            printf("parola del livello %d %s con lunghezza: %d\n",i, p, len);
            if(strcmp(p, parola)==0) // le 2 parole combaciano (trovata)
                {
                    free(p); //faccio la free della parola
                    return 1;
                }
            free(p); //faccio la free della parola e tento il prossimo livello
        }
    return 0; // nessun livello compatibile
    }
Tree nn(char c,Tree left,Tree right){Tree n=(Tree)malloc(sizeof(Nodo));n->c=c;n->left=left;n->right=right;return n;}
Tree crea(){Tree t=nn('A',nn('B',nn('D',NULL,NULL),nn('E',nn('G',NULL,NULL),NULL)),nn('C',NULL,nn('F',NULL,NULL)));return t;}
