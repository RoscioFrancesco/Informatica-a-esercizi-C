//
//  main.c
//  tde carta tde 5 albero -15
//
//  Created by Francesco Roscio Ricon on 04/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct t {
    int valore;
    struct t *left, *right;
} Nodo;

typedef Nodo *Tree;


int f(Tree t);

/* =========================
   UTILITY: creazione / stampa / free
   ========================= */
static Tree newNode(int v, Tree left, Tree right) {
    Tree n = (Tree)malloc(sizeof(Nodo));
    if (!n) { perror("malloc"); exit(1); }
    n->valore = v;
    n->left = left;
    n->right = right;
    return n;
}

static void freeTree(Tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* stampa preorder per vedere la struttura */
static void printTree(Tree t) {
    if (!t) { printf("NULL"); return; }
    printf("%d(", t->valore);
    printTree(t->left);
    printf(", ");
    printTree(t->right);
    printf(")");
}

/* altezza (utile per stampare per livelli nei test) */
static int height(Tree t) {
    if (!t) return 0;
    int hl = height(t->left);
    int hr = height(t->right);
    return 1 + (hl > hr ? hl : hr);
}

static void printLevel(Tree t, int level) {
    if (level == 1) {
        if (t) printf("%d ", t->valore);
        else   printf("_ ");
        return;
    }
    if (!t) {
        /* espando NULL per mantenere il “layout” */
        printLevel(NULL, level - 1);
        printLevel(NULL, level - 1);
        return;
    }
    printLevel(t->left, level - 1);
    printLevel(t->right, level - 1);
}

static void printByLevels(Tree t) {
    int h = height(t);
    for (int i = 1; i <= h; i++) {
        printf("Livello %d: ", i);
        printLevel(t, i);
        printf("\n");
    }
}

/* =========================
   MAIN DI TEST
   ========================= */
int profondita(Tree t);
int max(int a, int b);
int main(void) {
    
    Tree t = newNode(10,
                newNode(5,
                    newNode(3, NULL, NULL),
                    newNode(7, NULL, NULL)
                ),
                newNode(20,
                    newNode(15, NULL, NULL),
                    newNode(30, NULL, NULL)
                )
            );
    printf("Albero (preorder): ");
    printTree(t);
    printf("\n\n");

    printf("Albero per livelli:\n");
    printByLevels(t);
    printf("\n");

    int ans = f(t);
    printf("Risultato f(t) = %d\n", ans);
    printf("Atteso: 4\n");

    freeTree(t);
    return 0;
}
int profondita(Tree t)
    {
        if(t==NULL)
            return 0;
    int sx=profondita(t->left);
    int dx=profondita(t->right);
    return max(sx, dx)+1;
    }
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int* vettore(int k)
    {
    int *v=malloc(sizeof(int)*k);
    for(int i=0; i<k; i++)
        {
            v[i]=0;
        }
        return v;
    }
void funz(Tree albero, int v[], int profondità)
    {
        if(albero==NULL)
            return;
        v[profondità]++;
    funz(albero->left, v, profondità+1);
    funz(albero->right, v, profondità+1);
    }
int f(Tree albero)
    {
    if(albero==NULL)
        return 0;
    int k=profondita(albero);
    int *v=vettore(k);
    funz(albero, v, 0);
    int max=0;
    for(int i=0; i<k; i++)
        {
            if(v[i]>max)
                {
                    max=v[i];
                }
        }
    free(v);
        return max;
    }
