//
//  main.c
//  tde 8 alberi -14
//
//  Created by Francesco Roscio Ricon on 05/02/26.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct TB {
    long int fiocchi, portata;
    struct TB *left, *right;
} Ramo;

typedef Ramo *Tree;

int resiste(Tree t);

/* =========================================================
   UTILITY per costruire / stampare / distruggere alberi
   (qui i cicli sono OK per test nel main)
   ========================================================= */
static Tree newNode(long int fiocchi, long int portata, Tree left, Tree right) {
    Tree n = (Tree)malloc(sizeof(Ramo));
    if (!n) { perror("malloc"); exit(1); }
    n->fiocchi = fiocchi;
    n->portata = portata;
    n->left = left;
    n->right = right;
    return n;
}

static void printTreeIndented(Tree t, int depth) {
    if (!t) return;
    /* stampa ruotata: prima destra, poi nodo, poi sinistra */
    printTreeIndented(t->right, depth + 1);

    for (int i = 0; i < depth; i++) printf("    ");
    printf("(%ld/%ld)\n", t->fiocchi, t->portata);

    printTreeIndented(t->left, depth + 1);
}

static void freeTree(Tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* =========================================================
   ESEMPI DI ALBERI DI TEST (modificali come vuoi)
   ========================================================= */

/* Albero piccolo “a mano” */
static Tree buildExample1(void) {
    /*
          (fiocchi/portata)
               (2/20)
              /     \
          (3/10)   (1/12)
           /   \
        (4/4)  (1/6)
    */
    Tree a = newNode(4, 4, NULL, NULL);
    Tree b = newNode(1, 6, NULL, NULL);
    Tree c = newNode(3, 10, a, b);
    Tree d = newNode(8, 12, NULL, NULL);
    Tree r = newNode(2, 20, c, d);
    return r;
}

/* Albero “solo radice” */
static Tree buildExample2(void) {
    return newNode(5, 5, NULL, NULL);
}

/* =========================================================
   MAIN DI TEST
   ========================================================= */
int scorri_albero(Tree albero);
int resiste(Tree albero);
long somma(Tree albero);
int main(void) {
    printf("=== TEST resiste(Tree) ===\n\n");

    /* Test 1 */
    Tree t1 = buildExample1();
    printf("[T1] Albero (stampa ruotata):\n");
    printTreeIndented(t1, 0);

    /* qui chiami la tua funzione */
    printf("[T1] resiste(t1) = %d (atteso: dipende dalla tua implementazione)\n\n", resiste(t1));

    freeTree(t1);

    /* Test 2 */
    Tree t2 = buildExample2();
    printf("[T2] Albero (stampa ruotata):\n");
    printTreeIndented(t2, 0);

    printf("[T2] resiste(t2) = %d (atteso: dipende dalla tua implementazione)\n\n", resiste(t2));

    freeTree(t2);

    printf("Fine test.\n");
    printf("\n%d", scorri_albero(t2));
    return 0;
}



long somma(Tree albero)
    {
        if(albero==NULL)
            return 0;
    return  albero->fiocchi+somma(albero->left)+somma(albero->right);
    }
int resiste(Tree albero)
    {
        if(albero==NULL)
            return 1;
        Tree temp=albero;
        long somma_nodo=somma(temp);
        if(somma_nodo>albero->portata)
            return 0;
    return resiste(albero->left)&&resiste(albero->right);
    }

int ripartiz(Tree albero) // 1 se ripartizione verificata, altrimenti 0
    {
        if(albero==NULL)
            return 1;
        long sx=somma(albero->left);
        long dx=somma(albero->right);
        if(sx/(sx+dx)<0.6 && sx/(sx+dx)>0.4)
            return 1;
        return 0;
    }
int scorri_albero(Tree albero)
    {
        if(albero==NULL)
            return 0;
        if (albero->left == NULL || albero->right == NULL)
            return 0;
        if(albero->left==NULL && albero->right==NULL)
            return 0;
        if(ripartiz(albero)==0)
            return 1;
    return scorri_albero(albero->left)||scorri_albero(albero->right);
    }
