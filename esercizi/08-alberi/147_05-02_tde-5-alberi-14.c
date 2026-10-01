//  Created by Francesco Roscio Ricon on 05/02/26.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

/* =========================
   STRUTTURA DELL'ALBERO
   ========================= */
typedef struct EL {
    int dato;               /* solo valori positivi */
    struct EL *left, *right;
} node;

typedef node* tree;


int diffMinima(tree t);   

/* =========================
   UTILITY: creazione / inserimento / stampa / free
   (qui i cicli vanno bene: sono solo per test)
   ========================= */
static node* newNode(int x) {
    node* n = (node*)malloc(sizeof(node));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = x;
    n->left = n->right = NULL;
    return n;
}


static tree bstInsert(tree t, int x) {
    if (t == NULL) return newNode(x);
    if (x < t->dato) t->left = bstInsert(t->left, x);
    else            t->right = bstInsert(t->right, x);
    return t;
}

static void printInOrder(tree t) {
    if (t == NULL) return;
    printInOrder(t->left);
    printf("%d ", t->dato);
    printInOrder(t->right);
}

static void freeTree(tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =========================
   MAIN DI TEST
   ========================= */
void trovamin(tree root, int *min);
int wrapper_min(tree root);
int wrapper_max(tree root);
void trovamax(tree root, int *max);
void diffmin(tree albero, tree nodo_mio, int*min);
void diffmin_scorrendoalbero(tree albero, int *min, tree root);

int main(void) {
    tree t = NULL;

    /* Albero di esempio (BST) */
    int v[] = {50, 20, 70, 10, 30, 25, 60, 90, 65};
    int n = (int)(sizeof(v) / sizeof(v[0]));

    for (int i = 0; i < n; i++)
        t = bstInsert(t, v[i]);

    printf("Albero (in-order): ");
    printInOrder(t);
    printf("\n");

    /* Chiamata alla funzione dell'esercizio */
    int ans = diffMinima(t);   
    printf("Differenza minima tra due nodi: %d\n", ans);

    freeTree(t);
    return 0;
}

/* =========================
   QUI SCRIVERAI LE FUNZIONI DI SUPPORTO + diffMinima(...)
   ========================= */
/*
int diffMinima(tree t) {
    // TODO
}
*/

void trovamax(tree root, int *max)
    {
        if(root==NULL)
            return;
        if(*max<root->dato)
            *max=root->dato;
    trovamax(root->left, max);
    trovamax(root->right, max);
    }
int wrapper_max(tree root)
    {
    int max=0;
    trovamax(root, &max);
    return max;
    }
int wrapper_min(tree root)
    {
    int min=wrapper_max(root);
    trovamin(root, &min);
    return min;
    }
void trovamin(tree root, int *min)
    {
        if(root==NULL)
            return;
        if(*min>root->dato)
            *min=root->dato;
    trovamin(root->left, min);
    trovamin(root->right, min);
    }
void diffmin(tree albero, tree nodo_mio, int*min)
    {
        if(albero==NULL)
            return;
        if(abs(albero->dato-nodo_mio->dato)<*min && nodo_mio!=albero)
            *min=abs(albero->dato-nodo_mio->dato);
    diffmin(albero->left, nodo_mio, min);
    diffmin(albero->right, nodo_mio, min);
    }
int diffmax(tree albero)
    {
    return wrapper_max(albero)-wrapper_min(albero);
    }
void diffmin_scorrendoalbero(tree albero, int *min, tree root)
    {
    if(albero==NULL)
        return;
    diffmin(root, albero, min);
    diffmin_scorrendoalbero(albero->left, min, root);
    diffmin_scorrendoalbero(albero->right, min, root);
    }
int diffMinima(tree albero)
    {
        if(albero==NULL)
            return 0;
        int min=diffmax(albero);
        diffmin_scorrendoalbero(albero, &min, albero);
        return min;
    }
