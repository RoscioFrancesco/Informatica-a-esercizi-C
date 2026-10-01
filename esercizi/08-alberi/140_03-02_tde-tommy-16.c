//
//  main.c
//  tde tommy-16
//
//  Created by Francesco Roscio Ricon on 03/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

/* =======================
   STRUTTURE (come traccia)
   ======================= */
typedef struct EL {
    int dato;
    struct EL *left, *right;
} node;

typedef node* tree;

/* =======================
   UTILITY: crea nodo
   ======================= */
static tree newNode(int v, tree l, tree r) {
    tree n = (tree)malloc(sizeof(node));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = v;
    n->left = l;
    n->right = r;
    return n;
}

/* =======================
   UTILITY: stampa albero (inorder)
   ======================= */
static void printInOrder(tree t) {
    if (!t) return;
    printInOrder(t->left);
    printf("%d ", t->dato);
    printInOrder(t->right);
}

/* stampa “a struttura” (ruotato) */
static void printTreeRotated(tree t, int depth) {
    if (!t) return;
    printTreeRotated(t->right, depth + 1);
    for (int i = 0; i < depth; i++) printf("    ");
    printf("%d\n", t->dato);
    printTreeRotated(t->left, depth + 1);
}

/* =======================
   UTILITY: libera albero
   ======================= */
static void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}


int wrapperscorrialbero(tree albero, int x, tree punt);
void trovamax(tree albero, int *max);
void trovamin(tree albero, int *min);
void f(tree T, int *diffmin, tree root);
int minDiff(tree albero);

int main(void) {

    printf("=== Esercizio: differenza minima tra due nodi di un albero binario ===\n\n");

    /* Caso 1: albero vuoto */
    {
        tree t = NULL;
        printf("Caso 1: albero vuoto\n");
        printf("Inorder: ");
        printInOrder(t);
        printf("\nRisultato minDiff = %d\n\n", minDiff(t));
    }

    /* Caso 2: un solo nodo */
    {
        tree t = newNode(10, NULL, NULL);
        printf("Caso 2: un solo nodo\n");
        printf("Albero (ruotato):\n");
        printTreeRotated(t, 0);
        printf("Inorder: ");
        printInOrder(t);
        printf("\nRisultato minDiff = %d\n\n", minDiff(t));
        freeTree(t);
    }

    /* Caso 3: albero generico (non BST) */
    {
        /* Struttura:
                 8
               /   \
              20    3
             /  \    \
            7   12    9

           Differenze minime: tra 8 e 7 = 1 (oppure 9 e 8 = 1)
        */
        tree t = newNode(8,
                    newNode(20,
                        newNode(7, NULL, NULL),
                        newNode(12, NULL, NULL)),
                    newNode(3,
                        NULL,
                        newNode(9, NULL, NULL)));

        printf("Caso 3: albero generico\n");
        printf("Albero (ruotato):\n");
        printTreeRotated(t, 0);
        printf("Inorder: ");
        printInOrder(t);
        printf("\nRisultato minDiff = %d\n\n", minDiff(t));
        freeTree(t);
    }

    /* Caso 4: altro test */
    {
        /* Struttura:
              15
             /  \
            1    40
                /  \
               30  41

           minDiff = 1 (40 e 41)
        */
        tree t = newNode(15,
                    newNode(1, NULL, NULL),
                    newNode(15,
                        newNode(30, NULL, NULL),
                        newNode(41, NULL, NULL)));

        printf("Caso 4: altro test\n");
        printf("Albero (ruotato):\n");
        printTreeRotated(t, 0);
        printf("Inorder: ");
        printInOrder(t);
        printf("\nRisultato minDiff = %d\n\n", minDiff(t));
        freeTree(t);
    }
    {
        tree t = newNode(10,
                    newNode(3, NULL, NULL),
                    NULL);
        printf("Caso 5: altro test\n");
        printf("Albero (ruotato):\n");
        printTreeRotated(t, 0);
        printf("Inorder: ");
        printInOrder(t);
        printf("\nRisultato minDiff = %d\n\n", minDiff(t));
        freeTree(t);
    }

    return 0;
}
void trovamax(tree albero, int *max)
    {
        if(albero==NULL)
            return;
        if(*max<albero->dato)
            *max=albero->dato;
    trovamax(albero->left, max);
    trovamax(albero->right, max);
    }
void trovamin(tree albero, int *min)
    {
        if(albero==NULL)
            return;
        if(*min>albero->dato)
            *min=albero->dato;
    trovamin(albero->left, min);
    trovamin(albero->right, min);
    }
int diffmax(tree T)
    {
    if(T==NULL)
        return 0;
    int max=0;
    trovamax(T, &max);
    int min=T->dato;
    trovamin(T, &min);
    return max-min;
    }
void f(tree T, int *diffmin, tree root)
    {
        if(T==NULL)
            return;
    if(*diffmin>wrapperscorrialbero(root, T->dato, T))
            {
                *diffmin=wrapperscorrialbero(root, T->dato, T);
            }
    f(T->left, diffmin, root);
    f(T->right, diffmin, root);
    }
int minDiff(tree albero)
    {
    if(albero==NULL)
        return 0;
    int max=diffmax(albero);
    int diffmin=max;
    f(albero, &diffmin, albero);
    return diffmin;
    }
void scorrialbero(int x, tree albero, int *diffmin, tree punt)
{
    if(albero==NULL)
        return;
    if(punt!=albero && abs(x-albero->dato)<*diffmin)
        {
            *diffmin=abs(x-albero->dato);
        }
    scorrialbero(x, albero->left, diffmin, punt);
    scorrialbero(x, albero->right, diffmin, punt);
    }
int wrapperscorrialbero(tree albero, int x, tree punt)
    {
    int diffmin=diffmax(albero);
    scorrialbero(x, albero, &diffmin, punt);
    return diffmin;
    }
