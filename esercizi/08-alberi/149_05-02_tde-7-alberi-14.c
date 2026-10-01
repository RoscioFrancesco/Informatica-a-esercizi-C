//
//  main.c
//  tde  7 alberi -14
//
//  Created by Francesco Roscio Ricon on 05/02/26.
#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   STRUTTURE DATI (come da consegna)
   ========================================================= */
typedef struct EL {
    int dato;
    struct EL *left, *right;
} node;

typedef node* tree;

/* =========================================================
   PROTOTIPI (funzione richiesta + supporto per test)
   ========================================================= */
int verificaSommeIncrociate(tree TA, tree TB);  /* TODO: NON svolta */

/* funzioni di supporto (consigliate dalla consegna) */
int sommaFoglie(tree T);        /* TODO */
int sommaInterni(tree T);       /* TODO */
int contieneValore(tree T, int x); /* TODO */

/* utility per costruire/stampare/distruggere alberi */
static node* newNode(int dato, node* left, node* right);
static void stampaInOrder(tree T);
static void distruggi(tree T);

/* =========================================================
   MAIN DI TEST (codice runnabile)
   ========================================================= */
void sommainterni(tree albero, int* somma);
int trovaval(int x, tree albero);
int verificaSommeIncrociate(tree TA, tree TB);
void sommafolgia(tree albero, int* somma);
int èfoglia(tree albero);
static node* newNode(int dato, node* left, node* right);
int main(void) {
    /* Costruisco due alberi di esempio (a mano) */

    /* TA:
             10
            /  \
           5    7
          / \
         2   3
       (foglie: 2,3,7)
       (interni: 10,5)
    */
    tree TA = newNode(10,
                      newNode(5,
                              newNode(2, NULL, NULL),
                              newNode(3, NULL, NULL)),
                      newNode(7, NULL, NULL));

    /* TB:
             8
            / \
           4   6
              /
             1
       (foglie: 4,1)
       (interni: 8,6)
    */
    tree TB = newNode(8,
                      newNode(4, NULL, NULL),
                      newNode(6,
                              newNode(1, NULL, NULL),
                              NULL));

    int ok = verificaSommeIncrociate(TA, TB);
    printf("\nRisultato verificaSommeIncrociate(TA, TB) (placeholder): %d\n", ok);

}

/* =========================================================
   FUNZIONE RICHIESTA (NON SVOLTA: solo scaffold)
   ========================================================= */

int èfoglia(tree albero)
    {
        if(albero==NULL)
            return 0;
        if(albero->left==NULL&& albero->right==NULL)
            return 1;
    return 0;
    }
void sommafolgia(tree albero, int* somma)
    {
        if(albero==NULL)
            return;
        if(èfoglia(albero))
            *somma=(*somma)+albero->dato;
    sommafolgia(albero->left, somma);
    sommafolgia(albero->right, somma);
    }
int trovaval(int x, tree albero)
    {
        if(albero==NULL)
            return 0;
        if(albero->dato==x)
            return 1;
    return trovaval(x, albero->right)|| trovaval(x, albero->left);
    }

void sommainterni(tree albero, int* somma)
    {
        if(albero==NULL)
            return;
        if(!èfoglia(albero))
            *somma=(*somma)+albero->dato;
    sommainterni(albero->left, somma);
    sommainterni(albero->right, somma);
    }
int verificaSommeIncrociate(tree TA, tree TB)
    {
    int sommafoglieTB=0;
    sommafolgia(TB, &sommafoglieTB);
    int sommainterniTA=0;
    sommainterni(TA, &sommainterniTA);
    if(trovaval(sommafoglieTB, TA) && trovaval(sommainterniTA, TB))
        return 1;
    return 0;
    }
static node* newNode(int dato, node* left, node* right) {
    node *n = (node*)malloc(sizeof(node));
    if (!n) { perror("malloc"); exit(1); }
    n->dato = dato;
    n->left = left;
    n->right = right;
    return n;
}

static void stampaInOrder(tree T) {
    if (T == NULL) return;
    stampaInOrder(T->left);
    printf("%d ", T->dato);
    stampaInOrder(T->right);
}

static void distruggi(tree T) {
    if (T == NULL) return;
    distruggi(T->left);
    distruggi(T->right);
    free(T);
}


