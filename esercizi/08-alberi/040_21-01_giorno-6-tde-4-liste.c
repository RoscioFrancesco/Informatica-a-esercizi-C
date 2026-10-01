//
//  main.c
//  giorno -6 tde 4 liste
//
//  Created by Francesco Roscio Ricon on 21/01/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct t{
    char c;
    struct t *left, *right;
} Nodo;

typedef Nodo *Tree;

Tree newNode(char c) {
    Tree n = (Tree)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->c = c;
    n->left = n->right = NULL;
    return n;
}

/*
Albero di test (radice = 'a')

Profondità (radice a profondità 0):
                a
              /   \
             b     c
            / \     \
           a   d     a
              /     / \
             e     f   a

Le 'a' compaiono alle profondità: 0, 2, 2, 3
=> profondità massima ripetizione = 3
*/
Tree creaAlberoTest(void) {
    Tree root = newNode('a');

    root->left = newNode('b');
    root->right = newNode('c');

    root->left->left = newNode('a');      // profondità 2
    root->left->right = newNode('d');
    root->left->right->left = newNode('e');

    root->right->right = newNode('a');    // profondità 2
    root->right->right->left = newNode('f');
    root->right->right->right = newNode('a'); // profondità 3 (massima)

    return root;
}

void stampaInOrder(Tree t) {
    if (!t) return;
    stampaInOrder(t->left);
    printf("%c ", t->c);
    stampaInOrder(t->right);
}

void freeTree(Tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

int wrapper(Tree albero);
void funzione(Tree albero, int*max_prof, int livello, char lettera_root);

int main(void) {
    Tree T = creaAlberoTest();

    printf("In-order: ");
    stampaInOrder(T);
    printf("\n");
    
    int p;
    p=wrapper(T);
    printf("Profondita massima di un nodo con valore uguale alla radice: %d\n", p);

    freeTree(T);
    return 0;
}

int wrapper(Tree albero)
    {
    int profondità_max=0;
    char lettera=albero->c;
    funzione(albero, &profondità_max, 0, lettera);
    return profondità_max;
    }

void funzione(Tree albero, int*max_prof, int livello, char lettera_root)
    {
    if(albero==NULL)
        return;
    if(albero->c==lettera_root)
        {
            if(livello>*max_prof)
                {
                    *max_prof=livello;
                }
        }
    funzione(albero->left, max_prof, livello+1, lettera_root);
    funzione(albero->right, max_prof, livello+1, lettera_root);
}
