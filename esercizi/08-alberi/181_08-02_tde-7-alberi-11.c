//
//  main.c
//  tde 7 alberi -11
//
//  Created by Francesco Roscio Ricon on 08/02/26.
//

#include <stdio.h>
#include <stdlib.h>

/* =========================
   STRUTTURE (come da testo)
   ========================= */
typedef struct ET {
    int *dato;              /* puntatore a int (dinamico) */
    struct ET *left;
    struct ET *right;
} treeNode;

typedef treeNode *tree;

/* =========================
   PROTOTIPO FUNZIONE ESERCIZIO (DA FARE)
   ========================= */
int oxfordiano(tree t);



void contafoglie(tree albero, int *contafoglie);
/* =========================
   UTILITY: crea nodo + stampa + free
   ========================= */
static tree nuovoNodo(int valore) {
    tree n = (tree)malloc(sizeof(*n));
    if (!n) { perror("malloc"); exit(1); }

    n->dato = (int *)malloc(sizeof(int));
    if (!n->dato) { perror("malloc"); exit(1); }
    *(n->dato) = valore;

    n->left = NULL;
    n->right = NULL;
    return n;
}

static void stampaPreorder(tree t) {
    if (t == NULL) {
        printf("NULL ");
        return;
    }
    printf("%d ", *(t->dato));
    stampaPreorder(t->left);
    stampaPreorder(t->right);
}

static void freeTree(tree t) {
    if (t == NULL) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t->dato);
    free(t);
}

/* =========================
   MAIN DI TEST
   ========================= */
void riempi(tree albero, int v[], int somma, int *scorri);
int main(void) {
    /*
        Costruisco un albero di test:

                 3
               /   \
              0     6
             / \     \
            0   3     0

        Percorsi radice->foglia e somme:
        3-0-0  = 3  (divisibile per 3)
        3-0-3  = 6  (divisibile per 3)
        3-6-0  = 9  (divisibile per 3)

        Quindi dovrebbe essere oxfordiano (atteso: 1)
    */
    tree t = nuovoNodo(3);
    t->left = nuovoNodo(0);
    t->right = nuovoNodo(6);
    t->left->left = nuovoNodo(0);
    t->left->right = nuovoNodo(3);
    t->right->right = nuovoNodo(0);

    printf("Albero (preorder): ");
    stampaPreorder(t);
    printf("\n");

    int res = oxfordiano(t);
    printf("oxfordiano(t) = %d\n", res);
    printf("(atteso: 1 se implementato correttamente)\n\n");

    /*
        Secondo albero: basta un percorso con somma NON divisibile per 3 per fare 0.

                 3
               /   \
              1     6
                   /
                  0

        Percorsi:
        3-1 = 4 (NON divisibile per 3) -> quindi non oxfordiano (atteso: 0)
    */
    tree t2 = nuovoNodo(3);
    t2->left = nuovoNodo(1);
    t2->right = nuovoNodo(6);
    t2->right->left = nuovoNodo(0);

    printf("Albero2 (preorder): ");
    stampaPreorder(t2);
    printf("\n");

    int res2 = oxfordiano(t2);
    printf("oxfordiano(t2) = %d\n", res2);
    printf("(atteso: 0 se implementato correttamente)\n");

    freeTree(t);
    freeTree(t2);
    return 0;
}
void contafoglie(tree albero, int *sum)
    {
        if(albero==NULL)
            return;
        if(albero->left==NULL && albero->right==NULL)
            (*sum)++;
    contafoglie(albero->left, sum);
    contafoglie(albero->right, sum);
    }
int wrappercontafoglie(tree albero)
    {
    int conta=0;
    contafoglie(albero, &conta);
    return conta;
    }

void riempi(tree albero, int v[], int somma, int *scorri)
    {
        if(albero==NULL)
            return;
        somma=somma+(*albero->dato);
        if(albero->left==NULL && albero->right==NULL)
            {
                v[*scorri]=somma;
                (*scorri)++;
            }
    riempi(albero->left, v, somma, scorri);
    riempi(albero->right, v, somma, scorri);
    }
int oxfordiano(tree albero)
    {
        if(albero==NULL)
            return 0;
        int len=wrappercontafoglie(albero);
    int *v=malloc(sizeof(int)*len);
    for(int i=0; i<len; i++)
        {
            v[i]=0;
        }
    int scorri=0;
    riempi(albero, v, 0, &scorri);
    for(int i=0; i<len; i++)
        {
            if(v[i]%3!=0)
                return 0;
        }
    return 1;
    }
