//  Created by Francesco Roscio Ricon on 22/01/26.

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

void wrapper(Albero tree, int livello, int*sommapari, int*sommadispari);
int check_tree(Albero tree1);


int main() {

    Albero t1 = costruisci1();
    Albero t2 = costruisci2();
    Albero t3 = costruisci3();

    int ris1=check_tree(t1);
    printf("%d\n", ris1);
    int ris2=check_tree(t2);
    printf("%d\n", ris2);
    int ris3=check_tree(t3);
    printf("%d\n", ris3);
    
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

int check_tree(Albero tree1)
    {
    int sommapari=0;
    int sommadispari=0;
    wrapper(tree1, 0, &sommapari, &sommadispari);
    if(sommapari==sommadispari)
        return 1;
    return 0;
    }

void wrapper(Albero tree, int livello, int*sommapari, int*sommadispari)
    {
        if(tree==NULL)
            return;
        if(livello%2==0)
            *sommapari=*sommapari+tree->val;
        if(livello%2==1)
            *sommadispari=*sommadispari+tree->val;
    wrapper(tree->left, livello+1, sommapari, sommadispari);
    wrapper(tree->right, livello+1, sommapari, sommadispari);
    }
