//
//  main.c
//  es albero  -7
//
//  Created by Francesco Roscio Ricon on 12/02/26.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *left, *right;
} Node;

typedef Node* Tree;

/* Risultato “complesso” da confrontare */
typedef struct {
    int len;        // lunghezza cammino (nodi)
    int sum;        // somma valori
    int valid;      // 1 se esiste un cammino (foglia raggiunta)
    Tree next;      // prossimo nodo nel cammino migliore (per ricostruire/stampare)
} Res;

/* --- Utility --- */
static Tree newNode(int v, Tree l, Tree r) {
    Tree n = (Tree)malloc(sizeof(Node));
    n->val = v; n->left = l; n->right = r;
    return n;
}
void stampa(char parola[], Tree t, int livello);
/*
Confronto tra due risultati (A vs B) secondo:
1) len maggiore
2) sum maggiore
3) a parità totale, vince il SINISTRO
   => nel chiamante: se A viene dal sinistro, basta fare "A >= B" e in parità torna A.
*/
char *f2(Tree albero, int *livello, int *somma);
void stampa(char parola[], Tree t, int livello);
void bestPathFrom(Tree t);
int main(void) {
    /*
        Esempio albero:
                 5
               /   \
              3     3
             / \     \
            2   2     2
           /           \
          9             9

        Ci sono due cammini di stessa lunghezza e stessa somma:
        5-3-2-9 (sinistra) e 5-3-2-9 (destra) => deve vincere il sinistro.
    */

    Tree T =
        newNode(5,
            newNode(3,
                newNode(2,
                    newNode(9, NULL, NULL),
                    NULL
                ),
                newNode(2, NULL, NULL)
            ),
            newNode(3,
                NULL,
                newNode(2,
                    NULL,
                    newNode(9, NULL, NULL)
                )
            )
        );
    bestPathFrom(T);
    

    return 0;
}
int max(int a, int b)
    {
    if (a>b) return a;
    return b;
    }
int depth(Tree albero)
    {
        if(albero==NULL)
            return 0;
    int sx=depth(albero->left);
    int dx=depth(albero->right);
    return 1+max(sx, dx);
    }

void bestPathFrom(Tree t)
    {
    int somma=0;
    int livello=0;
    char* parola=f2(t, &livello, &somma);
    stampa(parola, t, 0);
    free(parola);
    return;
    }
char *f2(Tree albero, int *livello, int *somma)
{
    if(albero==NULL)
        {
            char *lettera=malloc(sizeof(char));
            *lettera='\0';
            return lettera;
        }
    (*livello)++;
    (*somma)=(*somma)+albero->val;
    if(albero->left==NULL && albero->right==NULL)
        {
            char *new=malloc(sizeof(char)*(*livello));
            new[(*livello)-1]='\0';
            return new;
        }
    int livdx=*livello;
    int livsx=*livello;
    int sommasx=*somma;
    int sommadx=*somma;
    char *pdx=f2(albero->right, &livdx, &sommadx);
    char *psx=f2(albero->left, &livsx, &sommasx);
    if(livsx>livdx)
    {
        free(pdx);
        psx[(*livello)-1]='s';
        *livello=livsx;
        *somma=sommasx;
        return psx;
    }
    else if (livdx>livsx)
    {
        free(psx);
        pdx[(*livello)-1]='d';
        *livello=livdx;
        *somma=sommadx;
        return pdx;
    }
    else
    {
        if(sommasx>=sommadx)
            {
                free(pdx);
                psx[(*livello)-1]='s';
                *livello=livsx;
                *somma=sommasx;
                return psx;
            }
        else
            {
                free(psx);
                pdx[(*livello)-1]='d';
                *livello=livdx;
                *somma=sommadx;
                return pdx;
            }
    }
//    return psx;
}

void stampa(char parola[], Tree t, int livello)
    {
        if(t==NULL)
        {
            if(parola[livello]=='\0')
                return;
            else
            {
                printf("errore coglione");
                return;
            }
                
        }
    printf("%d-->", t->val);
    if(parola[livello]=='s')
        stampa(parola, t->left, livello+1);
    else if (parola[livello]=='d')
        stampa(parola, t->right, livello+1);
    if(parola[livello]!='s' && parola[livello]!='d')
        {
            printf("finito");
        }
     
    return;
    }
