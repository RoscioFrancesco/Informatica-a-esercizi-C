//  Created by Francesco Roscio Ricon on 16/01/26.

#include <stdio.h>
#include <stdlib.h>

typedef struct El {
    int val;
    struct El *left,*right;
} Nodo;

typedef Nodo *Albero;

Albero nN(int valore);
Albero costruisci1();
Albero costruisci2();
Albero costruisci3();
int wrapper(Albero t);
void check_tree(Albero t, int livello, int *sommapari, int *sommadispari);
// TODO prototipi

int main() {
    Albero t1 = costruisci1();
    Albero t2 = costruisci2();
    Albero t3 = costruisci3();
    int ris=wrapper(t3);
    printf("%d", ris);

}

// Funzione per creare un nuovo nodo
Albero nN(int valore) {
    Albero nodo = (Albero) malloc(sizeof(Nodo));
    nodo->val = valore;
    nodo->left = NULL;
    nodo->right = NULL;
    return nodo;
}

Albero costruisci1() {
    Albero radice = nN(2);
    radice->left = nN(1);
    radice->right = nN(5);
    radice->left->left = nN(0);
    radice->left->right = nN(2);
    radice->right->right = nN(2);
    return radice;
}

Albero costruisci2() {
    Albero radice = nN(5);
    radice->left = nN(1);
    radice->right = nN(5);
    radice->left->left = nN(0);
    radice->left->right = nN(2);
    radice->right->right = nN(2);
    return radice;
}

Albero costruisci3() {
    Albero radice = nN(2);
    radice->left = nN(5);
    radice->left->left = nN(1);
    radice->left->right = nN(2);
    return radice;
}

void check_tree(Albero t, int livello, int *sommapari, int *sommadispari)
    {
        if(t==NULL)
            return;
        if(livello%2==0)
            {
                *sommapari=*sommapari+t->val;
            }
        if(livello%2==1)
            {
                *sommadispari=*sommadispari+t->val;
            }
    check_tree(t->left, livello+1, sommapari, sommadispari);
    check_tree(t->right, livello+1, sommapari, sommadispari);
    }

int wrapper(Albero t)
    {
    int somma_pari=0;
    int somma_dispari=0;
    int livello=1;
    check_tree(t, livello, &somma_pari, &somma_dispari);
    if(somma_pari==somma_dispari)
        return 1;
    return 0;
    }
