//
//  main.c
//  tde alberi 1 -14
//
//  Created by Francesco Roscio Ricon on 05/02/26.
//
#include <stdio.h>
#include <stdlib.h>

/* Strutture date dall'esercizio */
typedef struct ET {
    int *dato;
    struct ET *left, *right;
} treeNode;

typedef treeNode *tree;


int alberoConKElementiUguali(tree T, int K);
void trovaelemento(tree albero, int x, int *count);
/* Supporto: crea nodo con valore (alloca anche l'int puntato da dato) */
tree newNode(int value, tree left, tree right) {
    treeNode *n = malloc(sizeof *n);
    if (!n) return NULL;

    n->dato = malloc(sizeof *n->dato);
    if (!n->dato) {
        free(n);
        return NULL;
    }

    *(n->dato) = value;
    n->left = left;
    n->right = right;
    return n;
}

/* Stampa albero: in-order (con parentesi) */
void printTree(tree T) {
    if (T == NULL) {
        printf("NULL");
        return;
    }
    printf("(");
    printTree(T->left);
    printf(" ");
    if (T->dato != NULL) printf("%d", *(T->dato));
    else printf("NULLdato");
    printf(" ");
    printTree(T->right);
    printf(")");
}

/* Deallocazione completa (libera anche dato) */
void freeTree(tree T) {
    if (T == NULL) return;
    freeTree(T->left);
    freeTree(T->right);
    free(T->dato);
    free(T);
}

int scorrialbero(tree albero, int K, tree root);
int funz(tree albero, int K);

int main(void) {
    int K;

    printf("Inserisci K: ");
    if (scanf("%d", &K) != 1 || K < 0) {
        printf("Input non valido.\n");
        return 1;
    }

    /* Esempio di albero (puoi modificarlo a piacere):
             5
            / \
           5   7
          / \
         5   2
       Valori: 5,5,7,5,2
    */
    tree T =
        newNode(5,
            newNode(5,
                newNode(5, NULL, NULL),
                newNode(2, NULL, NULL)
            ),
            newNode(7, NULL, NULL)
        );

    printf("\nAlbero (in-order con parentesi):\n");
    printTree(T);
    printf("\n");

    /* Chiamata alla funzione dell'esercizio */
    int res = funz(T, K);

    printf("\nRisultato alberoConKElementiUguali(T, %d) = %d\n", K, res);

    freeTree(T);
    return 0;
}


void trovaelemento(tree albero, int x, int *count)
    {
        if(albero==NULL)
            return;
        if(x==*albero->dato)
            (*count)++;
    trovaelemento(albero->left, x, count);
    trovaelemento(albero->right, x, count);
    }
int scorrialbero(tree albero, int K, tree root)
    {
        if(albero==NULL)
            return 0;
        int count=0;
        trovaelemento(root, *albero->dato, &count);
        if(count==K)
            return 1;
    return scorrialbero(albero->left, K, root) || scorrialbero(albero->right, K, root);
    }
int funz(tree albero, int K)
    {
    return scorrialbero(albero, K, albero);
    }
