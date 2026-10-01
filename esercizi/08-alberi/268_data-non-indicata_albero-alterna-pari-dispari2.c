#include <stdio.h>
#include <stdlib.h>

typedef struct nodeS {
    int val;
    struct nodeS *left, *right;
} node;

typedef node* tree;

/* Crea un nuovo nodo */
tree newNode(int val) {
    tree n = (tree)malloc(sizeof(node));
    if (n == NULL) {
        printf("Errore allocazione memoria\n");
        exit(1);
    }
    n->val = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/* Libera memoria albero */
void freeTree(tree T) {
    if (T == NULL) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T);
}

/* Funzione di supporto:
   prevParity = 0 se il padre è pari
               1 se il padre è dispari
*/
int checkAlternating(tree T, int prevParity) {
    if (T == NULL) return 0;
    
    int currParity;

    if (T->val % 2 == 0)
        currParity = 0;   // pari
    else
        currParity = 1;   // dispari

    /* deve alternare con il padre */
    if (currParity == prevParity)
        return 0;

    /* se è foglia, percorso valido */
    if (T->left == NULL && T->right == NULL)
        return 1;

    /* basta un ramo valido */
    return checkAlternating(T->left, currParity) ||
           checkAlternating(T->right, currParity);
}

/* Funzione richiesta dall'esercizio */
int esistePercorsoAlternato(tree T) {
    if (T == NULL) return 0;

    /* Se è solo un nodo (radice = foglia), esiste un percorso */
    if (T->left == NULL && T->right == NULL)
        return 1;

    int rootParity;

    if (T->val % 2 == 0)
        rootParity = 0;   // pari
    else
        rootParity = 1;   // dispari

    return checkAlternating(T->left, rootParity) ||
           checkAlternating(T->right, rootParity);
}

int main() {
    /*
        Costruiamo questo albero:

               2
             /   \
            7     4
           / \     \
          6   9     5
         /
        3

      Percorso alternato valido:
      2 (pari) -> 7 (dispari) -> 6 (pari) -> 3 (dispari)
    */

    tree T = newNode(2);
    T->left = newNode(7);
    T->right = newNode(4);

    T->left->left = newNode(6);
    T->left->right = newNode(9);

    T->left->left->left = newNode(3);

    T->right->right = newNode(5);

    if (esistePercorsoAlternato(T))
        printf("Esiste almeno un percorso radice-foglia con alternanza pari/dispari ✅\n");
    else
        printf("NON esiste alcun percorso radice-foglia con alternanza pari/dispari ❌\n");

    freeTree(T);
    return 0;
}
