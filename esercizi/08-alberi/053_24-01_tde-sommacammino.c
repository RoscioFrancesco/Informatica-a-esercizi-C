//
//  main.c
//  tde sommacammino
//
//  Created by Francesco Roscio Ricon on 24/01/26.
//
#include <stdio.h>
#include <stdlib.h>


// Definizione della struttura Nodo
typedef struct N {
    int valore;
    struct N * left;
    struct N * right;
} Nodo;
typedef Nodo * Albero;


Albero nuovoNodo(int valore);
void stampaAlbero(Albero t);
void print(Albero t);
void riempivettore(Albero tree, int *segnaposto, int vett[], int somma);
void sommaPercorsi(Albero tree);
 
int main() {
    // Creazione dell'albero
    Albero radice = nuovoNodo(3);
    radice->left = nuovoNodo(4);
    radice->right = nuovoNodo(9);
    radice->left->left = nuovoNodo(2);
    radice->left->right = nuovoNodo(7);
    radice->right->left = nuovoNodo(8);
    radice->left->left->left = nuovoNodo(1);
    radice->left->left->right = nuovoNodo(3);


    // Stampa dell'albero
    printf("Stampa dell'albero in ordine antecedente (radice, left, right):\n");
    stampaAlbero(radice);
    printf("\n");
    sommaPercorsi(radice);


    return 0;
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


int contafoglie(Albero tree)
    {
        if(tree==NULL)
            return 0;
        if(tree->left==0 && tree->right==0)
            return 1;
    return contafoglie(tree->left)+contafoglie(tree->right);
    }

void sommaPercorsi(Albero tree)
    {
    int numfoglie=contafoglie(tree);
    int segnaposto=0;
    int *vett=malloc(sizeof(int)*numfoglie); // allocazione vettore dinamico
    riempivettore(tree, &segnaposto, vett, 0);
    int i=0;
    for(i=0; i<numfoglie; i++)
        {
            printf("%d-->", vett[i]);
        }
    free(vett);
    }
void riempivettore(Albero tree, int *segnaposto, int vett[], int somma)
    {
        if(tree==NULL)
            return;
    somma=somma+tree->valore;
    if(tree->left==NULL && tree->right==NULL)
        {
            vett[*segnaposto]=somma;
            *segnaposto=*segnaposto+1;
            return;
        }
    riempivettore(tree->left, segnaposto, vett, somma);
    riempivettore(tree->right, segnaposto, vett, somma);
    }
