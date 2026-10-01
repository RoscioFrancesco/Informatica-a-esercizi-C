//
//  main.c
//  ancora alberi
//
//  Created by Francesco Roscio Ricon on 25/01/26.
//

#include <stdio.h>
#include <stdlib.h>
typedef struct t {
    char c;
    struct t *left, *right;
} Nodo;

typedef Nodo* Tree;

/*** PROTOTIPI ***/
Tree newNode(char c);
void freeTree(Tree t);
void stampaPreordine(Tree t);

/*** SUPPORTO ***/
Tree newNode(char c) {
    Tree n = (Tree)malloc(sizeof(Nodo));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->c = c;
    n->left = n->right = NULL;
    return n;
}

void freeTree(Tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

void stampaPreordine(Tree t) {
    if (t == NULL) {
        printf(". ");
        return;
    }
    printf("%c ", t->c);
    stampaPreordine(t->left);
    stampaPreordine(t->right);
}
int profonditaMassimaRipetizione(Tree albero);
void funzione(Tree albero, char root, int *max, int livello);

int main() {
    /*
        Costruiamo un albero di esempio:

                 A
               /   \
              B     A
             / \     \
            A   D     E
               /
              A

        Valore radice = 'A'
        Profondità (radice=0):
        - A (radice) -> depth 0
        - A (a destra della radice) -> depth 1
        - A (figlio sinistro di B) -> depth 2
        - A (figlio sinistro di D) -> depth 3   <-- massimo
    */

    Tree t = newNode('A');
    t->left = newNode('B');
    t->right = newNode('A');

    t->left->left = newNode('A');
    t->left->right = newNode('D');

    t->left->right->left = newNode('A');

    t->right->right = newNode('E');

    printf("Albero in preordine ('.' = NULL):\n");
    stampaPreordine(t);
    printf("\n\n");

    int maxProf = profonditaMassimaRipetizione(t);
    printf("Profondita massima di un nodo con valore uguale alla radice ('%c'): %d\n",
           t->c, maxProf);

    freeTree(t);
    return 0;
}

void funzione(Tree albero, char root, int *max, int livello)
    {
        if(albero==NULL)
            return;
        if(root==albero->c)
            {
                if(*max<livello)
                    *max=livello;
            }
    funzione(albero->left, root, max, livello+1);
    funzione(albero->right, root, max, livello+1);
    }
int profonditaMassimaRipetizione(Tree albero)
    {
    char root=albero->c;
    int max=0;
    funzione(albero, root, &max, 1);
    return max;
    }

