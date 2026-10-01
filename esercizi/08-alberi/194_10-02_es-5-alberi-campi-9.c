//
//  main.c
//  es 5 alberi campi -9
//
//  Created by Francesco Roscio Ricon on 10/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURA (come da testo, con refuso corretto)
   ========================= */
typedef struct EL {
    int dato;                 /* sempre positivo */
    struct EL *left, *right;  /* due rami */
} node;

typedef node * tree;

/* =========================
   PROTOTIPI FUNZIONI RICHIESTE
   ========================= */
/* punteggio massimo su un cammino radice->foglia */
int maxPunti(tree t);

/* dice se esiste un cammino radice->foglia che somma esattamente k */
int esisteCammino(tree t, int k);

/* =========================
   SUPPORTO PER TEST (costruzione albero)
   ========================= */
static tree nuovoNodo(int v) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

int f2(int K, tree albero, int somma);
int esisteCammino(tree t, int k) {
    return f2(k, t, 0);
}

/* =========================
   MAIN
   ========================= */
void f1(tree t, int *max, int somma, int *flag);
int main() {
    tree T;
    int max, k, ok;

    /* Costruisco un albero di esempio (valori positivi):
             5
            / \
           3   8
          / \   \
         2   4   10
    */
    T = nuovoNodo(5);
    T->left = nuovoNodo(3);
    T->right = nuovoNodo(8);
    T->left->left = nuovoNodo(2);
    T->left->right = nuovoNodo(4);
    T->right->right = nuovoNodo(10);

    /* Test maxPunti */
    max = maxPunti(T);
    printf("Punteggio massimo radice->foglia: %d\n", max);

    /* Test esisteCammino */
    k = 5 + 8 + 10; /* esempio di k (puoi cambiarlo) */
    ok = esisteCammino(T, k);

    if (ok)
        printf("Esiste un cammino radice->foglia con somma ESATTA = %d\n", k);
    else
        printf("NON esiste un cammino radice->foglia con somma ESATTA = %d\n", k);

    return 0;
}
int maxPunti(tree t)
    {
    int max=0;
    int flag=0;
    f1(t, &max, 0, &flag);
    return max;
    }

void f1(tree t, int *max, int somma, int *flag)
    {
        if(t==NULL)
            return;
        somma=somma+t->dato;
    if(t->left==NULL && t->right==NULL)
    {
        if(*flag==0)
        {
            *flag=1;
            *max=somma;
        }
        if(*flag==1)
        {
            if(somma>*max)
            {
                *max=somma;
                return;
            }
        }
    }
    f1(t->left, max, somma, flag);
    f1(t->right, max, somma, flag);
    }
int f2(int K, tree albero, int somma)
    {
        if(albero==NULL)
            return 0;
        somma=somma+albero->dato;
    if (albero->left==NULL && albero->right==NULL) {
        if(K==somma)
            return 1;
        return 0;
    }
    return f2(K, albero->left, somma)|| f2(K, albero->right, somma);
    }
