//  Created by Francesco Roscio Ricon on 20/01/26.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definizione della struttura Nodo
typedef struct N {
    int valore;
    struct N * left,* right;
} Nodo;
typedef Nodo * Albero;


Albero nuovoNodo(int valore);
void stampaAlbero(Albero t);
void print(Albero t);
Albero costruisci1();
Albero costruisci2();
void funzione(Albero tree, int *var_max, int min_prec, int max_prec);
int f(Albero t);
int main() {
    // Creazione dell'albero
    Albero alb1 = costruisci1();
    Albero alb2 = costruisci2();


    // Stampa dell'albero
    printf("Stampa dell'albero in ordine (left, radice, right):\n");
    stampaAlbero(alb1);
    stampaAlbero(alb2);
    
    printf("Albero 1: %d\n",f(alb1));
    printf("Albero 2: %d\n",f(alb2));


    return 0;
}



// Funzione per creare un nuovo nodo
Albero nN(int valore) {
    Albero nodo = (Albero) malloc(sizeof(Nodo));
    nodo->valore = valore;
    nodo->left = NULL;
    nodo->right = NULL;
    return nodo;
}


// Funzione per stampare l'albero
void stampaAlbero(Albero t){print(t);printf("\n");}
void print(Albero t){
    if(t==NULL)return;
    else{printf(" (");print(t->left);printf(" %d ", t->valore);print(t->right);printf(") ");}
}
Albero costruisci1(){
    Albero radice=nN(3);radice->left=nN(4);radice->right=nN(9);radice->left->left=nN(2);radice->left->right=nN(6);radice->right->left=nN(8);radice->left->left->left=nN(1);radice->left->left->right=nN(3);
    return radice;
}
Albero costruisci2(){
    Albero radice=nN(3);radice->left=nN(4);radice->right=nN(9);radice->left->left=nN(2);radice->left->right=nN(6);radice->right->left=nN(8);radice->right->right=nN(5);
    return radice;
}

void funzione(Albero tree, int *var_max, int min_prec, int max_prec)
{
    if (tree == NULL) return;

    if (tree->valore < min_prec) min_prec = tree->valore;
    if (tree->valore > max_prec) max_prec = tree->valore;

    if (tree->left == NULL && tree->right == NULL) {
        int var = max_prec - min_prec;
        if (var > *var_max) *var_max = var;
        return;
    }

    funzione(tree->left, var_max, min_prec, max_prec);
    funzione(tree->right, var_max, min_prec, max_prec);
}

int f(Albero t)
{
    if (t == NULL) return 0;
    int var_max = 0;
    funzione(t, &var_max, t->valore, t->valore);
    return var_max;
}
