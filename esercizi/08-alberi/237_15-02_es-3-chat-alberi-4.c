//
//  main.c
//  es 3 chat alberi -4
//
//  Created by Francesco Roscio Ricon on 15/02/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct EL {
    int dato;
    struct EL *left;
    struct EL *right;
} node;

typedef node* tree;

static tree newNode(int x) {
    tree n = (tree)malloc(sizeof(node));
    n->dato = x;
    n->left = NULL;
    n->right = NULL;
    return n;
}

static void freeTree(tree t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* Preorder “con parentesi” per vedere la forma */
static void stampaPreorder(tree t) {
    if (t == NULL) { printf("NULL"); return; }
    printf("%d(", t->dato);
    stampaPreorder(t->left);
    printf(",");
    stampaPreorder(t->right);
    printf(")");
}

/* ============================
   ESERCIZIO 3 (DA SVOLGERE)
   ============================ */
/*
ESERCIZIO 3 (12 pt) — “Sottoalbero bilanciato per somma a livelli”

Un nodo X è buono se nel suo sottoalbero vale:

1) |sommaLivelloMax - sommaLivelloMax-1| <= S
2) tutte le foglie sono su al massimo 2 profondità diverse (quasi-perfetto)

Scrivere:
    int contaBuoni(tree T, int S);

Note:
- Devi far risalire più info: minDepthFoglia, maxDepthFoglia, sommaDepthMax, sommaDepthMax-1.
- Profondità RELATIVE al nodo X (non all’intero albero).
*/

/* STUB: compila e gira, ma NON risolve l'esercizio */
int contaBuoni(tree T, int S);

/* ============================
   ALBERI DI TEST (costruiti a mano)
   ============================ */

/* TEST 1 (atteso: 7 con S=10)
        10
      /    \
     4      6
    / \    / \
   3  1   2  4

È perfetto: ogni sottoalbero è quasi-perfetto.
Con questi valori: differenze tra somma livello max e max-1 risultano 0 o piccole,
quindi tutti i 7 nodi risultano “buoni”.
*/
static tree buildTest1(void) {
    tree r = newNode(10);
    r->left = newNode(4);
    r->right = newNode(6);

    r->left->left = newNode(3);
    r->left->right = newNode(1);

    r->right->left = newNode(2);
    r->right->right = newNode(4);
    return r;
}


static tree buildTest2(void) {
    tree r = newNode(8);
    r->left = newNode(4);
    r->right = newNode(5);
    r->left->left = newNode(3);
    return r;
}

/* TEST 3 (atteso: 4 con S=100)
       7
      / \
     4   6
    /
   2
  /
 1

- La radice 7 NON è quasi-perfetta: ha foglie a profondità 1 (6) e 3 (1) => differenza 2.
- I sottoalberi in 4, 2, 1 e 6 sono quasi-perfetti e con S=100 passano anche la soglia.
Conteggio buoni atteso: 4 (tutti tranne la radice).
*/
static tree buildTest3(void) {
    tree r = newNode(7);
    r->left = newNode(4);
    r->right = newNode(6);

    r->left->left = newNode(2);
    r->left->left->left = newNode(1);
    return r;
}

void riempivett(tree albero, int vett[], int d);
void wrapper(tree t, int S, int *count);

int main(void) {
    /* TEST 1 */
    {
        int S = 10;
        tree T = buildTest1();
        printf("=== TEST 1 ===\n");
        printf("S = %d\n", S);
        printf("Albero (preorder): ");
        stampaPreorder(T);
        printf("\n");

        int out = contaBuoni(T, S);
        printf("contaBuoni (ottenuto): %d\n", out);
        printf("contaBuoni ATTESO (corretto): 7\n\n");

        freeTree(T);
    }

    /* TEST 2 */
    {
        int S = 5;
        tree T = buildTest2();
        printf("=== TEST 2 ===\n");
        printf("S = %d\n", S);
        printf("Albero (preorder): ");
        stampaPreorder(T);
        printf("\n");

        int out = contaBuoni(T, S);
        printf("contaBuoni (ottenuto): %d\n", out);
        printf("contaBuoni ATTESO (corretto): 3\n\n");

        freeTree(T);
    }

    /* TEST 3 */
    {
        int S = 100;
        tree T = buildTest3();
        printf("=== TEST 3 ===\n");
        printf("S = %d\n", S);
        printf("Albero (preorder): ");
        stampaPreorder(T);
        printf("\n");

        int out = contaBuoni(T, S);
        printf("contaBuoni (ottenuto): %d\n", out);
        printf("contaBuoni ATTESO (corretto): 4\n\n");

        freeTree(T);
    }

    return 0;
}
int max(int a, int b)
    {
        if(a>b)
            return a;
    return b;
    }
int depth(tree t)
    {
    if(t==NULL)
        return 0;
    int sx=depth(t->left);
    int dx=depth(t->right);
    return 1+max(sx, dx);
    }
void riempivett(tree albero, int vett[], int d)
    {
        if(albero==NULL)
            return;
    vett[d]=vett[d]+albero->dato;
    riempivett(albero->left, vett, d+1);
    riempivett(albero->right, vett, d+1);
    }

void riempifoglie(tree albero, int foglie[], int d)
    {
        if(albero==NULL)
            return;
    if(albero->left==NULL && albero->right==NULL)
        {
            (foglie[d])++;
        }
    riempifoglie(albero->left, foglie, d+1);
    riempifoglie(albero->right, foglie, d+1);
    }
int èbuono(tree t, int S)
    {
        if(t==NULL)
            return 0;
        int prof=depth(t);
        int *vett=malloc(sizeof(int)*(prof+1));
        int *foglie=malloc(sizeof(int)*(prof+1));
        for(int i=0; i<=prof; i++)
            {
                vett[i]=0;
                foglie[i]=0;
            }
        riempivett(t, vett, 0);
        riempifoglie(t, foglie,0);
    int count=0;
    for(int i=0; i<prof; i++)
        {
            if(foglie[i]!=0)
                count++;
        }
    if(count>2)
    {
        free(vett);
        free(foglie);
        return 0;
    }
    if(prof<2)
        {
            free(vett);
            free(foglie);
            return 1;
        }
    if(abs(vett[prof-1]-vett[prof-2])<=S)
    {
        free(vett);
        free(foglie);
        return 1;
    }
    return 0;
    }
int contaBuoni(tree T, int S) {
    int count=0;
    wrapper(T, S, &count);
    return count;
}
void wrapper(tree t, int S, int *count)
    {
        if(t==NULL)
            return;
        if(èbuono(t, S))
            (*count)++;
    wrapper(t->left, S, count);
    wrapper(t->right, S, count);
    }
