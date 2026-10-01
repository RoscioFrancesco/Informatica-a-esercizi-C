//
//  main.c
//  altro tde alberi
//
//  Created by Francesco Roscio Ricon on 26/01/26.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct N {
    int valore;
    struct N * left;
    struct N * right;
} Nodo;
typedef Nodo * Albero;
Albero nuovoNodo(int valore);
void stampaAlbero(Albero t);
void print(Albero t);
int contafoglie(Albero T);
void f(Albero T, int somma, int *segna, int v[]);
void sommaPercorsi(Albero T);
int main() {
    Albero radice = nuovoNodo(3);
    radice->left = nuovoNodo(4);
    radice->right = nuovoNodo(9);
    radice->left->left = nuovoNodo(2);
    radice->left->right = nuovoNodo(7);
    radice->right->left = nuovoNodo(8);
    radice->left->left->left = nuovoNodo(1);
    radice->left->left->right = nuovoNodo(3);
    printf("Stampa dell'albero in ordine antecedente (radice, left, right):\n");
    stampaAlbero(radice);
    sommaPercorsi(radice);
}


// Funzione per creare un nuovo nodo
Albero nuovoNodo(int valore) {
    Albero nodo = (Albero) malloc(sizeof(Nodo));
    nodo->valore = valore;
    nodo->left = NULL;
    nodo->right = NULL;
    return nodo;
}


// Funzione per stampare l'albero
void stampaAlbero(Albero t) { print(t); printf("\n");}
void print(Albero t) {
    if (t == NULL)return;
    else {
        printf(" (");
        print(t->left);
        printf(" %d ", t->valore);
        print(t->right);
        printf(") ");
    }
}
int contafoglie(Albero T)
    {
        if(T==NULL)
            return 0;
        if(T->left==NULL && T->right==NULL)
            return 1;
    return contafoglie(T->left)+contafoglie(T->right);
    }
void sommaPercorsi(Albero T)
    {
    int num=contafoglie(T);
    int *v=malloc(sizeof(int)*num);
    int segna=0;
    f(T, 0, &segna, v);
    for(int i=0; i<num; i++)
        {
            printf("%d  ", v[i]);
        }
    free(v);
    return;
    }
void f(Albero T, int somma, int *segna, int v[])
    {
        if(T== NULL)
            return;
    somma=somma+T->valore;
        if(T->left==NULL && T->right==NULL)
        {
            v[*segna]=somma;
            (*segna)++;
            return;
        }
    f(T->left, somma, segna, v);
    f(T->right, somma, segna, v);
    }

