//
//  main.c
//  giorno -9 tde4 alberi 
//
//  Created by Francesco Roscio Ricon on 18/01/26.
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
void funzione(int v[], Albero t, int somma, int *indice);
void wrapper(int v[], Albero t);
 
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

    int v[4];
    // Stampa dell'albero
    printf("Stampa dell'albero in ordine antecedente (radice, left, right):\n");
    stampaAlbero(radice);
    wrapper(&v[0], radice);
    int i=0;
    for(i=0; i<4; i++)
        {
            printf("%d", v[i]);
        }
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

void wrapper(int v[], Albero t)
    {
        if(t==NULL)
            return;
    int indice=0;
    funzione(v, t, 0, &indice);
        
    }
void funzione(int v[], Albero t, int somma, int *indice)
    {
        if(t==NULL)
            return;
        if(t->left==NULL && t->right==NULL)
            {
                somma=somma+t->valore;
                v[*indice]=somma;
                (*indice)++;
                return;
            }
        somma=somma+t->valore;
    funzione(v, t->left, somma, indice);
    funzione(v, t->right, somma, indice);
    }


